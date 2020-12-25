import copy

INPUT_FILE_NAME = "input.txt"

class Seat():
	def set_neighbors(self,state):
		self.neighbors = []
		num_occupied = 0
		for i in range(self.row-1,self.row+2):
				row = []
				for j in range(self.col-1,self.col+2):
					row.append(state[i][j].property)
					#don't count the cell itself
					if(state[i][j].property=="#" and not (i == self.row and j == self.col)):
						num_occupied = num_occupied + 1
				self.neighbors.append(row)
		self.num_occupied = num_occupied
		return num_occupied

	def __init__(self,seat_chart,row,col,prop=''):
		self.property=prop
		self.num_occupied = 0
		if(prop==''):
			self.property = seat_chart[row][col]
		self.neighbors = []
		self.row = row
		self.col = col

def empty_row(length):
	row = []
	for i in range(0,length):
		row.append(Seat(['.'],0,0))
	return row

def update_states(state):
	update_flag = -1
	new_state = []
	new_state.append(empty_row(len(state[0])))
	for i in range(1,len(state)-1):
		new_row = []
		new_row.append(Seat(['.'],0,0))
		for j in range(1,len(state[0])-1):
			seat = state[i][j]
			new_seat = Seat([],seat.row,seat.col,seat.property)
			num_occupied = seat.set_neighbors(state)
			if(seat.property == "L" and num_occupied == 0):
				new_seat.property = "#"
				update_flag = 0
			elif(seat.property == "#" and num_occupied >= 4):
				new_seat.property = "L"
				update_flag = 0
			new_row.append(new_seat)
		new_row.append(Seat(['.'],0,0))
		new_state.append(new_row)
	new_state.append(empty_row(len(state[0])))
	return [update_flag,new_state]

def count_states(last_state,display):
	count = 0
	for i in range(0,len(last_state)):
		row=[]
		for j in range(0,len(last_state[0])):
			row.append(last_state[i][j].property)
			if(last_state[i][j].property=="#"):
				count = count + 1
		if(display):
			print("".join(row))
	return count

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		num_cols = len(input_list[0].rstrip())
		num_rows = len(input_list)

		#create empty border to make neighbor checking easier
		seat_chart = []
		blank_row = "."*(num_cols+2)
		seat_chart.append(list(blank_row))
		for i in range(0,num_rows):
			new_row = ['.']
			old_row = list(input_list[i].rstrip())
			for j in range(0,num_cols):
				new_row.append(old_row[j])
			new_row.append('.')
			seat_chart.append(new_row)
		seat_chart.append(list(blank_row))

		#create state0 for the seat states
		seat_states = []
		state0 = []
		for row in range(0,len(seat_chart)):
			seat_row = []
			for col in range(0,len(seat_chart[0])):
				seat = Seat(seat_chart,row,col)
				seat_row.append(seat)
			state0.append(seat_row)
		seat_states.append(state0)

		#update the seat states
		update_flag = 0
		while(update_flag == 0):
			[update_flag,state] = update_states(seat_states[-1])
			seat_states.append(state)
			
		#count occupied seats:
		last_state = seat_states[-1]
		count = count_states(last_state,False)
		print("(part 1) The number of occupied seats in steady state is: "+str(count))