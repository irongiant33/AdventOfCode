FILENAME = "input.txt"

def parse_input():
    floorplan = []
    row_index = 0
    col_index = 0
    count = 0
    with open(FILENAME, "r") as fileobj:
        for line in fileobj:
            row = list(line.rstrip())
            index = -1
            try:
                index = row.index('^')
            except:
                pass
            if(index != -1):
                col_index = index
                row_index = count
            floorplan.append(row)
            count = count + 1
    return floorplan, (row_index, col_index)

def part1():
    floorplan, starting_pos = parse_input()
    current_pos = [starting_pos[0], starting_pos[1]]
    out_of_bounds = False
    step = [[-1, 0], [0, 1], [1, 0], [0, -1]]
    step_index = 0
    while(not out_of_bounds):
        next_pos = [current_pos[0] + step[step_index][0], current_pos[1] + step[step_index][1]]
        if(next_pos[0] >= len(floorplan) or 
           next_pos[0] < 0 or 
           next_pos[1] >= len(floorplan[0]) or 
           next_pos[1] < 0):
            out_of_bounds = True
            floorplan[current_pos[0]][current_pos[1]] = 'X'
        elif(floorplan[next_pos[0]][next_pos[1]] == '#'):
            step_index = (step_index + 1) % len(step)
        else:
            floorplan[current_pos[0]][current_pos[1]] = 'X'
            current_pos = [next_pos[0], next_pos[1]]
    count = 0
    for row in floorplan:
        #print(row)
        for val in row:
            if(val == 'X'):
                count = count + 1
    return count

def part2():
    return -1

if __name__ == "__main__":
    part1_ans = part1()
    print(f"part 1 ans is {part1_ans}")
    part2_ans = part2()
    print(f"part 2 ans is {part2_ans}")
