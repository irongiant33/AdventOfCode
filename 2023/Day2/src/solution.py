import re

def part1(input_filename):
    bag_config = {
        "red": 12,
        "blue":14,
        "green":13
    }
    with open(input_filename) as infile:
        sum = 0
        debug = False
        debugcount = 0
        game_count = 1
        pattern = re.compile("(\d+)\s(\w+)")
        for line in infile:
            if debug and debugcount > 10:
                break
            debugcount += 1
            add = True
            matches = pattern.findall(line.rstrip())
            if not matches:
                continue
            for match in matches:
                digit, color = match[0], match[1]
                if(bag_config[color] < int(digit)):
                    add = False
                    break
                if(not add):
                    break
            if(add):
                sum += game_count
            game_count += 1
        return sum
       
def part2(input_filename):
    sum = 0
    debug = False
    debugcount = 0
    pattern = re.compile("(\d+)\s(\w+)")
    with open(input_filename) as infile:
        for line in infile:
            bag_config = {
                 "red":0,
                 "green":0,
                 "blue":0
            }
            if debug and debugcount > 7:
                break
            debugcount += 1
            matches = pattern.findall(line.rstrip())
            if not matches:
                continue
            for match in matches:
                if bag_config[match[1]] < int(match[0]):
                    bag_config[match[1]] = int(match[0])
            product = 1
            for value in bag_config.values():
                if debug:
                    print(f"{value} ", end="")
                product *= value
            sum += product
            if debug:
                print(line.rstrip())
    return sum
           

if __name__=="__main__":
    part1_ans = part1("input.txt")
    print(f"The answer to part 1 is: {part1_ans}")
   
    part2_ans = part2("input.txt")
    print(f"The answer to part 2 is: {part2_ans}") 