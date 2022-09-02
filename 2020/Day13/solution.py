INPUT_FILE_NAME = "input.txt"

def find_index(id_num, bus_id_num, offset_lists, time_offsets,first_index=-1,jump=-1):
	index = bus_id_num.index(id_num)
	offset_list = offset_lists[index]
	if(first_index==-1):
		first_index = offset_list.index(time_offsets[index])
		return find_index(bus_id_num[index+1],bus_id_num,offset_lists,time_offsets,first_index,id_num)
	else:
		special_offset = [offset_list[first_index % id_num]]
		new_index = first_index
		for i in range(1,id_num):
			new_index = (new_index + jump) % id_num
			special_offset.append(offset_list[new_index])
		if(time_offsets[index] >= id_num):
			# assume that the match case does not occur at t < max(bus_id_num)
			time_offsets[index] = time_offsets[index] % id_num
		next_index = 0
		next_index = special_offset.index(time_offsets[index]) * jump
		if(index + 1 == len(bus_id_num)):
			return first_index + next_index
		else:
			jump = jump*len(special_offset)
			return find_index(bus_id_num[index+1],bus_id_num,offset_lists,time_offsets,first_index + next_index,jump)

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		earliest_departure = int(input_list[0].rstrip())
		bus_id = (input_list[1].rstrip()).split(',')
		bus_id_num = []
		minimum_state = [9999999,9999999]
		for id in bus_id:
			try:
				id_num = int(id)
				bus_id_num.append(id_num)
				num_loops = (earliest_departure//id_num)+1
				wait_time = num_loops*id_num - earliest_departure
				if(wait_time < minimum_state[1]):
					minimum_state[0] = id_num
					minimum_state[1] = wait_time
			except:
				pass
		print("(part 1) the bus ID times the wait time is: "+str(minimum_state[0]*minimum_state[1]))

		t = 0
		original = bus_id_num.pop(0)
		offset_lists = []
		time_offsets = []
		for id_num in bus_id_num:
			time_offset = bus_id.index(str(id_num))
			time_offsets.append(time_offset)
			multiplied_list = list(range(0,original*id_num+id_num,id_num))
			original_list = list(range(0,original*id_num,original))
			offset_list = []
			compare = multiplied_list.pop(0)
			for i in range(0,id_num):
				product = original_list[i]
				while(compare < product):
					compare = multiplied_list.pop(0)
				offset_list.append(compare-product)
			offset_lists.append(offset_list)

		first_time = original * find_index(bus_id_num[0], bus_id_num, offset_lists, time_offsets)
		print("(part 2): the first time at which the buses depart at subsequent times is: " + str(first_time))
			