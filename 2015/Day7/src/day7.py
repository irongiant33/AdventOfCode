'''
make the assumption that wires are only the output once in the instruction list
for example
123 -> a
the wire "a" can only be on the left side of an operator now.
'''
import sys
import re
import copy

DEBUG = False
NUM_BITS = 16

class Command:  
    def and_func(self):
        return int(self.lhs) & int(self.rhs)

    def or_func(self):
        return int(self.lhs) | int(self.rhs)

    def not_func(self):
        mask = (2**NUM_BITS)-1
        result = mask ^ int(self.rhs)
        if(DEBUG):
            print(f"NOT: {mask=}, {self.rhs=}, {result=}")
        return result 

    def lshift_func(self):
        mask = (2**NUM_BITS)-1
        result = mask & (int(self.lhs) << int(self.rhs))
        if(DEBUG):
            print(f"LSHIFT: {mask=}, {self.rhs=}, {result=}")
        return result

    def rshift_func(self):
        return int(self.lhs) >> int(self.rhs)

    def is_func(self):
        return int(self.rhs)

    """
    @param rhs (str): right hand side symbol
    @param output (str): symbol of output
    @param lhs (str): left hand side symbol
    @param func (function): function to operate on left and right hand side
    """
    def __init__(self, rhs: str, output: str, lhs=None, func_str="NOT"):
        function_dict = {"NOT":self.not_func, 
                         "AND":self.and_func,
                         "LSHIFT":self.lshift_func,
                         "RSHIFT":self.rshift_func,
                         "OR":self.or_func,
                         "IS":self.is_func}
        self.rhs = rhs
        self.lhs = lhs
        self.output = output
        self.func = function_dict[func_str]
        self.func_str = func_str

    def __repr__(self):
        if(self.lhs is not None):
            return f"{self.lhs} {self.func_str} {self.rhs} -> {self.output}"
        else:
            return f"{self.func_str} {self.rhs} -> {self.output}"

def solve_part1(commands: list, wire_dict: dict, end_wire='a'):
    commands_index = 0
    while(end_wire not in wire_dict):
        try:
            current_command = commands[commands_index]
        except:
            print(wire_dict)
            exit(1)
        # replace symbols with values if we have them
        if(current_command.lhs is not None and current_command.lhs in wire_dict):
            current_command.lhs = str(wire_dict[current_command.lhs])
        if(current_command.rhs in wire_dict):
            current_command.rhs = str(wire_dict[current_command.rhs])
        # if all symbols are known in the command, compute the result
        lhs_is_valid = current_command.lhs is None or current_command.lhs.isdigit()
        rhs_is_valid = current_command.rhs.isdigit()
        if(lhs_is_valid and rhs_is_valid):
            wire_dict[current_command.output] = current_command.func()
            commands.pop(commands_index)
        else:
            commands_index += 1
        if(len(commands) > 0):
            commands_index %= len(commands)
    return wire_dict[end_wire]

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day7.py input.txt")
        exit(1)
    wire_dict = {}
    commands = []
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            line_items = line.rstrip().split(' ')
            output_wire = line_items[-1]
            if(len(line_items[:-2]) == 1): # starting with a value
                try:    
                    wire_dict[output_wire] = int(line_items[0])
                except ValueError: # int conversion attempted on string
                    commands.append(Command(line_items[0], output_wire, func_str="IS"))
            elif(len(line_items[:-2]) == 2): # unary operation
                commands.append(Command(line_items[1], output_wire))
            elif(len(line_items[:-2]) == 3): # binary operation
                commands.append(Command(line_items[2], output_wire, line_items[0], line_items[1]))
            else: # unknown
                print(f'unknown input: {line}')
    if(DEBUG):
        print(commands)
        print(wire_dict)

    original_wire_dict = copy.copy(wire_dict)
    original_commands = copy.deepcopy(commands)
    # part 1
    ret_val = solve_part1(commands, wire_dict)
    print(f"Answer to part 1 is {ret_val}")

    if(DEBUG):
        print(wire_dict)

    # part 2
    original_wire_dict['b'] = str(ret_val)
    if(DEBUG):
        print(original_wire_dict)
        print(original_commands)
    ret_val = solve_part1(original_commands, original_wire_dict)
    print(f"Answer to part 2 is {ret_val}")
