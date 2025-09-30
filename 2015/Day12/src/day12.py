import json
import sys

DEBUG = False

def get_sum(element, spacing=0, ignore_red=False):
    if(DEBUG):
        print(f"{" "*spacing}Element is {element}", end='')
    my_sum = 0
    if(type(element) == type([])):
        if(DEBUG):
            print(' is a list')
        for next_element in element:
            my_sum += get_sum(next_element, spacing+1, ignore_red)
    elif(type(element) == type(1)):
        if(DEBUG):
            print(' is an int')
        my_sum += element
    elif(type(element) == type({})):
        if(DEBUG):
            print(' is a dict', end='')
        if(ignore_red and ('red' in element.keys() or 'red' in element.values())):
            my_sum += 0
        else:
            for item in element.items():
                if(DEBUG):
                    print(', getting key value')
                my_sum += get_sum(item[0], spacing+1, ignore_red)
                if(DEBUG):
                    print('{" "*spacing}...now getting value value')
                my_sum += get_sum(item[1], spacing+1, ignore_red)
    else:
        my_sum += 0
    return my_sum

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day12.py input.txt")
        exit(1)
    with open(sys.argv[1], "r") as fileobj:
        file_input = fileobj.read()
        file_dict = json.loads(file_input)
        sum_part1 = 0
        sum_part2 = 0
        for element in file_dict:
            sum_part1 += get_sum(element)
            sum_part2 += get_sum(element, ignore_red=True)
        print(f"Sum for part 1 is {sum_part1}")
        print(f"Sum for part 2 is {sum_part2}")
