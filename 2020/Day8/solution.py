INPUT_FILE_NAME = "input.txt"

def parse_input(input_list):
	parsed_input = []
	for input_value in input_list:
		sign = 1
		[command,value] = input_value.rstrip().split(" ")
		if(value[0] == "-"):
			sign = -1
		new_value = int(value[1:])
		parsed_input.append([command,sign,new_value])
	return parsed_input

def run_program(parsed_input):
	num_instructions = len(parsed_input)
	pointer_history = []
	pointer = 0
	accumulator = 0
	while(pointer < num_instructions):
		command = parsed_input[pointer][0]
		sign = parsed_input[pointer][1]
		value = parsed_input[pointer][2]
		if(command == "acc"):
			accumulator = accumulator + sign * value
			pointer = pointer + 1
		elif(command == "jmp"):
			pointer = pointer + sign * value
		else:
			pointer = pointer + 1
		if(pointer in pointer_history):
			return [pointer,accumulator]
		else:
			pointer_history.append(pointer)

	if(pointer == num_instructions):
		return [pointer,accumulator]
	return [pointer,accumulator]

def fix_program(parsed_input):
	for i in range(0,len(parsed_input)):
		command = parsed_input[i][0]
		pointer = 0
		if(command == "jmp"):
			parsed_input[i][0] = "nop"
			[pointer,accum_value] = run_program(parsed_input)
			parsed_input[i][0] = "jmp"

		elif(command == "nop"):
			parsed_input[i][0] = "jmp"
			[pointer,accum_value] = run_program(parsed_input)
			parsed_input[i][0] = "nop"

		# the parsed input file is 622 long
		if(pointer == len(parsed_input)):
			return accum_value
	return -1

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		parsed_input = parse_input(input_list)
		[flag1,accum_value] = run_program(parsed_input)
		print("(part 1) the accumulator value just before the infinite loop is: " + str(accum_value))
		accum_value2 = fix_program(parsed_input)
		print("(part 2) the accumulator value at the end of the program is: " + str(accum_value2))