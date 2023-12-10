import re
from math import gcd

def navigate_to_node(curr_node, instructions, node_dict, end_node="ZZZ"):
    instruction_index = 0
    num_instructions = len(instructions)
    num_steps = 0
    while(curr_node[-len(end_node):] != end_node):
        curr_node = node_dict[curr_node][instructions[instruction_index]]
        instruction_index = (instruction_index + 1) % num_instructions
        num_steps += 1
    return num_steps

def part1(infilename):
    nodepattern = "[A-Z]+"
    node_dict = {}
    instructions = []
    instruction_map = {"R":1, "L":0}
    curr_node = "AAA" 
    with open(infilename) as infile:
        instructions_str = list(infile.readline().rstrip())
        instructions = [instruction_map[item] for item in instructions_str]
        for line in infile:
            node_matches = re.findall(nodepattern, line.rstrip())
            if(node_matches):
                node, left, right = node_matches
                node_dict[node] = (left, right)
                if(curr_node == ""):
                    curr_node = node
    return navigate_to_node(curr_node, instructions, node_dict)

def lcm(a, b):
    return abs(a * b) // gcd(a, b)

def find_lcm_of_set(numbers):
    if len(numbers) < 2:
        raise ValueError("At least two numbers are required to find the LCM.")

    result_lcm = numbers[0]
    
    for i in range(1, len(numbers)):
        result_lcm = lcm(result_lcm, numbers[i])

    return result_lcm

def part2(infilename):
    nodepattern = "[A-Z0-9]+"
    node_dict = {}
    debug = True
    instructions = []
    instruction_map = {"R":1, "L":0}
    curr_nodes = [] 
    with open(infilename) as infile:
        instructions_str = list(infile.readline().rstrip())
        instructions = [instruction_map[item] for item in instructions_str]
        for line in infile:
            node_matches = re.findall(nodepattern, line.rstrip())
            if(node_matches):
                node, left, right = node_matches
                node_dict[node] = (left, right)
                if(node[-1] == "A"):
                    curr_nodes.append(node)
    distances = []
    for node in curr_nodes:
        distance = navigate_to_node(node, instructions, node_dict, end_node="Z")
        distances.append(distance)
    return find_lcm_of_set(distances)

if __name__=="__main__":
    part1ans = part1("input.txt")
    print(f"The answer to part 1 is: {part1ans}")
    
    part2ans = part2("input.txt")
    print(f"The answer to part 2 is: {part2ans}")