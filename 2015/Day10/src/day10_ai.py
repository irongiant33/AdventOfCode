import re

def look_and_say_once(sequence):
    # Split into groups of consecutive identical digits
    pattern = r'((.)\2*)'
    groups = [match[0] for match in re.findall(pattern, sequence)]
    
    # Generate the next sequence
    result = ''
    for group in groups:
        count = len(group)  # Number of digits in the group
        digit = group[0]    # The digit itself
        result += str(count) + digit
    return result

def look_and_say_n_times(file_path, iterations):
    # Read the initial sequence from input.txt
    try:
        with open(file_path, 'r') as file:
            sequence = file.read().strip()
    except FileNotFoundError:
        print(f"Error: {file_path} not found")
        return 0
    
    # Apply look-and-say process for the specified number of iterations
    for _ in range(iterations):
        sequence = look_and_say_once(sequence)
    
    return len(sequence)

# Solve both parts
file_path = 'input.txt'
part1_length = look_and_say_n_times(file_path, 40)
part2_length = look_and_say_n_times(file_path, 50)

print(f"Part 1 - Length after 40 iterations: {part1_length}")
print(f"Part 2 - Length after 50 iterations: {part2_length}")
