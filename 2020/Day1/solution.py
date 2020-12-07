import sys

SUM_VAL = 2020
INPUT_FILE_NAME = "input.txt"

def get_input_list():
	input_file = open(INPUT_FILE_NAME,"r")
	input_file_list = []
	for line in input_file:
		input_file_list.append(int(line))
	input_file.close()
	return input_file_list
	
def reduce_input_list(lowerbound, upperbound, input_list):
	reduced_list = []
	for value in input_list:
		if(value >= lowerbound and value <= upperbound):
			reduced_list.append(value)
	return reduced_list

def get_bounds(input_list, num_summed):
	upperbound = sys.maxsize
	lowerbound = -sys.maxsize - 1
	for i in range(0,num_summed - 1):
		upperbound = SUM_VAL - min(input_list)
		lowerbound = SUM_VAL - max(input_list)
		input_list.remove(max(input_list))
		input_list.remove(min(input_list))
	return [lowerbound, upperbound]

def get_part_one_answer(input_list):
	[lowerbound, upperbound] = get_bounds(input_list, 2)
	reduced_input_list = reduce_input_list(lowerbound,upperbound,input_list)
	input_list_size = len(reduced_input_list)
	
	for i in range(0,input_list_size):
		value1 = reduced_input_list[i]
		for j in range(i+1,input_list_size):
			value2 = reduced_input_list[j]
			if(value1 + value2 == SUM_VAL):
				product = value1 * value2
				print("(Part 1) The answer is: " + str(product))
				break
				
def get_part_two_answer(input_list):
	[lowerbound, upperbound] = get_bounds(input_list, 3)
	reduced_input_list = reduce_input_list(lowerbound,upperbound,input_list)
	input_list_size = len(reduced_input_list)
	
	for i in range(0,input_list_size):
		value1 = reduced_input_list[i]
		for j in range(i+1,input_list_size):
			value2 = reduced_input_list[j]
			for k in range(j+1, input_list_size):
				value3 = reduced_input_list[k]
				if(value1 + value2 + value3 == SUM_VAL):
					product = value1 * value2 * value3
					print("(Part 2) The answer is: " + str(product))
					break
	
	print("All done!")
					
if __name__ == "__main__":
	input_list = get_input_list()
	get_part_one_answer(input_list)
	get_part_two_answer(input_list)
		
