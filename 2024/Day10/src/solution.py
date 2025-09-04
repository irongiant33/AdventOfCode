FILENAME = "input.txt"
DEBUG = False

class TrailBlock:
    def __init__(self, height, row, col):
        self.row = row
        self.col = col
        self.height = height
        self.neighbors = []

    def __eq__(self, other_block):
        return ((self.row == other_block.row) and (self.col == other_block.col))

    def __repr__(self):
        return str(self.height)

def build_map() -> list:
    trail_map = []
    row_count = 0
    with open(FILENAME, "r") as fileobj:
        for line in fileobj:
            col_count = 0
            line_str = list(line.rstrip())
            line_objects = []
            for char in line_str:
                if char == '.':
                    line_objects.append(None)
                elif char.isdigit():
                    line_objects.append(TrailBlock(int(char), row_count, col_count))
                col_count = col_count + 1
            trail_map.append(line_objects)
            row_count = row_count + 1
    for row_index in range(len(trail_map)):
        for col_index in range(len(trail_map[0])):
            if(trail_map[row_index][col_index] is None):
                continue
            if(row_index - 1 >= 0):
                trail_map[row_index][col_index].neighbors.append(trail_map[row_index - 1][col_index])
            if(row_index + 1 < len(trail_map)):
                trail_map[row_index][col_index].neighbors.append(trail_map[row_index + 1][col_index])
            if(col_index - 1 >= 0):
                trail_map[row_index][col_index].neighbors.append(trail_map[row_index][col_index - 1])
            if(col_index + 1 < len(trail_map[0])):
                trail_map[row_index][col_index].neighbors.append(trail_map[row_index][col_index + 1])
    return trail_map

def find_trail_heads(trail_map: list) -> list:
    trail_heads = []
    for row_index in range(len(trail_map)):
        for col_index in range(len(trail_map[0])):
            if(trail_map[row_index][col_index] is not None and trail_map[row_index][col_index].height == 0):
                trail_heads.append((row_index, col_index))
    return trail_heads

def print_path(path, num_rows, num_cols):
    map_string = []
    for i in range(num_rows):
        map_string.append(list('.' * num_cols))
    for trail_block in path:
        map_string[trail_block.row][trail_block.col] = str(trail_block.height)
    for row in map_string:
        print(''.join(row))

def find_score(trail_head: tuple, trail_map: list) -> int:
    # number of 9's that the trail head can reach by only increasing by 1 each step
    score = 0
    visited_list = []
    path_list = [[trail_map[trail_head[0]][trail_head[1]]]]
    if(DEBUG):
        print(f'finding scores for trail head {trail_head}')
    while(len(path_list) > 0):
        path = path_list.pop(0)
        if(DEBUG):
            print(f'path: {path}, next neighbors: {path[-1].neighbors}')
            print_path(path, len(trail_map), len(trail_map[0]))
        for neighbor in path[-1].neighbors:
            if(neighbor is not None and neighbor.height == 9 and neighbor.height == path[-1].height + 1):
                score = score + 1
                if(neighbor not in visited_list):
                    visited_list.append(neighbor)
            elif(neighbor is not None and neighbor.height == path[-1].height + 1):
                new_path = [trail_block for trail_block in path]
                new_path.append(neighbor)
                if(DEBUG):
                    print(f'adding neighbor {neighbor} to new path {new_path}')
                path_list.append(new_path)
    if(DEBUG):
        print(f'score for trail head {trail_head} is {len(visited_list)}')
        print()
    return len(visited_list), score

def print_trail_map_and_heads(trail_map, trail_heads=None):
    for row in trail_map:
        for col in row:
            if(col is not None):
                print(col, end='')
            else:
                print('.', end='')
        print('')
    if(trail_heads is not None):
        print(trail_heads)

def part1():
    trail_map = build_map()
    trail_heads = find_trail_heads(trail_map)
    if(DEBUG):
        print_trail_map_and_heads(trail_map, trail_heads)

    score = 0
    for trail_head in trail_heads:
        nondistinct_score, _ = find_score(trail_head, trail_map)
        score = score + nondistinct_score
    return score


def part2():
    trail_map = build_map()
    trail_heads = find_trail_heads(trail_map)
    if(DEBUG):
        print_trail_map_and_heads(trail_map, trail_heads)

    score = 0
    for trail_head in trail_heads:
        _, distinct_score = find_score(trail_head, trail_map)
        score = score + distinct_score
    return score

if __name__ == "__main__":
    part1_ans = part1()
    print(f'part 1 answer is {part1_ans}')
    part2_ans = part2()
    print(f'part 2 answer is {part2_ans}')
