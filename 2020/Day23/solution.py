INPUT_FILE_NAME = "input.txt"

NUM_MOVES = 10

def play_game(cup_list):
	num_cups = len(cup_list)
	pointer = 0
	for i in range(0,NUM_MOVES):
		print(cup_list)

		grabbed_cups = []
		grab_cup_pointer = pointer + 1
		for j in range(0,3):
			if(grab_cup_pointer >= len(cup_list)):
				grab_cup_pointer = 0
			grabbed_cups.append(cup_list.pop(grab_cup_pointer))
		
		print(grabbed_cups)
		destination = int(cup_list[pointer]) - 1
		while(str(destination) in grabbed_cups):
			destination = destination - 1
			if(destination < 1):
				destination = 9
		print(destination)
		destination_pointer = cup_list.index(str(destination)) + 1
		index = 0
		while(len(grabbed_cups) > 0):
			cup_list.insert(destination_pointer + index, grabbed_cups.pop(0))
			index = index + 1
		pointer = pointer + 1
		if(pointer >= len(cup_list)):
			pointer = 0
	return cup_list


if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		cup_list = list(input_list[0])
		cup_list = play_game(cup_list)
		print(cup_list)