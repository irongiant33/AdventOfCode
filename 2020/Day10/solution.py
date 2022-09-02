import math
INPUT_FILE_NAME = "input.txt"
DEVICE_DIFFERENCE = 3

def find_distribution(input_list):
	distribution = [0,0,0]
	differences = []
	input_list.insert(0,0)
	input_list.append(input_list[len(input_list)-1] + DEVICE_DIFFERENCE)
	for i in range(1,len(input_list)):
		difference = input_list[i] - input_list[i-1]
		differences.append(difference)
		distribution[difference-1] = distribution[difference-1]+1
	return [distribution, differences]

def find_removables(input_list, differences):
	removable = []
	for i in range(0,len(differences)-1):
		if(differences[i] + differences[i+1] <= 3):
			removable.append(input_list[i+1])
	return removable

def group_removables(removables):
	group=[removables[0]]
	groups=[]
	for i in range(1,len(removables)):
		if(removables[i] == removables[i-1]+1):
			group.append(removables[i])
		else:
			groups.append(group)
			group=[removables[i]]
	groups.append(group)
	return groups

def get_combinations(n):
	c = 1
	for r in range(0,n):
		c = c + math.factorial(n)/(math.factorial(r)*math.factorial(n-r))
	return int(c)

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		for i in range(0,len(input_list)):
			input_list[i] = int(input_list[i].rstrip())
		input_list.sort()
		[distribution, differences] = find_distribution(input_list)
		print("(part 1) the number of 1 differences multiplied by 3 differences is: "+str(distribution[0]*distribution[2]))
		removables = find_removables(input_list, differences)
		groups = group_removables(removables)
		combinations = 1
		# the total number of combinations is the product of the combinations of
		# the subgroups. This is because the sub-group arrangements are independent of one another
		for group in groups:
			# general equation for all combinations:
			# Sigma_{r=0}^{r=n}(n!/(r!(n-r)!)) where n = group size
			if(len(group) == 3):
				# you can do everything EXCEPT remove all members of the group
				# you could see it as Sigma_{r=0}^{r=n}(n!/(r!(n-r)!)) - 1 for n=3
				combinations = combinations * (get_combinations(len(group)) - 1)
			else:
				combinations = combinations * get_combinations(len(group))
		print("(part 2) the number of arrangements is: " + str(combinations))