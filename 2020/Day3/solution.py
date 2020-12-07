INPUT_FILE_NAME = "input.txt"

def read_input_file():
	input_file = open(INPUT_FILE_NAME,"r")
	input_file_list = []
	for line in input_file:
		row = list(line)
		input_file_list.append(row)
		
	input_file.close()
	return input_file_list
	
def get_num_trees(tree_matrix,slope):
	RISE = slope[0]
	RUN = slope[1]
	num_trees = 0
	row_num = 0
	col_num = 0
	max_rows = len(tree_matrix)
	max_cols = len(tree_matrix[0])-1
	while(row_num < max_rows):
		if(tree_matrix[row_num][col_num] == '#'):
			num_trees = num_trees + 1
		row_num = row_num + RISE
		col_num = (col_num + RUN) % (max_cols)
	
	return num_trees

if __name__ == "__main__":
	tree_matrix = read_input_file()
	num_trees = get_num_trees(tree_matrix, [1,3])
	print("(Part 1): There are this many trees: " + str(num_trees))
	slopes = [[1,1],[1,3],[1,5],[1,7],[2,1]]
	product = 1
	for slope in slopes:
		product = product * get_num_trees(tree_matrix, slope)
	print("(Part 2): The product is: " + str(product))
