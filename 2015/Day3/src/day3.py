import sys

direction = {'<':(-1, 0), '^':(0, 1), '>':(1, 0), 'v':(0, -1)}
debug = False

class Position:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __repr__(self):
        return f"({self.x}, {self.y})"

def pos_found(visited_dict, pos):
    for value, key in enumerate(visited_dict):
        if(pos.x == key.x and pos.y == key.y):
            return key
    return None

def find_num_visited(commands : list) -> int:
    old_pos = Position(0, 0)
    visited_dict = {old_pos:1}
    for command in commands:
        pos = Position(0,0)
        pos.x = old_pos.x + direction[command][0]
        pos.y = old_pos.y + direction[command][1]
        key = pos_found(visited_dict, pos)
        if(key == None):
            visited_dict[pos] = 1
        else:
            visited_dict[key] += 1
        old_pos = pos
        if(debug):
            print(visited_dict)
    return len(visited_dict)

def find_num_visited_part2(commands : list) -> int:
    old_santa_pos = Position(0, 0)
    old_robot_pos = Position(0, 0)
    visited_dict = {old_santa_pos:1}
    for i in range(0, len(commands), 2):
        santa_pos = Position(0,0)
        santa_pos.x = old_santa_pos.x + direction[commands[i]][0]
        santa_pos.y = old_santa_pos.y + direction[commands[i]][1]
        key = pos_found(visited_dict, santa_pos)
        if(key == None):
            visited_dict[santa_pos] = 1
        else:
            visited_dict[key] += 1
        old_santa_pos = santa_pos

        robot_pos = Position(0,0)
        robot_pos.x = old_robot_pos.x + direction[commands[i+1]][0]
        robot_pos.y = old_robot_pos.y + direction[commands[i+1]][1]
        key = pos_found(visited_dict, robot_pos)
        if(key == None):
            visited_dict[robot_pos] = 1
        else:
            visited_dict[key] += 1
        old_robot_pos = robot_pos
    return len(visited_dict)

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day2.py input.txt")
        exit
    commands = []
    with open(sys.argv[1], "r") as fileobj:
        commands = list(fileobj.read())
    while('\n' in commands):
        commands.remove('\n')
    num_visited = find_num_visited(commands)
    print(f"answer to part 1 is {num_visited}")

    num_visited = find_num_visited_part2(commands)
    print(f"answer to part 2 is {num_visited}")
