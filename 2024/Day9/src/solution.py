FILENAME = "input.txt"
DEBUG = False

class Block:
    def __init__(self, pos, size, mem_id):
        self.size = size
        self.mem_id = mem_id
        self.pos = pos
        self.moved = False
    
    def get_pos(self):
        return self.pos

def calculate_checksum(disk_format: list) -> int:
    checksum = 0
    for i in range(len(disk_format)):
        if(disk_format[i] > -1):
            checksum = checksum + disk_format[i] * i
    return checksum

def get_disk_input() -> list:
    string_input = ""
    with open(FILENAME, "r") as fileobj:
        string_input = fileobj.readline().rstrip()
    disk_input = [int(value) for value in list(string_input)]
    return disk_input

def part1():
    disk_input = get_disk_input()
    disk_format = []
    memory_id = 0
    min_free_index = 2**10 # arbitrarily large number
    max_mem_index = -1
    for i in range(len(disk_input)):
        if(i % 2 == 0): # signifies number of memory blocks
            disk_format.extend([memory_id] * disk_input[i])
            max_mem_index = len(disk_format) - 1
            memory_id = memory_id + 1
        else: # signifies amount of free space
            if(len(disk_format) < min_free_index):
                min_free_index = len(disk_format)
            disk_format.extend([-1] * disk_input[i])
    while(min_free_index < max_mem_index):
        disk_format[min_free_index] = disk_format[max_mem_index]
        disk_format[max_mem_index] = -1
        for i in range(min_free_index + 1, len(disk_format)):
            if(disk_format[i] == -1):
                min_free_index = i
                break
            if(i == (len(disk_format) - 1)):
                min_free_index = len(disk_format)
        for i in range(max_mem_index - 1, -1, -1):
            if(disk_format[i] > -1):
                max_mem_index = i
                break
            if(i == 0):
                max_mem_index = -1
    return calculate_checksum(disk_format)
    
def convert_memory_blocks_to_disk_format(memory_blocks):
    disk_format = []
    sorted_memory_blocks = sorted(memory_blocks, key=Block.get_pos)
    for block in sorted_memory_blocks:
        if block.pos > len(disk_format):
            disk_format.extend([-1] * (block.pos - len(disk_format)))
        disk_format.extend([block.mem_id] * block.size)
    return disk_format

def print_disk_format(disk_format: list):
    disk_string = ""
    for val in disk_format:
        if(val >= 0):
            disk_string = disk_string + str(val) + ' '
        else:
            disk_string = disk_string + '. '
    print(disk_string)
    
def part2():
    disk_input = get_disk_input()
    memory_id = 0
    memory_blocks = []
    free_blocks = []
    pos = 0
    for i in range(len(disk_input)):
        if(disk_input[i] == 0):
            continue
        if(i % 2 == 0): # signifies number of memory blocks
            memory_blocks.append(Block(pos, disk_input[i], memory_id))
            pos = pos + disk_input[i]
            memory_id = memory_id + 1
        else: # signifies empty space
            free_blocks.append(Block(pos, disk_input[i], -1))
            pos = pos + disk_input[i]
    num_free_blocks = len(free_blocks) 
    if(DEBUG):
        disk_format = convert_memory_blocks_to_disk_format(memory_blocks)
        print_disk_format(disk_format)
    for i in range(len(memory_blocks) - 1, -1, -1): # step through memory blocks
        for j in range(num_free_blocks):
            if(free_blocks[j].pos > memory_blocks[i].pos):
                break
            if(free_blocks[j].size >= memory_blocks[i].size):
                free_blocks[j].size = free_blocks[j].size - memory_blocks[i].size
                memory_blocks[i].pos = free_blocks[j].pos
                memory_blocks[i].moved = True # even though I technically don't need this because I shouldn't revisit this block
                free_blocks[j].pos  = free_blocks[j].pos  + memory_blocks[i].size
                break
        if(DEBUG):
            disk_format = convert_memory_blocks_to_disk_format(memory_blocks)
            print_disk_format(disk_format)
    disk_format = convert_memory_blocks_to_disk_format(memory_blocks)
    return calculate_checksum(disk_format)

if __name__=="__main__":
    part1_ans = part1()
    print(f"answer to part 1 is {part1_ans}")
    part2_ans = part2()
    print(f"answer to part 2 is {part2_ans}")
