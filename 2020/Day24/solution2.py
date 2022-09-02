#!/usr/bin/python3

import sys

INPUT_FILE_NAME = "input.txt"
# movement directions
direction_dict = {"e":[2,0], "w":[-2,0],"nw":[-1,1], "ne":[1,1],"sw":[-1,-1],"se":[1,-1]}
NUM_DAYS = 100

class Tile():
	def __init__(self,coordinates):
		self.coordinates = coordinates
		self.color = 0 # black = 1, white = 0.
		self.num_black_neighbors = 0
	
	def flip(self):
		self.color = (self.color + 1) % 2
	
	def match(self,coordinates):
		d = ((self.coordinates[0] - coordinates[0])**2 + (self.coordinates[1] - coordinates[1])**2)**0.5
		if(d < (3**0.5)/2):
			return True
		return False

	def get_neighbors(self,tiles):
		new_neighbors = []
		for direction in direction_dict:
			shift = direction_dict[direction]
			x_shift = self.coordinates[0] + shift[0]
			y_shift = self.coordinates[1] + shift[1]
			new_coordinates = (x_shift, y_shift)
			if(new_coordinates not in tiles):
				new_neighbors.append(Tile(new_coordinates))
			else:
				self.num_black_neighbors += tiles[new_coordinates].color
		return new_neighbors

	def __repr__(self):
		return self.color + " (" + str(self.num_black_neighbors)+")" + \
			": " + str(self.coordinates[0]) + ", " + str(self.coordinates[1])

def count_black_tiles(tiles):
	black_count = 0
	for tile in tiles:
		black_count += tile.color
	return black_count

if __name__ == "__main__":
	input_list = []
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()

	tiles = dict()
	for tile_instruction_str in input_list:
		tile_instruction = list(tile_instruction_str.rstrip())
		instruction_index = 0
		x_shift = 0
		y_shift = 0
		while(instruction_index < len(tile_instruction)):
			relative_move = tile_instruction[instruction_index]
			shift = []
			if(relative_move == "n" or relative_move == "s"):
				instruction_index = instruction_index + 1
				relative_move = relative_move + tile_instruction[instruction_index]
			shift = direction_dict[relative_move]
			x_shift += shift[0]
			y_shift += shift[1]
			instruction_index = instruction_index + 1

		tile_coordinates = (x_shift, y_shift)
		if(not tiles or tile_coordinates not in tiles):
			tiles[tile_coordinates] = Tile(tile_coordinates)

		tiles[tile_coordinates].flip()
	
	black_count = count_black_tiles(tiles.values())
	print("(part 1) the number of black tiles is: " + str(black_count))

	# fill in the rest of the tiles
	NUM_FILL_CYCLES = 3
	for _ in range(NUM_FILL_CYCLES):
		temp_dict = dict()
		for coordinate in tiles:
				tile = tiles[coordinate]

				new_neighbors = tile.get_neighbors(tiles)
				for neighbor in new_neighbors:
					if(neighbor.coordinates not in tiles and neighbor.coordinates not in temp_dict):
						temp_dict[neighbor.coordinates] = neighbor
		
		for coordinate in temp_dict:
			tiles[coordinate] = temp_dict[coordinate]


	for day_num in range(1,NUM_DAYS):

		for coordinate in tiles:
			tile = tiles[coordinate]
			if(tile.color == 1 and (tile.num_black_neighbors == 0 or tile.num_black_neighbors > 2)):
				tile.color = 0
			elif(tile.color == 0 and (tile.num_black_neighbors == 2)):
				tile.color = 1
		
		for coordinate in tiles:
			tile = tiles[coordinate]
			# NEED TO REMOVE THE PART OF THIS THAT ADDS NEW TILES?
			tile.get_neighbors(tiles)
		print(count_black_tiles(tiles.values()))

	black_count = count_black_tiles(tiles.values())
	print("(part 2) the number of black tiles after 100 days is: " + str(black_count))



