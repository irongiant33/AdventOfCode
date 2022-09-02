#!/usr/bin/python3
"""
APPROACH:
There are 8 possible rotations for each tile:
1. same
2. L1/R3
3. L2/R2
4. L3/R1
5. flip x 		(same as L2/R2, flip y)
6. flip x, L1   (same as L3/R1, flip x  and  L1/R3, flip y)
7. flip y		(same as L2/R2, flip x)
8. flip y, L1   (same as L1/R3, flip x  and  L3/R1, flip y)

But we only need to code 2 types of transitions to represent all of these states
(L)eft rotate
Left rotate, Flip (LX)

Using these two, we can move between every state:
1. same       (L)  => L1/R3
2. L1/R3      (L)  => L2/R2
3. L2/R2      (L)  => L3/R3
4. L3/R1      (LX) => flip x
5. flip x     (L)  => flip x, L1
6. flip x, L1 (L)  => flip y
7. flip y     (L)  => flip y, L1
8. flip y, L1 (LX) => same

A grid of size N will always have N^2 tiles, so the brute force state space
ramps up exponentially according to:
8^(N^2)

Even for the trial problem of N=3, there are 134,217,728 combinations. This will
make the actual problem of N=12 much more difficult without reducing the state
space in some other way.

PART 1:

1. Start by pairing pieces together without rotating anything and see what the
output & leftovers are
2. From here, you could just try to place all of the edge pieces so that you can
build the corners. The middle of the puzzle shouldn't matter.
3. Find the four pieces closest to each of the corners. Using the rest of the
pieces that aren't in the puzzle, try to match them up with the four corner-ish
pieces. If there is a match, continue on to the next corner piece.
4. Once you've matched (or attempted to match) all corner-ish pieces, repeat
step 3 until you have a puzzle that is finally NxN. Then repeat step 3, except
if a corner piece already exists, omit it from the list.

PART 2:
1. Start by completing the puzzle.
2. Once the puzzle is completed, generate the sea map (this will require
translating the interior part of the image according to the final rotation)
3. search the map row by row by sliding the SECOND row of the dragon from row 1
to row M-1 , from column 0 to D-20 where M is the number of rows in the sea map
and D is the number of columsn in the sea map
4. If there is a match, test the row below and then the row above for the
existence of a sea monster. If there is a sea monster, change the # to O. Repeat
step 3-4 until the whole map is searched

The reason for starting with the second row, then the third row, then the first
row of the sea monster is the probability that there are 8 # is lower than 1 #.
So you can potentially save time by only looking at the strictest conditions
first.

To do this we will need the following:

- function to create tiles from a file
- using the first tile in the list, loop through every other tile to see if
  there is a match. do this for every tile except for the last tile.
	- if there is a match, add the tiles to the puzzle. 

- tile object
	- rotation property (value from 1-8)
	- ID property
	- array of row string that represent the tile
	- array of edge strings: [top, right, bottom, left] where each string is
	  defined from left to right, top to bottom.
	- match function that returns the relative position of the called tile. For
	  example:
	    tileObj.match(otherTile)
	  returns 0 if otherTile matches the top string of tileObj, 1 if otherTile
	  matches the right string of tileObj...etc. -1 if no match.
	- print function: prints the tile ID on the first line followed by every row
	  in the array of row strings representing the tile.
	- rotate function: rotates the tile according to the scheme above
- puzzle object
	- add function: adds tiles to the puzzle in the specified arrangement. For
	  example:
	    puzzle.add(tileObj, otherTile, 1)
	  The position in the 3rd parameter is similar to the match function of the
	  tile object. It means that otherTile is above tileObj. If the tiles do not
	  exist in the puzzle, add them. If one exists, add the other in a relative
	  position

	  Returns true if the piece was successfully added and returns false if a 
	  piece already exists in that position or if the depth/width of the puzzle
	  exceeds N
	- puzzle property: 2d array of tile objects that correspond to their
      position in the puzzle. My idea is that this is NOT initialized to be NxN,
	  rather it expands as pieces are added to it. 
	- print function: loops through the puzzle property and prints pieces,
	  printing spaces where there are empty pieces.

LIMITATION:
- There could be multiple tiles that fit the corner, necessitating a more
complete solution of the puzzle to validate that the corner fits both edges
rather than just one
"""
# global imports
import sys
from copy import deepcopy
import re

# global constants
DEFAULT_ROTATION = 1
TILE_IDENTIFIER = "Tile "
TOP = 1
RIGHT = 2
BOTTOM = 3
LEFT = 4
NUM_ROTATION_STATES = 8
MAX_NUM_ATTEMPTS = 100

# (?=()) notation circumvents the non-overlapping default characteristic of regex
MONSTER = [
	re.compile("(?=(..................#.))"),
	re.compile("(?=(#....##....##....###))"),
	re.compile("(?=(.#..#..#..#..#..#...))")
]
NUM_TAGS_PER_MONSTER = 15 # number of `#` symbols per monster

class Puzzle:
	"""
	Contains attributes of the entire collection of Tiles as well as functions
	to manipulate the tiles within the puzzle as well as the puzzle itself
	"""

	def __init__(self, size):
		self.puzzle = []
		self.size = size
		self.num_image_rows = 0
		self.num_image_cols = 0
		self.sea_map = []
		self.rotation = DEFAULT_ROTATION

	def __repr__(self):
		puzzle_str = ""
		for row in self.puzzle:
			for i in range(self.num_image_rows + 1):
				for col in row:
					if(col is None):
						# 2 additional spaces for buffer between tiles
						puzzle_str += " " * (self.num_image_cols + 2)
					else:
						row_string = col.row_repr(i)
						spaces = " " * (self.num_image_cols - len(row_string))
						puzzle_str += f"{row_string}{spaces}  "
				puzzle_str += "\n"
			puzzle_str += "\n"
		return puzzle_str

	def _check_neighbors(self, tile_row, tile_col, tile_obj):
		"""
		private function that guarantees the tile_obj matches all surrounding
		tiles, if they exist
		@param tile_row: the index of the row the new tile is located
		@param tile_col: the index of the column the new tile is located
		@param tile_obj: the tile to cross reference
		@return matches_all: boolean to indicate whether the tile_obj matches
							 all of its neighbors or not
		"""
		last_row_idx = len(self.puzzle) - 1
		last_col_idx = len(self.puzzle[0]) - 1

		# top check
		if(tile_row != 0):
			new_tile = self.puzzle[tile_row - 1][tile_col]
			if(new_tile is not None):
				match_pos = tile_obj.match(new_tile)
				if(TOP != match_pos):
					print(f"Doesn't match top! Match pos: {match_pos}")
					return False
		# bottom check
		if(tile_row != last_row_idx):
			new_tile = self.puzzle[tile_row + 1][tile_col]
			if(new_tile is not None):
				match_pos = tile_obj.match(new_tile)
				if(BOTTOM != match_pos):
					print(f"Doesn't match bottom! Match pos: {match_pos}")
					return False
		# left check
		if(tile_col != 0):
			new_tile = self.puzzle[tile_row][tile_col - 1]
			if(new_tile is not None):
				match_pos = tile_obj.match(new_tile)
				if(LEFT != match_pos):
					print(f"Doesn't match left! Match pos: {match_pos}")
					return False
		# right check
		if(tile_col != last_col_idx):
			new_tile = self.puzzle[tile_row][tile_col + 1]
			if(new_tile is not None):
				match_pos = tile_obj.match(new_tile)
				if(RIGHT != match_pos):
					print(f"Doesn't match right! Match pos: {match_pos}")
					return False
		return True
		

	def _add_above(self, rel_tile_row, rel_tile_col, new_tile):
		"""
		private function to add the new tile in the slot above the relative tile
		"""
		if(0 != rel_tile_row):
			if(self.puzzle[rel_tile_row - 1][rel_tile_col] is not None):
				print("Tile above already exists!")
				return False
			if(self._check_neighbors(rel_tile_row - 1, rel_tile_col, new_tile)):
				self.puzzle[rel_tile_row - 1][rel_tile_col] = new_tile
		elif(rel_tile_row == 0 and (len(self.puzzle) < self.size)):
			new_row = [None] * len(self.puzzle[rel_tile_row])
			new_row[rel_tile_col] = new_tile
			self.puzzle.insert(0, new_row)
		else:
			print(f"Cannot place outside of puzzle bounds! Size: {self.size}")
			return False
		return True


	def _add_right(self, rel_tile_row, rel_tile_col, new_tile):
		"""
		private function to add the new tile in the slot to the right of the
		relative tile
		"""
		puzzle_width = len(self.puzzle[0])
		last_col_idx = puzzle_width - 1
		if(rel_tile_col != last_col_idx):
			if(self.puzzle[rel_tile_row][rel_tile_col + 1] is not None):
				print("Tile right already exists!")
				return False
			if(self._check_neighbors(rel_tile_row, rel_tile_col + 1, new_tile)):
				self.puzzle[rel_tile_row][rel_tile_col + 1] = new_tile
		elif(rel_tile_col == last_col_idx and (puzzle_width < self.size)):
			for i in range(len(self.puzzle)):
				if(i == rel_tile_row):
					self.puzzle[i].append(new_tile)
				else:
					self.puzzle[i].append(None)
		else:
			print("Cannot place outside of puzzle bounds!")
			return False
		return True


	def _add_bottom(self, rel_tile_row, rel_tile_col, new_tile):
		"""
		private function to add the new tile in the slot to below the relative
		tile
		"""
		last_row_idx = len(self.puzzle) - 1
		if(rel_tile_row != last_row_idx):
			if(self.puzzle[rel_tile_row + 1][rel_tile_col] is not None):
				print("Tile bottom already exists!")
				return False
			if(self._check_neighbors(rel_tile_row + 1, rel_tile_col, new_tile)):
				self.puzzle[rel_tile_row + 1][rel_tile_col] = new_tile
		elif(rel_tile_row == last_row_idx and (len(self.puzzle) < self.size)):
			new_row = [None] * len(self.puzzle[rel_tile_row])
			new_row[rel_tile_col] = new_tile
			self.puzzle.append(new_row)
		else:
			print("Cannot place outside of puzzle bounds!")
			return False
		return True


	def _add_left(self, rel_tile_row, rel_tile_col, new_tile):
		"""
		private function to add the new tile in the slot to the left of the
		relative tile
		"""
		puzzle_width = len(self.puzzle[0])
		last_col_idx = puzzle_width - 1
		if(0 != rel_tile_col):
			if(self.puzzle[rel_tile_row][rel_tile_col - 1] is not None):
				print("Tile left already exists!")
				return False
			if(self._check_neighbors(rel_tile_row, rel_tile_col - 1, new_tile)):
				self.puzzle[rel_tile_row][rel_tile_col - 1] = new_tile
		elif(0 == rel_tile_col and (puzzle_width < self.size)):
			for i in range(len(self.puzzle)):
				if(i == rel_tile_row):
					self.puzzle[i].insert(0, new_tile)
				else:
					self.puzzle[i].insert(0, None)
		else:
			print("Cannot place outside of puzzle bounds!")
			return False
		return True


	def add(self, rel_tile, new_tile, rel_pos):
		"""
		Function to add tiles to the list.
		@param rel_tile: relative tile object
		@param new_tile: new tile object
		@param rel_pos: the position of the new tile object relative to rel_tile
						1 is above rel_tile, 2 is to the right, 3 is below, 4 is
						to the left
		@return success: true if one of the tiles were successfully added to the
						 list or if the tiles already existed in that
						 configuration
						 false if the tile to be added will be duplicated, or if
						 there is an existing tile in the relative position
		"""
		tiles_in_puzzle = []
		for row in self.puzzle:
			tiles_in_puzzle.extend(row)
		if(new_tile in tiles_in_puzzle):
			print("Tile is already in the puzzle!")
			return False

		rel_tile_row = 0
		rel_tile_col = 0
		if(0 == len(self.puzzle)):
			self.puzzle.append([rel_tile])
			self.num_image_cols = len(rel_tile.image[0])
			self.num_image_rows = len(rel_tile.image)
		elif(rel_tile not in tiles_in_puzzle):
			print("Relative tile does not exist!")
			return False

		for row_idx in range(0, len(self.puzzle)):
			for col_idx in range(0, len(self.puzzle[0])):
				if(rel_tile == self.puzzle[row_idx][col_idx]):
					rel_tile_row = row_idx
					rel_tile_col = col_idx
		try:
			if(TOP == rel_pos):
				return self._add_above(rel_tile_row, rel_tile_col, new_tile)
			elif(RIGHT == rel_pos):
				return self._add_right(rel_tile_row, rel_tile_col, new_tile)
			elif(BOTTOM == rel_pos):
				return self._add_bottom(rel_tile_row, rel_tile_col, new_tile)
			elif(LEFT == rel_pos):
				return self._add_left(rel_tile_row, rel_tile_col, new_tile)
		except(Exception) as err:
			print(f"rel_row: {rel_tile_row} rel_tile_col: {rel_tile_col}")
			print(f"width of puzzle: {len(self.puzzle[0])}")
			print(f"height of puzzle: {len(self.puzzle)}")
			print(err)
			sys.exit(0)


	def find_closest_tile(self, node_row_idx, node_col_idx):
		"""
		Finds the closest corner piece based on the manhattan distance. Since
		the puzzle grows as tiles are added, the longest the distance could be
		is one less than the size. This would be the case if we are searching
		for the tile closest to the top left corner and somehow the entire
		bottom row and entire right col were filled out with nothing in between.

		@param corner_row_idx: the row index of the corner to search
		@param corner_col_idx: the col index of the corner to search
		@return closest_tile: the tile object closest to the corner
		"""
		closest_tile = None
		min_dist = self.size
		for row_idx in range(0, len(self.puzzle)):
			for col_idx in range(0, len(self.puzzle[0])):
				dist = abs(node_row_idx - row_idx) + abs(node_col_idx - col_idx)
				tile = self.puzzle[row_idx][col_idx]
				if(dist < min_dist and tile is not None):
					min_dist = dist
					closest_tile = tile
		return closest_tile
	

	def find_close_corners(self):
		"""
		Function to find the four tiles that are closest to each corner. If a
		corner piece already exists, the function omits that tile from the
		return list.
		@return close_corners: list of tiles that are closest to each of the
							   four corners (in no particular order)
		"""
		width  = len(self.puzzle[0])
		height = len(self.puzzle)
		last_col_idx  = width - 1
		last_row_idx  = height - 1
		close_corners = []
		temp_corners = []
		
		left_top  = self.find_closest_tile(0, 0)
		right_top = self.find_closest_tile(0, last_col_idx)
		left_bot  = self.find_closest_tile(last_row_idx, 0)
		right_bot = self.find_closest_tile(last_row_idx, last_col_idx)
		if(width == self.size and height == self.size):
			if(self.puzzle[0][0] is None):
				temp_corners.append(left_top)
			if(self.puzzle[0][last_col_idx] is None):
				temp_corners.append(right_top)
			if(self.puzzle[last_row_idx][0] is None):
				temp_corners.append(left_bot)
			if(self.puzzle[last_row_idx][last_col_idx] is None):
				temp_corners.append(right_bot)
		else:
			temp_corners = [left_top, right_top, left_bot, right_bot]

		# prevent duplicate tiles appearing in the list
		for i in range(len(temp_corners)):
			if(temp_corners[i] not in temp_corners[i + 1:]):
				close_corners.append(temp_corners[i])
			

		return close_corners

	
	def corner_product(self):
		"""
		Finds the product of the ID of each of the 4 corners.
		@return product: product of 4 corner IDs. -1 on error.
		"""
		puzzle_width = len(self.puzzle[0])
		puzzle_height = len(self.puzzle)
		product = -1
		if(self.size == puzzle_height and self.size == puzzle_width):
			product = 1
			product *= self.puzzle[0][0].id
			product *= self.puzzle[0][puzzle_width - 1].id
			product *= self.puzzle[puzzle_height - 1][0].id
			product *= self.puzzle[puzzle_height - 1][puzzle_width - 1].id
		else:
			print("Puzzle is not finished!")
		return product


	def get_sea_map(self):
		"""
		Returns a list of strings corresponding to the sea map. Each string is a
		row in the map.
		@return sea_map: list of strings
		"""
		self.sea_map = []
		num_image_rows = len(self.puzzle[0][0].image)
		num_image_cols = len(self.puzzle[0][0].image[0])
		for row_idx in range(0, self.size):
			# exclude top and bottom edges
			for image_row_idx in range(1, num_image_rows - 1):
				sea_map_row = ""
				for col_idx in range(0, self.size):
					sea_map_row += self.puzzle[row_idx][col_idx].image[image_row_idx][1:(num_image_cols - 1)]
				self.sea_map.append(sea_map_row)

	
	def rotate(self):
		"""
		Rotates the sea map according to the rotation state
		"""
		temp_sea_map = deepcopy(self.sea_map)
		num_rows = len(self.sea_map)
		num_cols = len(self.sea_map[0])
		index = 0
		inc = 1

		# for state 1-3, 5-7, the first col will become the last row.
		if(self.rotation % 4 != 0):
			index = -1
			inc = -1

		# convert cols into rows
		for col_idx in range(0, num_cols):
			new_row = ""
			for row_idx in range(0, num_rows):
				new_row += temp_sea_map[row_idx][col_idx]
			self.sea_map[index] = new_row
			index += inc

		self.rotation += 1


class Tile:
	"""
	Contains attributes of a single tile as well as functions to manipulate
	the tile
	"""


	def __init__(self, image, id):
		"""
		Initialization function for a Tile
		@param image: array of strings representing the tile's image
		@param id: integer value corresponding to the ID # of the tile
		"""
		self.image = image
		self.id = id
		self._rotation = DEFAULT_ROTATION
		self.edges = self._get_edges()

	@property
	def rotation(self):
		return self._rotation

	@rotation.setter
	def rotation(self, value):
		# rotation values should be of the range 1-8
		self._rotation = ((value - 1) % NUM_ROTATION_STATES) + 1


	def _get_edges(self):
		"""
		Returns the edges of the image as a list
		@return edges -> list
		"""
		edges = []
		left_col = []
		right_col = []
		row_length = len(self.image[0])
		col_length = len(self.image)

		for row in self.image:
			left_col.append(row[0])
			right_col.append(row[row_length - 1])

		# in order: top, right, bottom, left
		edges.append(self.image[0])
		edges.append("".join(right_col))
		edges.append(self.image[col_length - 1])
		edges.append("".join(left_col))
		return edges


	def __str__(self):
		"""
		String representation of the ID when you don't want to display the tile
		"""
		return f"Tile #{self.id}/{self.rotation}"


	def get_tile_str(self, middle=False):
		"""
		@return string representation of the Tile
		"""
		representation = ""
		num_rows = len(self.image)
		
		if(middle):
			representation += f"{self.row_repr(0)}\n"
			for i in range(0,len(self.image)):
				representation += f"{self.image[i]}\n"
		else:
			for i in range(num_rows + 1):
				representation += f"{self.row_repr(i)}\n"
		return representation


	def row_repr(self, row_num):
		"""
		Returns a string representing each row in the image.
		Row 0 denotes the title. Row 1 denotes image[0], row 2 = image[1]...etc
		@param row_num: row index you wish to print
		@return string representation of the row
		"""
		num_rows = len(self.image)
		num_cols = len(self.image[0])
		if(0 == row_num):
			return(f"{self.id}/{self.rotation}")
		elif(1 == row_num):
			return(f"{self.edges[0]}")
		elif(num_rows == row_num):
			return(f"{self.edges[2]}")
		elif(1 < row_num < num_rows):
			spaces = " " * (num_cols - 2)
			return(f"{self.edges[3][row_num - 1]}{spaces}{self.edges[1][row_num -  1]}")
		else:
			print(f"Bad row num {row_num}")

	
	def match(self, other_tile):
		"""
		Determines whether this tile and other_tile match in any direction
		@param other_tile: other tile to find potential match
		@return position: relative position to this tile if there is a match
						  1 if the other_tile is on top
						  2 if on right
						  3 if on bottom
						  4 if on left
						 -1 if no match
		"""
		for i in range(0, len(self.edges)):
			# match index should always be opposite
			other_index = (i + 2) % 4
			if(self.edges[i] == other_tile.edges[other_index]):
				return (i + 1)
		return -1


	def rotate_edges(self):
		"""
		Rotates the edges according to the rotation state
		"""
		temp_edges = deepcopy(self.edges)
		# States 1-3, 5-7 are associated with (L)eft Rotation
		if(self.rotation % 4 != 0):
			self.edges[0] = temp_edges[1]
			self.edges[1] = temp_edges[2][-1::-1]
			self.edges[2] = temp_edges[3]
			self.edges[3] = temp_edges[0][-1::-1]
		# States 4, 8 are associated with left rotation, flip x (LX)
		else:
			self.edges[0] = temp_edges[3]
			self.edges[1] = temp_edges[2]
			self.edges[2] = temp_edges[1]
			self.edges[3] = temp_edges[0]
		self.rotation += 1

	def rotate(self):
		"""
		Rotates the image according to the rotation state
		"""
		temp_image = deepcopy(self.image)
		num_rows = len(self.image)
		num_cols = len(self.image[0])
		index = 0
		inc = 1

		# for state 1-3, 5-7, the first col will become the last row.
		if(self.rotation % 4 != 0):
			index = -1
			inc = -1

		# convert cols into rows
		for col_idx in range(0, num_cols):
			new_row = ""
			for row_idx in range(0, num_rows):
				new_row += temp_image[row_idx][col_idx]
			self.image[index] = new_row
			index += inc

		self.rotation += 1
		self.edges = self._get_edges()


def get_tile_list(filename):
	"""
	Returns a list of tile objects from the provided filename
	@param filename: name of the file to read from
	@return tile_list: list of tile objects in the file
	"""
	contents = []
	tile_list = []
	num_lines = 0
	tile_id = 0
	image = []
	line = ""

	with open(filename) as file_obj:
		contents = file_obj.readlines()

	num_lines = len(contents)
	for i in range(num_lines):
		line = contents[i].rstrip()
		if(0 == len(line)):
			new_tile = Tile(image, tile_id)
			tile_list.append(new_tile)
			tile_id = 0
			image = []
		elif(TILE_IDENTIFIER in line):
			colon_index = line.index(":")
			tile_id = int(line[len(TILE_IDENTIFIER):colon_index])
		else:
			image.append(line.rstrip())

	# for last tile (if there is no blank line at the end of the input text)
	if(image):
		new_tile = Tile(image, tile_id)
		tile_list.append(new_tile)
	
	return tile_list

if __name__ == "__main__":
	tile_list = get_tile_list("input.txt")
	puzzle_size = int(len(tile_list)**0.5)
	puzzle_obj = Puzzle(puzzle_size)
	tiles_not_in_puzzle = []
	tiles_in_puzzle = []

	# build puzzle without rotations
	for i in range(0, len(tile_list) - 1):
		primary_tile = tile_list[i]
		for j in range(i + 1, len(tile_list)):
			new_tile = tile_list[j]
			match_pos = primary_tile.match(new_tile)
			if(-1 != match_pos):
				print(f"{str(primary_tile)} matches {str(new_tile)} at {match_pos}")
				puzzle_obj.add(primary_tile, new_tile, match_pos)

	# find list of tiles in and out of the puzzle
	for row in puzzle_obj.puzzle:
		tiles_in_puzzle.extend(row)
	for tile in tile_list:
		if(tile not in tiles_in_puzzle):
			tiles_not_in_puzzle.append(tile)

	# build out to the corners using rotations
	attempts = 0
	closest_corners = puzzle_obj.find_close_corners()
	while(attempts < MAX_NUM_ATTEMPTS and 0 != len(closest_corners)):
		for tile in closest_corners:
			matched = -1
			index = 0
			new_tile = tiles_not_in_puzzle[index]
			while(-1 == matched and index < len(tiles_not_in_puzzle)):
				new_tile = tiles_not_in_puzzle[index]
				new_tile.rotate()
				matched = tile.match(new_tile)
				while(-1 == matched and new_tile.rotation != 1):
					new_tile.rotate()
					matched = tile.match(new_tile)
				index += 1
			if(-1 != matched):
				if(puzzle_obj.add(tile, new_tile, matched)):
					tiles_not_in_puzzle.remove(new_tile)
					tiles_in_puzzle.append(new_tile)
		closest_corners = puzzle_obj.find_close_corners()
		attempts += 1

	print(f"Answer to part 1 is: {puzzle_obj.corner_product()}")
	#################### END PART 1 ############################################

	# build out the rest of the puzzle
	attempts = 0
	while(attempts < MAX_NUM_ATTEMPTS and 0 != len(tiles_not_in_puzzle)):
		for row_idx in range(0, puzzle_size):
			for col_idx in range(0, puzzle_size):
				tile = puzzle_obj.puzzle[row_idx][col_idx]
				if(tile is None):
					closest_tile = puzzle_obj.find_closest_tile(row_idx, col_idx)
					matched = -1
					index = 0
					new_tile = tiles_not_in_puzzle[index]
					while(-1 == matched and index < len(tiles_not_in_puzzle)):
						new_tile = tiles_not_in_puzzle[index]
						new_tile.rotate()
						matched = closest_tile.match(new_tile)
						while(-1 == matched and new_tile.rotation != 1):
							new_tile.rotate()
							matched = closest_tile.match(new_tile)
						index += 1
					if(-1 != matched):
						if(puzzle_obj.add(closest_tile, new_tile, matched)):
							tiles_not_in_puzzle.remove(new_tile)
							tiles_in_puzzle.append(new_tile)
		attempts += 1
	
	# find number of monsters for every rotation
	puzzle_obj.get_sea_map()
	max_num_monsters = 0

	for k in range(1, NUM_ROTATION_STATES + 1):
		num_monsters = 0
		num_map_rows = len(puzzle_obj.sea_map)
		for i in range(1, num_map_rows - 1):
			matches = [[], [], []]
			rows = []
			rows.append(puzzle_obj.sea_map[i - 1])
			rows.append(puzzle_obj.sea_map[i])
			rows.append(puzzle_obj.sea_map[i + 1])

			finds = MONSTER[1].findall(rows[1])
			for find in finds:
				matches[1].append(rows[1].index(find))
			if(matches[1]):
				finds = MONSTER[2].findall(rows[2])
				for find in finds:
					matches[2].append(rows[2].index(find))
				if(matches[2]):
					finds = MONSTER[0].findall(rows[0])
					for find in finds:
						matches[0].append(rows[0].index(find))
					if(matches[0]):
						for match in matches[0]:
							if(match in matches[1] and match in matches[2]):
								num_monsters += 1

		if(num_monsters > max_num_monsters):
			max_num_monsters = num_monsters
		puzzle_obj.rotate()	

	# subtract the number of symbols in the monster from the total number of symbols
	tag_count = 0
	for row in puzzle_obj.sea_map:
		tag_count += row.count('#')
	leftovers = tag_count - max_num_monsters * NUM_TAGS_PER_MONSTER
	print(f"Part 2: The number of leftover # is: {leftovers}")
