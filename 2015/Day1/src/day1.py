import sys

def part1(line: str) -> int:
    floor = 0
    for char in line:
        if char == "(":
            floor += 1
        elif char == ")":
            floor -= 1
    return floor

def part2(line: str) -> int:
    floor = 0
    for i in range(len(line)):
        char = line[i]
        if char == "(":
            floor += 1
        elif char == ")":
            floor -= 1
        if floor < 0:
            return (i + 1)
    return len(line) # floor was never negative

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("usage: python3 day1.py input.txt")
        exit(1)

    line = ""
    with open(sys.argv[1], "r") as fileobj:
        line = fileobj.readline().strip()

    part1_ans = part1(line)
    part2_ans = part2(line)
    
    print(f"Part 1: Santa ends up on floor {part1_ans}")
    print(f"Part 2: position {part2_ans} causes Santa to enter basement")
