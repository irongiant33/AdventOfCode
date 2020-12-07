INPUT_FILE_NAME = "input.txt"

def get_input_list():
	input_file = open(INPUT_FILE_NAME)
	input_file_list = []
	for line in input_file:
		input_file_list.append(line.rstrip())
	return input_file_list

if __name__ == "__main__":
	input_list = get_input_list()
