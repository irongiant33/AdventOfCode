import sys

def count_in_memory(line: str):
    count = 0
    i = 1
    while(i < len(line) - 1): # ignore start " and end "
        count += 1
        if(line[i] == "\\" and i + 1 < len(line) - 1):
            if(line[i + 1] == "\""):
                i += 1
            elif(line[i + 1] == "\\"):
                i += 1
            elif(line[i + 1] == "x"):
                i += 3
        i += 1
    return count

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day8.py input.txt")

    # part 1
    total_num_chars = 0
    in_memory_count = 0
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            total_num_chars += len(line.rstrip())
            in_memory_count += count_in_memory(line.rstrip())
    print(f"Answer to part 1 is {total_num_chars - in_memory_count}")

    # part 2
    count = 0 
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            line_count = 2 # starts with 2 chars, starting " and ending "
            i = 0
            while(i < len(line.rstrip())):
                line_count += 1
                if(line[i] == "\""):
                    line_count += 1
                if(line[i] == "\\"):
                    line_count += 1
                i += 1
            count += line_count
    print(f"Answer to part 2 is {count - total_num_chars}")
