import sys

def calculate_square_footage(input_values : list)->int :
    square_footage = 0
    for value in input_values:
        areas = [value[0] * value[1], value[1] * value[2], value[2] * value[0]]
        min_area = min(areas)
        surface_area = sum(areas) * 2
        square_footage += surface_area + min_area
    return square_footage

def calculate_ribbon_length(input_values : list)->int :
    ribbon_length = 0
    for value in input_values:
        perimeters = [2*(value[0] + value[1]), 2*(value[1] + value[2]), 2*(value[2] + value[0])]
        min_perimeter = min(perimeters)
        volume = value[0] * value[1] * value[2]
        ribbon_length += min_perimeter + volume
    return ribbon_length

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day2.py input.txt")
        exit
    
    # get input
    input_values = []
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            input_values.append([int(a) for a in line.split('x')])

    # part 1
    part1_ans = calculate_square_footage(input_values)

    # part 2
    part2_ans = calculate_ribbon_length(input_values)

    print(f"The answer to part 1 is {part1_ans}")
    print(f"The answer to part 2 is {part2_ans}")
