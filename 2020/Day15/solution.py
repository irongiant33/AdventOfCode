INPUT_FILE_NAME = "input.txt"
PART1 = 2020
PART2 = 30000000

def solve(limit,input_list):
	starting_numbers = (input_list[0].rstrip()).split(',')
	numbers = {}
	count = 0
	while(len(starting_numbers) > 0):
		numbers[int(starting_numbers.pop(0))] = count
		count = count + 1
	next_number = 0
	update = 0
	while(count < limit-1):
			if(next_number in numbers):
				update = count - numbers[next_number]
				numbers[next_number] = count
			else:
				update = 0
				numbers[next_number] = count
			next_number = update
			count = count + 1
	return next_number

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		part1 = solve(PART1,input_list)
		print("(part1): the "+str(PART1)+"th number spoken will be: " + str(part1))
		part2 = solve(PART2,input_list)
		print("(part2): the "+str(PART2)+"th number spoken will be: " + str(part2))