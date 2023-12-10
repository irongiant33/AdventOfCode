import re

def part1(infilename):
    timepattern = "Time:\s+(\d+(?:\s+\d+)*)"
    distancepattern = "Distance:\s+(\d+(?:\s+\d+)*)"
    time_values = []
    distance_values = []
    with open(infilename) as infile:
        time_match = re.match(timepattern, infile.readline().rstrip())
        distance_match = re.match(distancepattern, infile.readline().rstrip())
        if(not time_match):
            print('no time match, exiting')
            exit
        time_values = list(map(int, time_match.group(1).split()))

        if(not distance_match):
            print('no distance match, exiting')
            exit
        distance_values = list(map(int, distance_match.group(1).split()))
    
    product = 1
    for i in range(len(time_values)):
        num_wins = 0
        for j in range(1, time_values[i]):
            if((((time_values[i] - j) * j)) > distance_values[i]):
                num_wins += 1
        product *= num_wins

    return product

def part2(infilename):
    timepattern = "Time:\s+(\d+(?:\s+\d+)*)"
    distancepattern = "Distance:\s+(\d+(?:\s+\d+)*)"
    time_value = -1
    distance_value = -1
    with open(infilename) as infile:
        time_match = re.match(timepattern, infile.readline().rstrip())
        distance_match = re.match(distancepattern, infile.readline().rstrip())
        if(not time_match):
            print('no time match, exiting')
            exit
        time_value = int(''.join(time_match.group(1).split()))

        if(not distance_match):
            print('no distance match, exiting')
            exit
        distance_value = int(''.join(distance_match.group(1).split()))
    

    num_wins = 0
    for j in range(1, time_value):
        if((((time_value - j) * j)) > distance_value):
            num_wins += 1

    return num_wins

if __name__ == "__main__":
    part1ans = part1("input.txt")
    print(f"the answer to part 1 is {part1ans}")

    part2ans = part2("input.txt")
    print(f"the answer to part 2 is {part2ans}")