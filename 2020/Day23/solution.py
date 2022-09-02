#!/usr/bin/python3

INPUT_FILE_NAME = "input.txt"

NUM_MOVES = 10000000
CUP_LIST_LEN = 1000000

CUP_DICT = dict()
PART1 = False
DEBUG = False

class Cup:
	def __init__(self, value, next_val):
		self.value = value
		self.next = next_val

	def __repr__(self):
		return f"Value: {self.value} Next: {self.next}"

def play_game(first_cup):
	grabbed_cup_vals = [0, 0, 0]
	dict_len = len(CUP_DICT.keys())
	for i in range(0,NUM_MOVES):
		if(DEBUG): print(f"Move {i}")

		grabbed_cup_vals[0] = first_cup.next
		grabbed_cup_vals[1] = CUP_DICT[grabbed_cup_vals[0]].next
		grabbed_cup_vals[2] = CUP_DICT[grabbed_cup_vals[1]].next

		if(DEBUG): print(f"Grabbed: {grabbed_cup_vals}")

		first_cup.next = CUP_DICT[grabbed_cup_vals[2]].next
		destination_value = (((first_cup.value - 1) - 1) % dict_len) + 1
		while(destination_value in grabbed_cup_vals):
			destination_value = (((destination_value - 1) - 1) % dict_len) + 1

		if(DEBUG): print(f"Destination: {destination_value}")
		
		destination_cup = CUP_DICT[destination_value]
		temp_val = destination_cup.next
		destination_cup.next = grabbed_cup_vals[0]
		CUP_DICT[grabbed_cup_vals[2]].next = temp_val

		first_cup = CUP_DICT[first_cup.next]

		if(DEBUG):
			repr = ""
			cup = first_cup
			for i in range(9):
				repr += str(cup.value)
				cup = CUP_DICT[cup.next]
			print(repr)
			print()


if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		cup_list_str = list(input_list[0])
		first_cup = int(cup_list_str[0])
		last_cup = None

		for i in range(len(cup_list_str) - 1):
			val = int(cup_list_str[i])
			CUP_DICT[val] = Cup(val, int(cup_list_str[i + 1]))
		
		if(PART1):
			CUP_DICT[int(cup_list_str[-1])] = Cup(int(cup_list_str[-1]), first_cup)
		else:
			for i in range(8, CUP_LIST_LEN):
				if(i < 8):
					val = int(cup_list_str[i])
					CUP_DICT[val] = Cup(val, int(cup_list_str[i + 1]))
				elif(i == 8):
					val = int(cup_list_str[i])
					CUP_DICT[val] = Cup(val, 10)
				elif(i > 9):
					CUP_DICT[i] = Cup(i, i + 1)
			CUP_DICT[CUP_LIST_LEN] = Cup(CUP_LIST_LEN, first_cup)

		play_game(CUP_DICT[first_cup])

		if(PART1):
			part1_ans = ""
			print_cup = CUP_DICT[CUP_DICT[1].next]
			for i in range(8):
				part1_ans += str(print_cup.value)
				print_cup = CUP_DICT[print_cup.next]
			print(part1_ans)
		else:
			cup1 = CUP_DICT[1]
			next_cup = CUP_DICT[cup1.next]
			next_next_cup = CUP_DICT[next_cup.next]
			print(f"Part 2 answer is: {next_cup.value * next_next_cup.value}")