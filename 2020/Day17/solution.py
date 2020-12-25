INPUT_FILE_NAME = "input.txt"
NUM_CYCLES = 6

# add inactive borders to a state in dimension, row, and column.
# state is 3D list: 1st D = dimension (z direction), 2nd D = row (x direction), 3rd D = col (y direction)
def add_border(state):
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

def count_neighbors(state,indices):
	dim, row, col = indices[0],indices[1],indices[2]
	num_active = 0
	for i in range(dim-1,dim+2):
		for j in range(row-1,row+2):
			for k in range(col-1,col+2):
				if(state[i][j][k] == '#' and not (i == dim and j == row and k == col)):
					num_active = num_active + 1
	return num_active 

def propagate(state):
	new_state = add_border(state) # makes it easier to check neighbors
	updated_state = []
	num_dimensions = len(new_state)
	num_rows = len(new_state[0])
	for i in range(1,num_dimensions-1):
		dimension = []
		for j in range(1,num_rows-1):
			row = []
			for k in range(1,num_rows-1):
				num_active = count_neighbors(new_state,[i,j,k])
				if(num_active == 3):
					row.append('#')
				elif(new_state[i][j][k]=='#' and num_active == 2):
					row.append('#')
				else:
					row.append('.')
			dimension.append(row)
		updated_state.append(dimension)
	return updated_state

def count_num_active(state):
	num_active = 0
	num_dimensions = len(state)
	num_rows = len(state[0])

	for i in range(0,num_dimensions):
		for j in range(0,num_rows):
			for k in range(0,num_rows):
				if(state[i][j][k]=='#'):
					num_active = num_active + 1
	return num_active

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()

		# create initial state that is 1 dimensional
		initial_state = [[]]
		for line in input_list:
			initial_state[0].append(list(line.rstrip()))

		for cycle in range(0,NUM_CYCLES):
			# add border
			new_state = add_border(initial_state)
			initial_state = None

			# propagate state
			initial_state = propagate(new_state)
		
		#count active states
		num_active = count_num_active(initial_state)
		print("(part 1): the number of active states after "+str(NUM_CYCLES)+" cycles is "+str(num_active))		
