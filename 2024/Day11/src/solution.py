FILENAME = "input.txt"
DEBUG = False

class Stone:
    def __init__(self, value):
        self.value = value
        self.transition = [1] # number of stones at each number of blinks

    def __eq__(self, other):
        return self.value == other.value

    def __repr__(self):
        return str(self.value)

def part1(end_state=25):
    input_stones = []
    with open(FILENAME, "r" ) as fileobj:
        input_stones = [Stone(int(value)) for value in fileobj.readline().rstrip().split(' ')]
    
    stone_freqs = {} # map stones to the number of times they appear
    for stone in input_stones:
        stone_freqs[stone.value] = 1
    stone_archive = {}
    for i in range(end_state):
        next_stone_freqs = {}
        if(DEBUG):
            print(f' iteration {i}: {stone_freqs}')
        for value in stone_freqs:
            frequency = stone_freqs[value]
            if(value in stone_archive):
                for next_stone in stone_archive[value]:
                    if(next_stone.value in next_stone_freqs):
                        next_stone_freqs[next_stone.value] += frequency
                    else:
                        next_stone_freqs[next_stone.value] = frequency
            else:
                stone_str = str(value)
                length = len(stone_str)
                if(length % 2 == 0):
                    stone_archive[value] = [Stone(int(stone_str[0:(length//2)])), Stone(int(stone_str[(length//2):]))]
                elif(value == 0):
                    stone_archive[value] = [Stone(1)]
                else:
                    stone_archive[value] = [Stone(value * 2024)]
                for next_stone in stone_archive[value]: 
                    if(next_stone.value in next_stone_freqs):
                        next_stone_freqs[next_stone.value] += frequency 
                    else:
                        next_stone_freqs[next_stone.value] = frequency
        stone_freqs = next_stone_freqs
    stone_count = 0
    for stone_value in stone_freqs:
        stone_count += stone_freqs[stone_value]
    return stone_count

def part2(end_state=75):
    return part1(end_state)

if __name__ == "__main__":
    part1_ans = part1()
    print(f"part 1 ans is {part1_ans}")
    part2_ans = part2()
    print(f'part 2 ans is {part2_ans}')
