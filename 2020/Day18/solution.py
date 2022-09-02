INPUT_FILE_NAME = "input.txt"

def solve(equation, operators):
	for i in range(0,len(operators)):
		solution = 0
		if(operators[i] == "+"):
			solution = equation[0].value + equation[1].value
		else:
			solution = equation[0].value * equation[1].value
		equation.pop(0)
		equation.pop(0)
		equation.insert(0,Value(str(solution),False))
	return equation[0].value

def advanced_solve(equation, operators):
	new_equation = []
	new_operators = []
	for i in range(0,len(operators)):
		solution = 0
		if(operators[i] == "+"):
			solution = solve([equation.pop(0), equation.pop(0)],["+"])
			equation.insert(0,Value(str(solution),True))
		else:
			new_equation.append(equation.pop(0))
			new_operators.append("*")
	new_equation.append(equation.pop(0))
	return solve(new_equation,new_operators)

def breakdown(line,is_part2,start_index=0):
	equation = []
	operators = []
	i = start_index
	while(i < len(line)):
		if(line[i] == "("):
			[eq,op,i] = breakdown(line,is_part2, i+1)
			sub_value = 0
			if(is_part2):
				sub_value = advanced_solve(eq,op)
			else:
				sub_value = solve(eq,op)
			equation.append(Value(str(sub_value),is_part2))
		elif(line[i] == ")"):
			return [equation, operators,i]
		elif(line[i] == "*" or line[i] == "+"):
			operators.append(line[i])
		elif(line[i].isnumeric()):
			equation.append(Value(line[i],is_part2))
		
		i = i + 1
	return [equation,operators,i]

class Value:
	def __init__(self,line,is_part2):
		self.value = None
		self.is_part2 = is_part2
		if(line.isnumeric()):
			self.value = int(line)
		else:
			[equation,operators] = breakdown(line,is_part2)
			if(is_part2):
				self.value = advanced_solve(equation,operators)
			else:
				self.value = solve(equation,operators)
	
	def __repr__(self):
		return str(self.value)

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		sum_val = [0,0]
		for line in input_list:
			input_line = line.rstrip()
			[equation1, operators1, index] = breakdown(input_line,False)
			[equation2, operators2, index] = breakdown(input_line,True)
			part1 = solve(equation1, operators1)
			part2 = advanced_solve(equation2,operators2)
			sum_val[0] = sum_val[0] + part1
			sum_val[1] = sum_val[1] + part2
		print("(part 1) the sum of all the equations is: " + str(sum_val[0]))
		print("(part 2) the sum of all the equations is: " + str(sum_val[1]))
