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
		equation.insert(0,Value(str(solution)))
	return equation[0].value

def breakdown(line,start_index=0):
	equation = []
	operators = []
	i = start_index
	while(i < len(line)):
		if(line[i] == "("):
			[eq,op,i] = breakdown(line, i+1)
			sub_value = solve(eq,op)
			equation.append(Value(str(sub_value)))
		elif(line[i] == ")"):
			return [equation, operators,i]
		elif(line[i] == "*" or line[i] == "+"):
			operators.append(line[i])
		elif(line[i].isnumeric()):
			equation.append(Value(line[i]))
		
		i = i + 1
	return [equation,operators,i]

class Value:
	def __init__(self,line):
		self.value = None
		if(line.isnumeric()):
			self.value = int(line)
		else:
			[equation,operators] = breakdown(line)
			self.value = solve(equation,operators)
	
	def __repr__(self):
		return str(self.value)

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		sum_val = 0
		for line in input_list:
			[equation, operators, index] = breakdown(line.rstrip())
			num = solve(equation, operators)
			sum_val = sum_val + num
		print("(part 1) the sum of all the equations is: " + str(sum_val))
