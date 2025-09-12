import sys
import re

debug = False

"""
@brief counts how much o f the matrix is "on" after processing commands
@param commands: list of commands in format [x, [a, b], [c,d]] where x is
                 action, [a,b] and [c,d] are coordinates such that
                 0 <= a,b,c,d < size, a <= c, b <= d. 0 <= x < 3, 0 represents
                 toggle, 1 represents on, 2 represents off
@param size: number of rows and columns in the matrix. All elements in matrix
             are initially off.
@param funcs : list of lambda functions for what to do with each command x.
               len(funcs) == 3.
"""
def count_lights(commands : list, size : int, funcs : list)->int:
    matrix = []
    for row in range(size):
        matrix.append([0]*size)
    if(debug):
        for row in matrix:
            print(row)
        print()
    func = lambda x: x ^ 1
    for command in commands:
        func = funcs[command[0]]
        row_start = command[1][0]
        row_stop  = command[2][0] + 1
        col_start = command[1][1]
        col_stop  = command[2][1] + 1
        if(debug):
            print(f"{command[0]} from {row_start}, {col_start} to {row_stop}, {col_stop}")
        for row_index in range(row_start, row_stop):
            if(debug):
                print(matrix[row_index][col_start:col_stop])
            matrix[row_index][col_start:col_stop] = list(map(func, matrix[row_index][col_start:col_stop]))
        if(debug):
            for row in matrix:
                print(row)
            print()
    light_count = 0
    for row in matrix:
        light_count += sum(row)
    return light_count

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day6.py input.txt")
        exit(1)
    keywords = ["toggle", "on", "off"]
    commands = []
    funcs = [lambda x: x ^ 1, lambda y: y | 1, lambda z: z & 0]
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            pattern_matches = re.findall("\\d+,\\d+", line.rstrip())
            command = [list(map(int, x.split(','))) for x in pattern_matches]
            for index, keyword in enumerate(keywords):
                if keyword in line:
                    command.insert(0, index) # insert the toggle/on/off case at beginning
                    commands.append(command)
    light_count = count_lights(commands, 1000, funcs)
    print(f'The answer to part 1 is {light_count}')

    funcs = [lambda x: x + 2, lambda y: y + 1, lambda z: z - (z != 0)]
    light_count = count_lights(commands, 1000, funcs)
    print(f"The answer to part 2 is {light_count}")
