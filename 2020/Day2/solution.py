INPUT_FILE_NAME = "input.txt"

def get_input_list():
	input_file = open(INPUT_FILE_NAME,"r")
	input_file_list = []
	for line in input_file:
		# parse the parameters on each line
		line_parameters = line.split(" ")
		letter_value = line_parameters[1][0]
		letter_range = line_parameters[0].split("-")
		
		#add those parameters to a list
		parameter_list = []
		for value in letter_range:
			parameter_list.append(int(value))
		parameter_list.append(letter_value)
		parameter_list.append(line_parameters[2])
		
		#add the list of parameters to your input file list
		input_file_list.append(parameter_list)
		
	input_file.close()
	return input_file_list
	
def get_num_valid_passwords_part_one(input_list):
	num_valid = 0
	for value in input_list:
		password = value[3]
		letter = value[2]
		lowerbound = value[0]
		upperbound = value[1]
		
		num_occurences = password.count(letter)
		if(num_occurences >= lowerbound and num_occurences <= upperbound):
			num_valid = num_valid + 1
			
	return num_valid
	
def get_num_valid_passwords_part_two(input_list):
	num_valid = 0
	for value in input_list:
		password = value[3]
		letter = value[2]
		lower_index = value[0]-1
		upper_index = value[1]-1
		
		lower_check = (password[lower_index] == letter)
		upper_check = (password[upper_index] == letter)
		
		# XOR condition
		if((lower_check and not upper_check) or (not lower_check and upper_check)):
			num_valid = num_valid + 1
		
	return num_valid

if __name__ == "__main__":
	input_list = get_input_list()
	num_valid1 = get_num_valid_passwords_part_one(input_list)
	num_valid2 = get_num_valid_passwords_part_two(input_list)
	print("The number of valid passwords for Part 1 is: " + str(num_valid1))
	print("The number of valid passwords for Part 2 is: " + str(num_valid2))
