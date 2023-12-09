import re

def part1(input_filename):
    sum = 0
    count = 0
    debug = False
    with open(input_filename) as infile:
        for line in infile:
            line_numbers = re.findall('\d', line.rstrip())
            value = int(line_numbers[0] + line_numbers[-1])
            sum += value
            if(debug and count < 10):
                print(f"{value} {sum}")
                count += 1
            elif(debug):
                break
           
    return sum

def part2(input_filename):
    number_map = {
        "one": 1,
        "two": 2,
        "three": 3,
        "four":4,
        "five":5,
        "six":6,
        "seven":7,
        "eight":8,
        "nine":9
    }
    with open(input_filename) as infile:
      sum = 0
      count = 0
      debug = False
      for line in infile:
            new_line = line.rstrip()
            for spelled_out, numeric_value in number_map.items():
                start_index = 0
                while(start_index < len(new_line)):
                    index = new_line.find(spelled_out, start_index)
                    if(index == -1):
                        break
                    start_index = index + 1
                    new_line = new_line[:start_index] + str(numeric_value) + new_line[start_index:]
                   
            line_numbers = re.findall('\d', new_line)
            value = line_numbers[0] + line_numbers[-1]
            sum += int(value)
            if(debug and count < 7):
                print(f"{line} {new_line}")
                print(f"{value} {sum}")
                count += 1
            elif(debug):
                break
      return sum
   
if __name__=="__main__":
    part1 = part1("input.txt")
    print(f"The value of part 1 is: {part1}")
   
    part2 = part2("input.txt")
    print(f"The value of part 2 is: {part2}") 