import copy
import numpy as np

INPUT_FILE_NAME = "input.txt"

class Edge():
	def __init__(self,edge,tile_id):
		self.edge = edge
		self.tile_id = tile_id
		self.neighbors = []
	
	def add_neighbor(self,edge):
		self.neighbors.append(edge)

	def __eq__(self,other):
		return self.edge == other.edge

class Tile():
	def __init__(self,id_num,pixel_map,rotate=0):
		self.id_num = id_num
		self.original = pixel_map
		self.pixel_map = pixel_map
		self.edges = self.get_edges()
		self.rot(rotate)
		self.rotate = rotate #0,1,2,3 corresponding to how many times you turn the original clockwise

	def rot(self,amount):
		temp = np.rot90(self.original,amount)
		self.rotate = amount
		self.pixel_map = temp.tolist()
		self.edges = self.get_edges()

	def get_edges(self):
		edges = []
		dimension = len(self.pixel_map)
		# top row
		edges.append(Edge(self.pixel_map[0],self.id_num))
		# right column
		right_column = []
		left_column = []
		for i in range(0,dimension):
			right_column.append(self.pixel_map[i][dimension-1])
			left_column.append(self.pixel_map[i][0])
		edges.append(Edge(right_column,self.id_num))
		# bottom row
		edges.append(Edge(self.pixel_map[dimension-1],self.id_num))
		# left column
		edges.append(Edge(left_column,self.id_num))
		return edges
	
	def to_str(self):
		pixel_map_str = "".join(self.pixel_map[0])
		for i in range(1,len(self.pixel_map)):
			pixel_map_str = pixel_map_str + '\n'+''.join(pixel_map[i])
		return pixel_map_str

	def __repr__(self):
		return (str(self.id_num) + "\n" + self.to_str()) + "\n"

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		pixel_map = []
		tile_set = []
		id_num = 0
		for line in input_list:
			if(line.rstrip()==""):
				tile_set.append(Tile(id_num,pixel_map))
				pixel_map = []
				id_num = 0
			elif(line.rstrip()[0:4]=="Tile"):
				id_str = line.rstrip().split(' ')[1]
				id_num = int(id_str[0:(len(id_str)-1)])
			else:
				pixel_map.append(list(line.rstrip()))
		tile_set.append(Tile(id_num,pixel_map))

		corners = []
		#find the tiles that have two edges with no matches. those are the corner tiles. 
		for i in range(0,len(tile_set)):
			tile1 = tile_set[i]
			for j in range(i+1,len(tile_set)):
				tile2 = tile_set[j]
				for k in range(0,4):
					if(tile1.edges[k] in tile2.edges):
						edge_index = tile2.edges.index(tile1.edges[k])
						tile1.edges[k].add_neighbor(tile2.edges[edge_index])
						tile2.edges[edge_index].add_neighbor(tile1.edges[k])
		
		output = ""
		edges = []
		for i in range(0,len(tile_set)):
			edge = []
			for j in range(0,4):
				output = output + str(len(tile_set[i].edges[j].neighbors)) + " "
				edge.append(tile_set[i].edges[j].edge)
			edges.append(edge)
			output = output + "\n"
		print(output)
		print(edges)
