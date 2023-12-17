START_CHAR = 'S'
UP = [-1, 0]
RIGHT = [0, 1]
DOWN = [1, 0]
LEFT = [0, -1]
DIRECTIONS = [UP, RIGHT, DOWN, LEFT] # CW starting at 12'o'clock
PIPE_LIST = [# start at 12'o'clock position and go counterclockwise. (row delta, col delta)
    "|",
    "-",
    "L",
    "J",
    "7",
    "F",
    "S"
]
PIPE_DIRS = [
    [DOWN, UP],
    [LEFT, RIGHT],
    [DOWN, LEFT],
    [DOWN, RIGHT],
    [UP, RIGHT],
    [LEFT, UP],
    [DOWN, RIGHT, LEFT, UP]
]
NEXT_DIRS = [
    [DOWN, UP],
    [LEFT, RIGHT],
    [UP, RIGHT],
    [LEFT, UP],
    [LEFT, DOWN],
    [RIGHT, DOWN],
    [UP, DOWN, LEFT, RIGHT]
]

def is_connected(direction, pipe_index):
    if(direction in PIPE_DIRS[pipe_index]):
        return True
    return False

def find_path(grid, start_pos, debug=False):
    num_rows = len(grid)
    num_cols = len(grid[0])
    current_pos = start_pos
    circle_complete = False
    path = [current_pos]
    prev_char = START_CHAR
    while(not circle_complete):
        if(debug):
            print(path)
        connection_exists = False
        pipe_directions = NEXT_DIRS[PIPE_LIST.index(prev_char)]
        for direction in pipe_directions:
            temp_x = current_pos[0] + direction[0]
            temp_y = current_pos[1] + direction[1]

            # check out of bounds
            if(temp_x >= num_rows or temp_x < 0 or temp_y < 0 or temp_y >= num_cols):
                if(debug):
                    print('oob')
                continue
            
            # check if connected
            if(grid[temp_x][temp_y] in PIPE_LIST and is_connected(direction, PIPE_LIST.index(grid[temp_x][temp_y]))):
                if(prev_char != START_CHAR and grid[temp_x][temp_y] == START_CHAR):
                    circle_complete = True
                    connection_exists = True
                    break
                elif(grid[temp_x][temp_y] != START_CHAR):
                    path.append([temp_x, temp_y])
                    current_pos = [temp_x, temp_y]
                    prev_char = grid[temp_x][temp_y]
                    grid[temp_x][temp_y] = '.'
                    connection_exists = True
                    break

        # start over :(
        if(not connection_exists):
            if(debug):
                print('starting over')
            if(current_pos == start_pos):
                print('no path :(')
                break
            current_pos = start_pos
            path = [current_pos]
    return path

def part1(infilename):
    grid = []
    debug = False
    start_pos = [0,0]
    with open(infilename) as infile:
        row_count = 0
        for line in infile:
            if(START_CHAR in line):
                start_pos[0] = row_count
                start_pos[1] = line.index(START_CHAR)
            items = list(line.rstrip())
            grid.append(items)
            row_count += 1
    return len(find_path(grid, start_pos, debug=debug))//2
    

def part2(infilename):
    grid = []
    debug = False
    start_pos = [0,0]
    with open(infilename) as infile:
        row_count = 0
        for line in infile:
            if(START_CHAR in line):
                start_pos[0] = row_count
                start_pos[1] = line.index(START_CHAR)
            items = list(line.rstrip())
            grid.append(items)
            row_count += 1
    path = find_path(grid, start_pos, debug=debug)

if __name__ == "__main__":
    part1ans = part1("input.txt")
    print(f"answer to part 1 is: {part1ans}")

    part2ans = part2("input.txt")
    print(f"answer to part 2 is: {part2ans}")