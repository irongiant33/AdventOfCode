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
		valid_tickets = []
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
				valid_tickets.append(numbers)
			sum_invalid = sum_invalid + num_invalid
		success_rate = num_valid_tickets/(len(input_list)-nearby_index)
		print("(part 1): the error rate is: "+str(sum_invalid))

		fields = []
		count = 0
		line = input_list[count].rstrip().split(' ')
		while(len(line) > 1):
			left = line[-3].split('-')
			left_bound = (int(left[0]),int(left[1]))
			right = line[-1].split('-')
			right_bound = (int(right[0]),int(right[1]))
			fields.append([left_bound,right_bound])
			count = count + 1
			line = input_list[count].rstrip().split(' ')
		
		added_fields = []
		mapping = {}
		field_num = -1
		while(len(added_fields) < len(valid_tickets[0])):
			field_num = field_num + 1
			if(field_num == len(valid_tickets[0])):
				field_num = 0
			field_indices = list(range(0,len(fields)))
			for added in added_fields:
				field_indices.remove(added)
			for ticket_num in range(0,len(valid_tickets)):
				field_val = int(valid_tickets[ticket_num][field_num])
				for field_index in field_indices:
					left = fields[field_index][0]
					right = fields[field_index][1]
					right_condition =  (field_val >= right[0] and field_val <= right[1])
					left_condition = (field_val >= left[0] and field_val <= left[1])
					if(not (left_condition or right_condition)):
						field_indices.remove(field_index)
						break
			if(len(field_indices) == 1):
				added_fields.append(field_indices[0])
				mapping[field_indices[0]] = field_num
		
		product = 1
		my_ticket_index = input_list.index('your ticket:\n')+1
		my_ticket = input_list[my_ticket_index].split(',')
		for i in range(0,6):
			product = product * int(my_ticket[mapping[i]])
		print("(part 2) the product of all destination fields on my ticket is: " + str(product))