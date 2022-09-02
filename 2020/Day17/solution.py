INPUT_FILE_NAME = "input.txt"
NUM_CYCLES = 6

class Cube_3D():
	def __init__(self,state=[[]]):
		self.initial_state = state

	# add inactive borders to a state in dimension, row, and column.
	# state is 3D list: 1st D = dimension (z direction), 2nd D = row (x direction), 3rd D = col (y direction)
	def add_border(self,state):
		num_dimensions = len(state)
		num_row = len(state[0])
		period_row = list('.'*(num_row + 2))
		period_dimension = []
		for i in range(0,num_row + 2):
			period_dimension.append(period_row)

		new_state = [period_dimension]
		for i in range(0,num_dimensions):
			dimension = [period_row]
			for j in range(0,num_row):
				row = ['.']
				for k in range(0,num_row):
					row.append(state[i][j][k])
				row.append('.')
				dimension.append(row)
			dimension.append(period_row)
			new_state.append(dimension)
		new_state.append(period_dimension)
		return new_state

	def count_neighbors(self,state,indices):
		dim, row, col = indices[0],indices[1],indices[2]
		num_active = 0
		for i in range(dim-1,dim+2):
			for j in range(row-1,row+2):
				for k in range(col-1,col+2):
					if(state[i][j][k] == '#' and not (i == dim and j == row and k == col)):
						num_active = num_active + 1
		return num_active 

	def propagate(self,state):
		new_state = self.add_border(state) # makes it easier to check neighbors
		updated_state = []
		num_dimensions = len(new_state)
		num_rows = len(new_state[0])
		for i in range(1,num_dimensions-1):
			dimension = []
			for j in range(1,num_rows-1):
				row = []
				for k in range(1,num_rows-1):
					num_active = self.count_neighbors(new_state,[i,j,k])
					if(num_active == 3):
						row.append('#')
					elif(new_state[i][j][k]=='#' and num_active == 2):
						row.append('#')
					else:
						row.append('.')
				dimension.append(row)
			updated_state.append(dimension)
		return updated_state

	def count_num_active(self,state):
		num_active = 0
		num_dimensions = len(state)
		num_rows = len(state[0])

		for i in range(0,num_dimensions):
			for j in range(0,num_rows):
				for k in range(0,num_rows):
					if(state[i][j][k]=='#'):
						num_active = num_active + 1
		return num_active

class Cube_4D():
	def __init__(self,state=[[[]]]):
		# state is 4D list: 1st D = hyper (w direction), 2nd D = dimension (z direction), 3rd D = row (x direction), 4th D = col (y direction)
		self.initial_state = state

	# add inactive borders to a state in hyper, dimension, row, and column.
	def add_border(self,state):
		num_hyper = len(state)
		num_dimensions = len(state[0])
		num_row = len(state[0][0])
		period_row = list('.'*(num_row + 2))
		period_hyper = []
		for j in range(0,num_dimensions+2):
			period_dimension = []
			for i in range(0,num_row + 2):
				period_dimension.append(period_row)
			period_hyper.append(period_dimension)

		new_state = [period_hyper]
		for h in range(0,num_hyper):
			hyper = [period_dimension]
			for i in range(0,num_dimensions):
				dimension = [period_row]
				for j in range(0,num_row):
					row = ['.']
					for k in range(0,num_row):
						row.append(state[h][i][j][k])
					row.append('.')
					dimension.append(row)
				dimension.append(period_row)
				hyper.append(dimension)
			hyper.append(period_dimension)
			new_state.append(hyper)
		new_state.append(period_hyper)
		return new_state

	def count_neighbors(self,state,indices):
		hyp, dim, row, col = indices[0],indices[1],indices[2],indices[3]
		num_active = 0
		for h in range(hyp-1,hyp+2):
			for i in range(dim-1,dim+2):
				for j in range(row-1,row+2):
					for k in range(col-1,col+2):
						if(state[h][i][j][k] == '#' and not (h == hyp and i == dim and j == row and k == col)):
							num_active = num_active + 1
		return num_active 

	def propagate(self,state):
		new_state = self.add_border(state) # makes it easier to check neighbors
		updated_state = []
		num_hyper = len(new_state)
		num_dimensions = len(new_state[0])
		num_rows = len(new_state[0][0])
		for h in range(1,num_hyper-1):
			hyper = []
			for i in range(1,num_dimensions-1):
				dimension = []
				for j in range(1,num_rows-1):
					row = []
					for k in range(1,num_rows-1):
						num_active = self.count_neighbors(new_state,[h,i,j,k])
						if(num_active == 3):
							row.append('#')
						elif(new_state[h][i][j][k]=='#' and num_active == 2):
							row.append('#')
						else:
							row.append('.')
					dimension.append(row)
				hyper.append(dimension)
			updated_state.append(hyper)
		return updated_state

	def count_num_active(self,state):
		num_active = 0
		num_hyper = len(state)
		num_dimensions = len(state[0])
		num_rows = len(state[0][0])
		for h in range(0,num_hyper):
			for i in range(0,num_dimensions):
				for j in range(0,num_rows):
					for k in range(0,num_rows):
						if(state[h][i][j][k]=='#'):
							num_active = num_active + 1
		return num_active

	def __repr__(self):
		string = ""
		for h in range(0,len(self.initial_state)):
			for i in range(0,len(self.initial_state[0])):
				for j in range(0,len(self.initial_state[0][0])):
					string = string + "".join(self.initial_state[h][i][j]) + "\n"
				string = string + "\n"
			string = string + "\n"
		string = string + "\nEND"
		return string

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()

		# create initial state that is 1 dimensional
		part1_cube = Cube_3D()
		for line in input_list:
			part1_cube.initial_state[0].append(list(line.rstrip()))

		for cycle in range(0,NUM_CYCLES):
			# add border
			new_state = part1_cube.add_border(part1_cube.initial_state)
			part1_cube.initial_state = None

			# propagate state
			part1_cube.initial_state = part1_cube.propagate(new_state)

		
		#count active states
		num_active = part1_cube.count_num_active(part1_cube.initial_state)
		print("(part 1): the number of active states after "+str(NUM_CYCLES)+" cycles for a 3D cube is "+str(num_active))	

		part2_cube = Cube_4D()
		for line in input_list:
			part2_cube.initial_state[0][0].append(list(line.rstrip()))	

		for cycle in range(0,NUM_CYCLES):
			# add border
			new_state = part2_cube.add_border(part2_cube.initial_state)
			part2_cube.initial_state = [[[]]]

			# propagate state
			part2_cube.initial_state = part2_cube.propagate(new_state)
		
		#count active states
		num_active = part2_cube.count_num_active(part2_cube.initial_state)
		print("(part 2): the number of active states after "+str(NUM_CYCLES)+" cycles for a 4D cube is "+str(num_active))	

