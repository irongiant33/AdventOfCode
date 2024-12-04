import re

FILENAME = "input.txt"

def part1():
    with open(FILENAME, "r") as fileobj:
        result = 0
        for input_line in fileobj:
            line = input_line.rstrip()
            instruction_list = re.findall("mul\(\d+,\d+\)", line)
            for instruction in instruction_list:
                digit_list = re.findall("\d+,\d+", instruction)[0].split(",")
                result = result + int(digit_list[0]) * int(digit_list[1])
    return result

def part2():
    with open(FILENAME, "r") as fileobj:
        result = 0
        enabled = True
        for input_line in fileobj:
            line = input_line.rstrip()
            instruction_list = re.findall("(mul\(\d+,\d+\))|(do\(\))|(don't\(\))", line)
            for instruction in instruction_list:
                if(instruction[1]):
                    enabled = True
                elif(instruction[2]):
                    enabled = False
                if(enabled and instruction[0]):
                    digit_list = re.findall("\d+,\d+", instruction[0])[0].split(",")
                    result = result + int(digit_list[0]) * int(digit_list[1])
        return result

if __name__ == "__main__":
    part1_ans = part1()
    print(f"Answer to part 1 is {part1_ans}")
    part2_ans = part2()
    print(f"Answer to part 2 is {part2_ans}")
