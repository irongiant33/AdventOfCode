import math

INPUT_FILE_NAME = "input.txt"
INITIAL_STATE = [0,0,0] #(X,Y,theta) where 0 degrees is east,180 is west. 
DEG_TO_RAD = math.pi/180

def find_position(navigation_instructions,debug):
	state = INITIAL_STATE
	for instruction in navigation_instructions:
		command = instruction[0]
		value = instruction[1]
		if(command == "F"):
			state[0] = state[0] + int(value*math.cos(state[2]*DEG_TO_RAD))
			state[1] = state[1] + int(value*math.sin(state[2]*DEG_TO_RAD))
		elif(command == "L"):
			state[2] = state[2] + value
			if(state[2]>180):
				state[2] = state[2]-360
		elif(command == "R"):
			state[2] = state[2] - value
			if(state[2]<-180):
				state[2] = state[2] + 360
		elif(command == "N"):
			state[1] = state[1] + value
		elif(command == "E"):
			state[0] = state[0] + value
		elif(command == "S"):
			state[1] = state[1] - value
		elif(command == "W"):
			state[0] = state[0] - value
		if(debug):
			print(state)
	return state


if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()

		#create navigation instruction input
		navigation_instructions = []
		for line in input_list:
			instruction = line.rstrip()
			command = instruction[0]
			value = int(instruction[1:])
			navigation_instructions.append((command,value))

		#find current position
		state = find_position(navigation_instructions,False)

		#calculate manhattan distance
		manhattan_distance = abs(state[0])+abs(state[1])
		print("(part 1) the manhattan distance is: "+str(manhattan_distance))
		