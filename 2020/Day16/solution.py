import re

INPUT_FILE_NAME = "input.txt"

def sort_bounds(bounds):
	new_bounds = []
	bounds_len = len(bounds)
	for i in range(0,bounds_len):
		min_num = 9999999999
		min_bound = []
		for j in range(0,len(bounds)):
			if(int(bounds[j][0]) < min_num):
				min_bound = bounds[j]
				min_num = int(min_bound[0])
		new_bounds.append(min_bound)
		bounds.remove(min_bound)
	return new_bounds

def compact_bounds(bounds):
	index = 0
	while(index < len(bounds)-1):
		if(int(bounds[index][1]) < int(bounds[index+1][0])):
			index = index + 1
		else:
			lower = bounds[index][0]
			upper = bounds[index+1][1]
			if(int(bounds[index][1]) > int(bounds[index+1][1])):
				upper = bounds[index][1]
			bounds.remove(bounds[index])
			bounds.remove(bounds[index])
			bounds.insert(index,[lower, upper])
	return bounds

def set_bounds(input_list):
	index = 0
	bounds = []
	while(input_list[index] != '\n'):
		line = input_list[index].rstrip()
		params = line.split(': ')
		ranges = params[1].split(' or ')
		bound = [i.split('-') for i in ranges]
		[bounds.append(b) for b in bound]
		index = index + 1
	new_bounds = sort_bounds(bounds)
	final_bounds = compact_bounds(new_bounds)
	return final_bounds

def in_list(n,bounds):
	in_list = False
	for b in bounds:
		if(int(n) >= int(b[0]) and int(n) <= int(b[1])):
			in_list = True
			break
	return in_list

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		bounds = set_bounds(input_list)
		nearby_index = input_list.index('nearby tickets:\n')+1
		num_valid_tickets = 0
		sum_invalid = 0
		for i in range(nearby_index,len(input_list)):
			line = input_list[i].rstrip()
			numbers = line.split(',')
			num_valid = 0
			num_invalid = 0
			for n in numbers:
				if(in_list(n,bounds)):
					num_valid = num_valid+1
				else:
					num_invalid = num_invalid + int(n)
			if(num_valid == len(numbers)):
				num_valid_tickets = num_valid_tickets + 1
			sum_invalid = sum_invalid + num_invalid
		success_rate = num_valid_tickets/(len(input_list)-nearby_index)
		print("(part 1): the error rate is: "+str(sum_invalid))