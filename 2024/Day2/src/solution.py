import re

FILENAME = "input.txt"

def test_line(line):
    increasing = True
    decreasing = True
    max_diff = 0
    for i in range(1, len(line)):
        diff = line[i] - line[i - 1]
        if(diff > 0):
            decreasing = False
        elif(diff < 0):
            increasing = False
        elif(diff == 0):
            decreasing = False
            increasing = False
        if(abs(diff) > max_diff):
            max_diff = abs(diff)
    if(max_diff <= 3 and (increasing or decreasing)):
        return True
    return False

def part1(filename):
    with open(filename, "r") as fileobj:
        safe_count = 0
        for line in fileobj:
            values = [int(value) for value in re.split("\s+", line.rstrip())]
            if(test_line(values)):
                safe_count = safe_count + 1
        return safe_count

def part2(filename):
    with open(filename, "r") as fileobj:
        safe_count = 0
        for line in fileobj:
            values = [int(value) for value in re.split("\s+", line.rstrip())]
            good_result = test_line(values)
            index = 0
            while(not good_result and index < len(values)):
                good_result = test_line([values[i] for i in range(len(values)) if i != index])
                index = index + 1
            if(good_result):
                safe_count = safe_count + 1
        return safe_count

if __name__ == "__main__":
    part1_ans = part1(FILENAME)
    print(f"Answer to part 1 is {part1_ans}")
    part2_ans = part2(FILENAME)
    print(f"Answer to part 2 is {part2_ans}")
