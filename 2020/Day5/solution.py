INPUT_FILE_NAME = "input.txt"
NUM_ROW_PARTITIONS = 7
NUM_COL_PARTITIONS = 3

class Seat:
	def get_id(self,flag):
		if(flag!=0):
			return self.id_num
			
		num_rows = 2**NUM_ROW_PARTITIONS
		num_cols = 2**NUM_COL_PARTITIONS
		row_val = [0,num_rows-1]
		col_val = [0,num_cols-1]

		for i in range(0,NUM_ROW_PARTITIONS):
			partition = num_rows/(2**(i+1))
			if(self.string[i] == 'F'):
				row_val[1] = row_val[1] - partition
			else:
				row_val[0] = row_val[0] + partition
				
		for j in range(NUM_ROW_PARTITIONS,NUM_ROW_PARTITIONS + NUM_COL_PARTITIONS):
			partition = num_cols/(2**(j-NUM_ROW_PARTITIONS+1))
			if(self.string[j] == "L"):
				col_val[1] = col_val[1] - partition
			else:
				col_val[0] = col_val[0] + partition
				
		#print(str(row_val) + " & " + str(col_val))
		id_num = 8*int(row_val[0]) + int(col_val[0])
		return id_num
	
	def __lt__(self,other):
		if(self.id_num < other.id_num):
			return True
		else:
			return False
		
	def __init__(self, string):
		self.string = string
		self.id_num = self.get_id(0)
		
def get_input_list():
	input_file = open(INPUT_FILE_NAME)
	input_file_list = []
	for line in input_file:
		input_file_list.append(line.rstrip())
	return input_file_list
	
def get_seat_list(input_list):
	max_seat = Seat("FFFFFFFLLL")
	seat_id_list = []
	for seat_string in input_list:
		new_seat = Seat(seat_string)
		seat_id_list.append(new_seat)
		if(new_seat.id_num > max_seat.id_num):
			max_seat = new_seat
	
	return [seat_id_list,max_seat]
		
def find_my_seat_id(seat_list):
	seat_list.sort()
	my_id = []
	starting_id = seat_list[0].id_num
	for i in range(1,len(seat_list)):
		next_id = seat_list[i].id_num
		if(next_id == starting_id + 2):
			return starting_id+1
		starting_id = next_id
	
	return -1

if __name__ == "__main__":
	input_list = get_input_list()
	[seat_list,max_seat] = get_seat_list(input_list)
	print("(part1) The max seat ID is: " + str(max_seat.id_num))
	my_seat_id = find_my_seat_id(seat_list)
	print("(part2) My seat ID is: " + str(my_seat_id))
	
