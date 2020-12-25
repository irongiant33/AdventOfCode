INPUT_FILE_NAME = "input.txt"
PART1 = 2020
PART2 = 30000000

def solve(limit,input_list):
	starting_numbers = (input_list[0].rstrip()).split(',')
	numbers = []
	while(len(starting_numbers) > 0):
		numbers.insert(0,starting_numbers.pop(0))
	next_number = '0'
	count = len(numbers)
	while(count < limit):
			first_index = -1
			try:
				first_index = numbers.index(next_number)
			except:
				pass
			numbers.insert(0,next_number)

			if(first_index == -1):
				next_number='0'
			else:
				next_number=str(first_index+1)

			count = count + 1
	return numbers[0]

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		part1 = solve(PART1,input_list)
		print("(part1): the "+str(PART1)+"th number spoken will be: " + str(part1))
		part2 = solve(PART2,input_list)
		print("(part2): the "+str(PART2)+"th number spoken will be: " + str(part2))