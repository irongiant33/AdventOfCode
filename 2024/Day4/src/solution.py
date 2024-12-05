import re

FILENAME = "input.txt"

def parse_input() -> list:
    char_map = []
    with open(FILENAME, "r") as fileobj:
        for line in fileobj:
            char_map.append(list(line.rstrip()))
    return char_map

def xmas_count(list_input: list) -> int:
    forward_count = len(re.findall("XMAS", "".join(list_input)))
    backward_count = len(re.findall("XMAS", "".join(list_input[-1::-1])))
    return forward_count + backward_count

def part1() -> int:
    """
    search and find any instance of XMAS, forward or backward, in a 2D gri
    occurences can be in rows, columns, or diagonals
    """
    char_map = parse_input()
    count = 0

    # check rows, forward and backward
    for i in range(len(char_map)):
        row = char_map[i]
        row_count = xmas_count(row)
        count = count + row_count

    #check cols, forward and backward
    for i in range(len(char_map[0])):
        col = [char_map[j][i] for j in range(len(char_map))]
        col_count = xmas_count(col)
        count = count + col_count

    # check forward slash diagonals. top right to left then bottom.
    for i in range(0, len(char_map[0])):
        rightward_diagonal = [char_map[k][i + k] for k in range(min(len(char_map), len(char_map[0]) - i))]
        rd_count = xmas_count(rightward_diagonal)
        count = count + rd_count

    for i in range(1, len(char_map)):
        downward_diagonal = [char_map[i + k][k] for k in range(min(len(char_map) - i, len(char_map[0])))]
        dd_count = xmas_count(downward_diagonal)
        count = count + dd_count

    # check backslash diagonals. bottom right to left then top.
    for i in range(0, len(char_map)):
        upward_diagonal = [char_map[i - k][k] for k in range(i + 1)]
        ud_count = xmas_count(upward_diagonal)
        count = count + ud_count

    for i in range(1, len(char_map[0])):
        rightward_diagonal = [char_map[len(char_map) - k - 1][i + k] for k in range(min(len(char_map[0]) - i, len(char_map)))]
        rd_count = xmas_count(rightward_diagonal)
        count = count + rd_count

    return count

def part2() -> int:
    char_map = parse_input()
    dimension = 3 # dimension of MAS "box"
    count = 0
    for i in range(len(char_map[0]) - dimension + 1):
        for j in range(len(char_map) - dimension + 1):
            word1 = "".join([char_map[j + k][i + k] for k in range(dimension)])
            word2 = "".join([char_map[j + dimension - 1 - k][i + k] for k in range(dimension)])
            if((word1 == word2 and word1 == "MAS") or 
               (word1 == "SAM" and word2 == "MAS") or
               (word1 == word2 and word1 == "SAM") or
               (word1 == "MAS" and word2 == "SAM")):
                count = count + 1
    return count

if __name__ == "__main__":
    part1_ans = part1()
    print(f"Part 1 answer is {part1_ans}")
    part2_ans = part2()
    print(f"Part 2 answer is {part2_ans}")
