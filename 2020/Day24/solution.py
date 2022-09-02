INPUT_FILE_NAME = "input.txt"
# movement directions
direction_dict = {"e":[3**0.5,0], "w":[-(3**0.5),0],"nw":[-(3**0.5)/2,1.5], \
	"ne":[(3**0.5)/2,1.5],"sw":[-(3**0.5)/2,-1.5],"se":[(3**0.5)/2,-1.5]}
NUM_DAYS = 1

class Tile():
	def __init__(self,coordinates):
		self.coordinates = coordinates
		self.color = "black"
		self.num_black_neighbors = 0
	
	def flip(self):
		if(self.color == "white"):
			self.color == "black"
		else:
			self.color = "white"
	
	def match(self,coordinates):
		d = ((self.coordinates[0] - coordinates[0])**2 + (self.coordinates[1] - coordinates[1])**2)**0.5
		if(d < (3**0.5)/2):
			return True
		return False

	def get_neighbors(self,tiles,order=0):
		directions = list(direction_dict.keys())
		new_neighbors = []
		for direction in directions:
			add = direction_dict[direction]
			new_coordinates = [self.coordinates[0] + add[0], self.coordinates[1] + add[1]]
			found = False
			for tile in tiles:
				if(tile.color == "black" and tile.match(new_coordinates)):
					self.num_black_neighbors = self.num_black_neighbors + 1
					found = True
					break
			if(not found and order == 0):
				new_tile = Tile(new_coordinates)
				new_tile.color = "white"
				new_neighbors.append(new_tile)
				new_tile.get_neighbors(tiles,1)
		return new_neighbors

	def __repr__(self):
		return self.color + " (" + str(self.num_black_neighbors)+")" + \
			": " + str(self.coordinates[0]) + ", " + str(self.coordinates[1])

def count_black_tiles(tiles):
	black_count = 0
	for tile in tiles:
		if(tile.color == "black"):
			black_count = black_count + 1
	return black_count

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		tiles = []
		for day_num in range(0,NUM_DAYS):
			for line in input_list:
				line = list(line.rstrip())
				count = 0
				coordinates = [0,0]
				while(count < len(line)):
					item = line[count]
					add = []
					if(item == "n" or item == "s"):
						count = count + 1
						item = item + line[count]
					add = direction_dict[item]
					coordinates[0] = coordinates[0] + add[0]
					coordinates[1] = coordinates[1] + add[1]
					count = count + 1

				found = False
				for tile in tiles:
					if(tile.match(coordinates)):
						tile.flip()
						found = True
						break

				if(not found):
					new_tile = Tile(coordinates)
					tiles.append(new_tile)
			
			black_count = count_black_tiles(tiles)

			if(day_num == 0):
				print("(part 1) the number of black tiles is: " + str(black_count))

			num_tiles = len(tiles)
			for i in range(0,num_tiles):
				tile = tiles[i]
				#if(tile.color == "black"):
				new_neighbors = tile.get_neighbors(tiles)
				for neighbor in new_neighbors:
					add_neighbor = True
					for t in tiles:
						if(t.match(neighbor.coordinates)):
							add_neighbor = False
							break
					if(add_neighbor):
						tiles.append(neighbor)

			for tile in tiles:
				print(tile)
				if(tile.color == "black" and (tile.num_black_neighbors == 0 or tile.num_black_neighbors > 2)):
					tile.color = "white"
				elif(tile.color == "white" and (tile.num_black_neighbors == 2)):
					tile.color = "black"
			print(count_black_tiles(tiles))

		black_count = count_black_tiles(tiles)
		print("(part 2) the number of black tiles after 100 days is: " + str(black_count))



