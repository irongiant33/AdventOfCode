grid = []

def get_neighbors(row, col):
    neighbors = []
    if(row != 0 and col != 0):
        neighbors.append(grid[row-1][col-1])
        neighbors.append(grid[row-1][col])
        neighbors.append(grid[row-1][col+1])
        neighbors.append(grid[row][col-1])
        neighbors.append(grid[row][col+1])
    elif(row !=0 and col == 0):
        neighbors.append(grid[row-1][col])
        neighbors.append(grid[row-1][col+1])
        neighbors.append(grid[row][col+1])
    elif(row==0 and col!=0):
        neighbors.append(grid[row][col-1])
        neighbors.append(grid[row][col+1])
    else:
        neighbors.append(grid[row][col+1])
   
    if(row != len(grid) and col != len(grid[0])):
        neighbors.append(grid[row+1][col-1])
        neighbors.append(grid[row+1][col])
        neighbors.append(grid[row+1][col+1])
    elif(row != len(grid) and col == len(grid[0])):
        neighbors.append(grid[row+1][col-1])
        neighbors.append(grid[row+1][col])
    return neighbors
   
def get_number_str(row, col,debug=False):
    numberstr = grid[row][col]
    grid[row][col] = "."
    newcol = col - 1
    while newcol > -1:
        if(grid[row][newcol].isdigit()):
            numberstr = grid[row][newcol] + numberstr
            grid[row][newcol] = "."
        else:
            break
        newcol -= 1
           
    newcol = col + 1
    while newcol < len(grid[0]):
        if(grid[row][newcol].isdigit()):
            numberstr = numberstr + grid[row][newcol]
            grid[row][newcol] ="."
        else:
            break
        newcol+= 1
    return numberstr

def get_numbers(row, col, debug=False):
    numbers = []
    for i in range(-1,2):
        newrow = row + i
        for j in range(-1, 2):
            newcol = col + j
            if(newrow < 0 or newrow >= len(grid) or newcol < 0 or newcol >= len(grid[0])):
                continue
            if(grid[newrow][newcol].isdigit()):
                if(debug):
                    print(f"{newrow}:{newcol} = {grid[newrow][newcol]}")
                numberstr = get_number_str(newrow, newcol,debug=debug)
                numbers.append(int(numberstr))
    return numbers

def part1():
    debug = False
    sum = 0
    if(debug):
        for line in grid:
            print(line)
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if(not grid[i][j].isdigit() and grid[i][j] != "."):
                if(debug):
                    print(grid[i][j])
                numbers = get_numbers(i, j,debug=debug)
                for number in numbers:
                    sum += number
                    if debug:
                        print(number)
    return sum
       
def part2():
    sum = 0
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if(grid[i][j] == "*"):
                numbers = get_numbers(i,j)
                if(len(numbers) == 2):
                    sum += numbers[0] * numbers[1]
    return sum

if __name__=="__main__":
    with open("day3.txt") as infile:
        for line in infile:
            grid.append(list(line.rstrip()))
    part1_ans = part1()
    print(f"The answer to part 1 is: {part1_ans}")
   
    with open("day3.txt") as infile:
        for line in infile:
            grid.append(list(line.rstrip()))
    part2_ans = part2()
    print(f"The answer to part 2 is: {part2_ans}") 