# Read input from file
try:
    with open('input.txt', 'r') as file:
        instructions = file.readline().strip()
except FileNotFoundError:
    print("Error: Unable to open input file")
    exit(1)

# Part 1: Calculate final floor
floor = 0
for char in instructions:
    if char == '(':
        floor += 1
    elif char == ')':
        floor -= 1

# Part 2: Find position of first basement entry
current_floor = 0
position = 0
for i, char in enumerate(instructions, 1):  # 1-based indexing
    if char == '(':
        current_floor += 1
    elif char == ')':
        current_floor -= 1
    if current_floor == -1:
        position = i
        break

# Output results
print(f"Part 1: Final floor = {floor}")
print(f"Part 2: First basement position = {position}")
