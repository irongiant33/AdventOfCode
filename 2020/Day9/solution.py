import copy
INPUT_FILE_NAME = "input.txt"
PREAMBLE_LEN = 25

def find_encryption_weakness(input_list,sum_check, sum_index,preamble_len):
	for i in range(0,sum_index-preamble_len):
		preamble = input_list[i:(i+preamble_len)]
		if(sum(preamble) == sum_check):
			return (min(preamble) + max(preamble))
	return -1

def preamble_check(preamble,index,sum_check):
	preamble_copy = copy.deepcopy(preamble)
	max1 = max(preamble)
	preamble_copy.remove(max1)
	max2 = max(preamble_copy)
	min1 = min(preamble)
	preamble_copy.remove(min1)
	min2 = min(preamble_copy)
	lowerbound = min1 + min2
	upperbound = max1 + max2
	if(sum_check < lowerbound or sum_check > upperbound):
		return sum_check
	else:
		found_flag = sum_check
		for i in range(0,25):
			for j in range(i+1,25):
				if(i != j and preamble[i]+preamble[j]==sum_check):
					found_flag = -1
					break
			if(found_flag == -1):
				break
	return found_flag

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		for i in range(0,len(input_list)):
			input_list[i] = int(input_list[i].rstrip())
		index = 0
		sum_index = 0
		preamble = input_list[0:PREAMBLE_LEN]
		flag = preamble_check(preamble,index,input_list[PREAMBLE_LEN])
		while(flag == -1):
			index = index + 1
			sum_index = PREAMBLE_LEN+index
			preamble = input_list[index:(sum_index)]
			flag = preamble_check(preamble,input_list[index:(sum_index)],input_list[sum_index])
		print("(part 1): the breakpoint for the preamble was: " + str(flag))

		preamble_len = 2
		part2_flag = find_encryption_weakness(input_list,flag,sum_index,preamble_len)
		while(part2_flag == -1):
			preamble_len = preamble_len + 1
			part2_flag = find_encryption_weakness(input_list,flag,sum_index,preamble_len)
		print("(part 2): the encryption weakness is: "+str(part2_flag))