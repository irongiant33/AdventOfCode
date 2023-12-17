import re

"""
@brief if the list has all the same values, return True
"""
def check_constant(input_list):
    first = input_list[0]
    for item in input_list:
        if(first != item):
            return False
    return True

def derivative(input_list):
    if(len(input_list) == 0):
        return input_list
    derivative_list = []
    for i in range(1, len(input_list)):
        derivative_list.append(input_list[i] - input_list[i - 1])
    return derivative_list

def integral(initial_value, input_list):
    integral_list = [initial_value]
    for i in range(len(input_list)):
        integral_list.append(integral_list[i] + input_list[i])
    return integral_list

def part1(infilename):
    line_pattern = "([-]?\d+)\s*"
    sum = 0
    debug = False
    debugcount = 0
    with open(infilename) as infile:
        for line in infile:
            line_find = re.findall(line_pattern, line.rstrip())
            line_nums = list(map(int, line_find))
            initial_values = []
            while(not check_constant(line_nums)):
                initial_values.insert(0, line_nums[0])
                if(debug):
                    print(f"derivative {len(initial_values)}: {line_nums}")
                derivative_list = derivative(line_nums)
                line_nums = derivative_list
            line_nums.append(line_nums[0]) # extend the list by its constant element
            for i in range(len(initial_values)):
                if(debug):
                    print(f"integral {i+1}: {line_nums}")
                integral_list = integral(initial_values[i], line_nums)
                line_nums = integral_list
            sum += line_nums[-1]
            debugcount += 1
            if(debug and debugcount > 3):
                break
            elif(debug):
                print(f"final: {line_nums[-1]} {sum}")
    return sum

def part2(infilename):
    line_pattern = "([-]?\d+)\s*"
    sum = 0
    debug = False
    debugcount = 0
    with open(infilename) as infile:
        for line in infile:
            line_find = re.findall(line_pattern, line.rstrip())
            line_nums = list(map(int, line_find))[-1::-1]
            initial_values = []
            while(not check_constant(line_nums)):
                initial_values.insert(0, line_nums[0])
                if(debug):
                    print(f"derivative {len(initial_values)}: {line_nums}")
                derivative_list = derivative(line_nums)
                line_nums = derivative_list
            line_nums.append(line_nums[0]) # extend the list by its constant element
            for i in range(len(initial_values)):
                if(debug):
                    print(f"integral {i+1}: {line_nums}")
                integral_list = integral(initial_values[i], line_nums)
                line_nums = integral_list
            sum += line_nums[-1]
            debugcount += 1
            if(debug and debugcount > 3):
                break
            elif(debug):
                print(f"final: {line_nums[-1]} {sum}")
    return sum

if __name__=="__main__":
    part1ans = part1("input.txt")
    print(f"answer to part 1 is: {part1ans}")

    part2ans = part2("input.txt")
    print(f"answer to part 2 is: {part2ans}")