INPUT_FILE_NAME = "input.txt"

def get_input_list()
	input_file = open(INPUT_FILE_NAME)
	input_file_list = []
	for line in input_file:
		input_file_list.append(line[0:(len(line)-1)])
	return input_file_list

if __name__ == "__main__":
	input_list = get_input_list()
