FILENAME = "input.txt"

class Antenna:
    def __init__(self, freq, row, col):
        self.row = row
        self.col = col
        self.freq = freq

    def __eq__(self, other_antenna):
        return other_antenna.freq == self.freq

    def __repr__(self):
        return f'Antenna freq: {self.freq}, pos: {self.row}, {self.col}'


class Antinode:
    def __init__(self, row, col, antenna_a, antenna_b):
        self.row = row
        self.col = col
        self.antenna_a = antenna_a
        self.antenna_b = antenna_b

    def __eq__(self, other_antinode):
        return ((self.row == other_antinode.row) and (self.col == other_antinode.col))

    def __repr__(self):
        return f'Antinode pos: {self.row}, {self.col} from {self.antenna_a} and {self.antenna_b}\n'


def create_antenna_dict():
    """
    return dictionary of Antenna objects, keys are the frequency, value is a list of all antennas at that freq
    also return tuple of the max row and column index because antinodes can't be outside the map
    """
    antenna_dict = {}
    with open(FILENAME, "r") as fileobj:
        row_count = 0 
        for line in fileobj:
            col_count = 0
            for char in line.rstrip():
                if(char != '.' and char not in antenna_dict):
                    antenna_dict[char] = [Antenna(char, row_count, col_count)] 
                elif(char != '.'):
                    antenna_dict[char].append(Antenna(char, row_count, col_count))
                col_count = col_count + 1
            row_count = row_count + 1
    return antenna_dict, (row_count - 1, col_count - 1)

def create_antinodes(antenna_a, antenna_b, row_max, col_max):
    rise = antenna_b.row - antenna_a.row
    run  = antenna_b.col - antenna_a.col
    antinode_list = []
    starting_antenna = antenna_b
    for i in range(2):
        antinode_row = starting_antenna.row + rise
        antinode_col = starting_antenna.col + run
        if(antinode_row >= 0 and
           antinode_row <= row_max and
           antinode_col >= 0 and
           antinode_col <= col_max):
            antinode_list.append(Antinode(antinode_row, antinode_col, antenna_a, antenna_b))
        rise = rise * -1
        run = run * -1
        starting_antenna = antenna_a
    return antinode_list

def print_map(antinode_list, antenna_dict, row_max, col_max):
    area_map = []
    for i in range(row_max + 1):
        area_map.append(['.'] * (col_max + 1))
    print(len(area_map))
    print(len(area_map[0]))
    for antinode in antinode_list:
        try:
            area_map[antinode.row][antinode.col] = '#'
        except:
            print(antinode)
    for key in antenna_dict:
        for antenna in antenna_dict[key]:
            area_map[antenna.row][antenna.col] = antenna.freq
    for row in area_map:
        print(''.join(row))

def part1() -> int:
    antenna_dict, (row_max, col_max) = create_antenna_dict()
    antinode_list = []
    for key in antenna_dict:
        for i in range(len(antenna_dict[key]) - 1):
            for j in range(i + 1, len(antenna_dict[key])):
                antinodes = create_antinodes(antenna_dict[key][i], antenna_dict[key][j], row_max, col_max)
                for antinode in antinodes:
                    if(antinode not in antinode_list):
                        antinode_list.append(antinode)
    return len(antinode_list)

def part2() -> int:
    return -1

if __name__ == "__main__":
    part1_ans = part1()
    print(f"ans to part 1 is {part1_ans}")
    part2_ans = part2()
    print(f"ans to part 2 is {part2_ans}")
