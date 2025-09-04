FILENAME = "testinput2.txt"
DEBUG = True
LEFT  = 0 # should do an enum
UP    = 1
RIGHT = 2
DOWN  = 3
WALL  = 4
ROBOT = 5
BOX   = 6

class Tile:
    def __init__(self, tile_type, row, col, big=False):
        self.tile_type = tile_type
        self.row       = row
        self.col       = col
        self.big       = big
    
    def update_pos(self, direction):
        if(direction == LEFT):
            self.col = self.col - 1
        elif(direction == RIGHT):
            self.col = self.col + 1
        elif(direction == UP):
            self.row = self.row - 1
        elif(direction == DOWN):
            self.row = self.row + 1
        return

    def __repr__(self):
        if(not self.big and self.tile_type == WALL):
            return '#'
        elif(self.big and self.tile_type == WALL):
            return '##'
        if(self.tile_type == ROBOT):
            return '@'
        if(not self.big and self.tile_type == BOX):
            return 'O'
        elif(self.big and self.tile_type == BOX):
            return '[]'
        return '?'

def print_grid(grid, num_rows, num_cols):
    for i in range(num_rows):
        for j in range(num_cols):
            if((i, j) in grid):
                print(grid[(i, j)], end='')
            else:
                print('.', end='')
        print()

def push(grid, tile, direction: int) -> bool:
    can_push = True
    next_row = tile.row
    next_col = tile.col
    if(direction == LEFT):
        next_col = next_col - 1
    elif(direction == RIGHT):
        next_col = next_col + 1
    elif(direction == DOWN):
        next_row = next_row + 1
    elif(direction == UP):
        next_row = next_row - 1
    if((next_row, next_col) in grid and grid[(next_row, next_col)].tile_type == BOX):
        can_push = push(grid, grid[(next_row, next_col)], direction)
    elif((next_row, next_col) in grid and grid[(next_row, next_col)].tile_type == WALL):
        return False
    # otherwise, the type must be empty, therefore we can push
    if(can_push):
        grid.pop((tile.row, tile.col))
        tile.update_pos(direction)
        grid[(tile.row, tile.col)] = tile
        return True

def part1():
    grid = {}
    num_rows = 0
    num_cols = 0
    row_index = 0
    robot = None
    read_grid = True
    instructions = []
    with open(FILENAME, "r") as fileobj:
        for line in fileobj:
            if(read_grid):
                row = list(line.rstrip())
                if(len(row) < num_cols):
                    read_grid = False
                    continue
                num_cols = len(row)
                for col_index in range(num_cols):
                    if(row[col_index] == '#'):
                        grid[(row_index, col_index)] = Tile(WALL, row_index, col_index)
                    elif(row[col_index] == '@'):
                        robot = Tile(ROBOT, row_index, col_index)
                        grid[(row_index, col_index)] = robot
                    elif(row[col_index] == 'O'):
                        grid[(row_index, col_index)] = Tile(BOX, row_index, col_index)
                row_index += 1
            else:
                row = list(line.rstrip())
                for instruction in row:
                    if(instruction == '>'):
                        instructions.append(RIGHT)
                    elif(instruction == 'v'):
                        instructions.append(DOWN)
                    elif(instruction == '<'):
                        instructions.append(LEFT)
                    elif(instruction == '^'):
                        instructions.append(UP)
    num_rows = row_index
    # follow instructions to push stuff around
    if(DEBUG):
        print_grid(grid, num_rows, num_cols)
        print(instructions)
    for instruction in instructions:
        push(grid, robot, instruction)
        if(DEBUG):
            print(f'Move {instruction}:')
            print_grid(grid, num_rows, num_cols)
            print()
    # calculate GPS coordinates. 100 per row from the edge, 1 per col from the edge
    gps = 0
    for tile_pos in grid:
        if(grid[tile_pos].tile_type == BOX):
            gps = gps + grid[tile_pos].row * 100
            gps = gps + grid[tile_pos].col
    return gps

def print_big_grid(grid, num_rows, num_cols):
    for i in range(num_rows):
        for j in range(num_cols):
            if((i, j) in grid):
                print(grid[(i, j)], end='')
            elif((i, j - 1) not in grid or grid[(i, j - 1)].big == False):
                print('.', end='')
        print()

def big_push(grid, tile, direction: int) -> bool:
    can_push = True
    next_row = tile.row
    next_col = tile.col
    if(direction == LEFT):
        next_col = next_col - 1
    elif(direction == RIGHT):
        next_col = next_col + 1
    elif(direction == DOWN):
        next_row = next_row + 1
    elif(direction == UP):
        next_row = next_row - 1
    pos_a = (next_row, next_col) in grid
    pos_b = (next_row, next_col - 1) in grid
    next_pos = pos_a
    if(not next_pos and pos_b):
        next_pos = pos_b

    if(((next_row, next_col) in grid or (next_row, next_col - 1) in grid) and grid[(next_row, next_col)].tile_type == BOX):
        can_push = push(grid, grid[(next_row, next_col)], direction)
    elif((next_row, next_col) in grid and grid[(next_row, next_col)].tile_type == WALL):
        return False
    # otherwise, the type must be empty, therefore we can push
    if(can_push):
        grid.pop((tile.row, tile.col))
        tile.update_pos(direction)
        grid[(tile.row, tile.col)] = tile
        return True

def part2():
    grid = {}
    num_rows = 0
    num_cols = 0
    row_index = 0
    robot = None
    read_grid = True
    instructions = []
    with open(FILENAME, "r") as fileobj:
        for line in fileobj:
            if(read_grid):
                row = list(line.rstrip())
                if(len(row) < num_cols):
                    read_grid = False
                    continue
                num_cols = len(row)
                for col_index in range(num_cols):
                    if(row[col_index] == '#'):
                        grid[(row_index, col_index * 2)] = Tile(WALL, row_index, col_index * 2, True)
                    elif(row[col_index] == '@'):
                        robot = Tile(ROBOT, row_index, col_index)
                        grid[(row_index, col_index * 2)] = robot
                    elif(row[col_index] == 'O'):
                        grid[(row_index, col_index * 2)] = Tile(BOX, row_index, col_index * 2, True)
                row_index += 1
            else:
                row = list(line.rstrip())
                for instruction in row:
                    if(instruction == '>'):
                        instructions.append(RIGHT)
                    elif(instruction == 'v'):
                        instructions.append(DOWN)
                    elif(instruction == '<'):
                        instructions.append(LEFT)
                    elif(instruction == '^'):
                        instructions.append(UP)
    num_rows = row_index
    if(DEBUG):
        print_big_grid(grid, num_rows, num_cols * 2)
        print(instructions)
    # follow instructions to push stuff around
    for instruction in instructions:
        big_push(grid, robot, instruction)
        if(DEBUG):
            print(f'Move {instruction}')
            print_big_grid(grid, num_rows, num_cols * 2)
            print()
    # calculate gps score

if __name__ == "__main__":
    # part1_ans = part1()
    # print(f'answer to part 1 is {part1_ans}')
    part2_ans = part2()
    print(f'answer to part 2 is {part2_ans}')
