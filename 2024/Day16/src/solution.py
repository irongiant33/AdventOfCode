import bisect

FILENAME = "input.txt"
DEBUG = False

UP    = (-1,  0)
DOWN  = ( 1,  0)
RIGHT = ( 0,  1)
LEFT  = ( 0, -1)

class Path:
    def __init__(self, steps: list, cost, orientation, end_step):
        self.steps = steps
        self.orientation = orientation
        self.path_cost = cost
        self.cost = self.path_cost + (steps[-1].row - end_step.row) + (steps[-1].col - end_step.col)
        if(DEBUG):
            print(f'initializing path with {len(steps)} steps and cost {self.cost}')

    def __lt__(self, other):
        return self.cost < other.cost

    def __gt__(self, other):
        return self.cost > other.cost

    def __eq__(self, other):
        return self.cost == other.cost

    def __le__(self, other):
        return self.cost <= other.cost

    def __ge__(self, other):
        return self.cost >= other.cost

    def __repr__(self):
        return f'path length {len(self.steps)}, cost {self.cost}, orientation {self.orientation}'

class Step:
    def __init__(self, row, col, icon='.'):
        self.row = row
        self.col = col
        self.icon = icon
        self.neighbors = []

    def __eq__(self, other):
        return ((self.row == other.row) and (self.col == other.col))

    def __repr__(self):
        return self.icon

    def make_neighbors(self, step_dict):
        up = (self.row + UP[0], self.col + UP[1])
        down = (self.row + DOWN[0], self.col + DOWN[1])
        left = (self.row + LEFT[0], self.col + LEFT[1])
        right = (self.row + RIGHT[0], self.col + RIGHT[1])
        if(up in step_dict):
            self.neighbors.append(up)
        if(down in step_dict):
            self.neighbors.append(down)
        if(left in step_dict):
            self.neighbors.append(left)
        if(right in step_dict):
            self.neighbors.append(right)
        return

    def get_distance(self, other):
        return (self.row - other.row)**2 + (self.col - other.col)**2 

def print_map(step_dict, num_rows, num_cols, steps=[]):
    str_map = []
    for i in range(num_rows):
        str_row = []
        for j in range(num_cols):
            if((i, j) not in step_dict):
                str_row.append(' ')
            else:
                str_row.append(step_dict[(i, j)].icon)
        str_map.append(str_row)
    for step in steps:
        str_map[step.row][step.col] = 'x'
    for row in str_map:
        print(''.join(row))
    return

def subtract(cost1, cost2):
    return 500 * (abs(cost1[0] - cost2[0]) + abs(cost1[1] - cost2[1])) + 1

def part1():
    # there is always an A* problem :)
    step_dict = {}
    end_step   = None
    start_step = None
    num_rows = -1
    num_cols = -1
    # read in file
    with open(FILENAME, "r") as fileobj:
        row_index = 0
        for line in fileobj:
            line_list = list(line.rstrip())
            num_cols = len(line_list) 
            for col_index in range(len(line_list)):
                if(line_list[col_index] != '#'):
                    current_step = Step(row_index, col_index, line_list[col_index])
                    step_dict[(row_index, col_index)] = current_step
                    if(line_list[col_index] == 'S'):
                        start_step = current_step
                    elif(line_list[col_index] == 'E'):
                        end_step   = current_step
            row_index += 1
        num_rows = row_index
    # build neighbors
    for step in step_dict.values():
        step.make_neighbors(step_dict)
    if(DEBUG):
        print_map(step_dict, num_rows, num_cols)
        print(f'Start step: {start_step.row}, {start_step.col}')
        print(f'End step: {end_step.row}, {end_step.col}')
    # start A* search
    path_list = [Path([start_step], 0, RIGHT, end_step)]
    reached_end = False
    optimal_path = None
    count = 0
    while(len(path_list) > 0 and not reached_end):
        best_path = path_list.pop(0)
        last_step = best_path.steps[-1]
        if(last_step.icon == 'E'):
            reached_end = True
            optimal_path = best_path
            break
        up         = (last_step.row + UP[0],    last_step.col + UP[1])
        up_cost    = best_path.path_cost + subtract(best_path.orientation, UP)
        down       = (last_step.row + DOWN[0],  last_step.col + DOWN[1])
        down_cost  = best_path.path_cost + subtract(best_path.orientation, DOWN)
        left       = (last_step.row + LEFT[0],  last_step.col + LEFT[1])
        left_cost  = best_path.path_cost + subtract(best_path.orientation, LEFT)
        right      = (last_step.row + RIGHT[0], last_step.col + RIGHT[1])
        right_cost = best_path.path_cost + subtract(best_path.orientation, RIGHT)
        # add next paths
        if(up in last_step.neighbors and Step(up[0], up[1]) not in best_path.steps):
            next_steps = []
            next_steps.extend(best_path.steps)
            next_steps.append(step_dict[up])
            bisect.insort(path_list, Path(next_steps, up_cost, UP, end_step))
        if(down in last_step.neighbors and Step(down[0], down[1]) not in best_path.steps):
            next_steps = []
            next_steps.extend(best_path.steps)
            next_steps.append(step_dict[down])
            bisect.insort(path_list, Path(next_steps, down_cost, DOWN, end_step))
        if(right in last_step.neighbors and Step(right[0], right[1]) not in best_path.steps):
            next_steps = []
            next_steps.extend(best_path.steps)
            next_steps.append(step_dict[right])
            bisect.insort(path_list, Path(next_steps, right_cost, RIGHT, end_step))
        if(left in last_step.neighbors and Step(left[0], left[1]) not in best_path.steps):
            next_steps = []
            next_steps.extend(best_path.steps)
            next_steps.append(step_dict[left])
            bisect.insort(path_list, Path(next_steps, left_cost, LEFT, end_step))
        count = count + 1
        if(DEBUG or count % 200000 == 0):
            print_map(step_dict, num_rows, num_cols, best_path.steps)
            print()
            count = 0
    return optimal_path.path_cost

            
def part2():
    return -1

if __name__ == "__main__":
    part1_ans = part1()
    print(f'answer to part 1 is {part1_ans}')
    part2_ans = part2()
    print(f'answer to part 2 is {part2_ans}')
