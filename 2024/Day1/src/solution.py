import re

FILENAME = "input.txt"

def get_lists(filename: str) -> list:
    first_list = []
    second_list = []
    with open(filename, "r") as fileobj:
        for line in fileobj:
            line_split = re.split("\s+", line)
            first_list.append(int(line_split[0]))
            second_list.append(int(line_split[1]))
    first_list.sort()
    second_list.sort()
    return first_list, second_list

def part1(filename: str) -> int:
    first_list, second_list = get_lists(filename)
    if(len(first_list) != len(second_list) or len(first_list) == 0):
        raise ValueError("error, list length mismatch")
    distance = 0
    for i in range(len(first_list)):
        distance = distance + abs(second_list[i] - first_list[i])
    return distance

def part2(filename: str) -> int:
    first_list, second_list = get_lists(filename)
    similarity_total = 0
    for value in first_list:
        similarity_count = second_list.count(value)
        similarity_total = similarity_total + value * similarity_count
    return similarity_total
        
if __name__ == "__main__":
    part1_ans = part1(FILENAME)
    print(f"The answer to part 1 is {part1_ans}")
    part2_ans = part2(FILENAME)
    print(f"The answer to part 2 is {part2_ans}")
