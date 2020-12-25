INPUT_FILE_NAME = "input.txt"

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		earliest_departure = int(input_list[0].rstrip())
		bus_id = (input_list[1].rstrip()).split(',')
		minimum_state = [9999999,9999999]
		for id in bus_id:
			try:
				id_num = int(id)
				num_loops = (earliest_departure//id_num)+1
				wait_time = num_loops*id_num - earliest_departure
				if(wait_time < minimum_state[1]):
					minimum_state[0] = id_num
					minimum_state[1] = wait_time
			except:
				pass
		print("(part 1) the bus ID times the wait time is: "+str(minimum_state[0]*minimum_state[1]))