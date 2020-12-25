INPUT_FILE_NAME = "input.txt"

def get_str(rules,pointer):
	rule_set = rules[pointer].split(' | ')
	if(rule_set[0][1].isalpha()):
		return rule_set[0][1]
		
	outputs = []
	for i in range(0,len(rule_set)):
		outputs.append([])
		pointers = rule_set[i].split(' ')
		for p in pointers:
			outputs[i].append(get_str(rules,int(p)))
	return outputs

def get_next_str(output):
	if(type(output) == type('string')):
		return output
	else:
		return get_next_str(output[0])

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()

		#create list of rules and inputs
		rules = []
		inputs = []
		switch = -1
		for line in input_list:
			if(line.rstrip() == ""):
				switch = 1
			elif(switch == -1):
				rules.append((line.rstrip().split(": "))[1])
			else:
				inputs.append(line.rstrip())

		# find all possible outputs
		outputs = []
		rule0 = rules[0].split(' ')
		for pointer in rule0:
			outputs.append(get_str(rules,int(pointer)))
		print(outputs)
		
		# count valid 
		num_valid = 0
		test_str = ""
		for output in outputs:
			test_str = test_str + get_next_str(output)
			
		
		print("(part 1): the number of valid inputs are: "+str(num_valid))
		