import re
import sys

DEBUG = True

def solve_puzzle(num_loops, input_string):
    cache = {}
    for i in range(num_loops):
        output_string = ""
        index = 1
        prev_char = input_string[0]
        while(index <= len(input_string)):
            count = 1
            while(index < len(input_string) and input_string[index] == prev_char ):
                index += 1
                count += 1
            result = f"{count}{prev_char}"
            output_string += result
            if(index < len(input_string)):
                prev_char = input_string[index]
            index += 1
            if(DEBUG):
                print(f"{i=}, {index=}, {input_string=}, {output_string=}")
        if(DEBUG):
            print(f"assigning {output_string} to output string")
        input_string = output_string
    return len(input_string)

def solve_puzzle_regex(num_loops ,input_string):
    pattern = r"((.)\2*)"
    cache = {}
    for i in range(num_loops):
        matches = re.findall(pattern, input_string)
        output_string = ""
        for match in matches:
            result = ""
            if match[0] in cache:
                result = cache[match[0]]
            else:
                result = f"{len(match[0])}{match[1]}"
                cache[match[0]] = result
            output_string += result
        input_string = output_string
    if(DEBUG):
        print(f"regex result: {len(input_string)}")
    return len(input_string)

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day10.py testinput.txt")
        exit(1)
    input_string = ""
    with open(sys.argv[1], "r") as fileobj:
        input_string = fileobj.readline().rstrip()
    if(DEBUG):
        print(f"Input string is {input_string}")
    part1_ans = solve_puzzle_regex(40, input_string)
    print(f"The answer to part 1 is {part1_ans}")
    part2_ans = solve_puzzle_regex(50, input_string)
    print(f"The answer to part 2 is {part2_ans}")
