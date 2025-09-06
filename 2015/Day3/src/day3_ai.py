def count_houses(directions):
    # Set to track unique house coordinates
    visited = {(0, 0)}  # Start at origin
    x, y = 0, 0  # Santa's position

    # Process each direction
    for direction in directions:
        if direction == '^':
            y += 1
        elif direction == 'v':
            y -= 1
        elif direction == '>':
            x += 1
        elif direction == '<':
            x -= 1
        visited.add((x, y))

    return len(visited)

def count_houses_with_robo(directions):
    # Sets to track unique house coordinates
    visited = {(0, 0)}  # Start at origin (both deliver here)
    santa_x, santa_y = 0, 0  # Santa's position
    robo_x, robo_y = 0, 0  # Robo-Santa's position

    # Alternate moves between Santa and Robo-Santa
    for i, direction in enumerate(directions):
        if i % 2 == 0:  # Santa's turn
            if direction == '^':
                santa_y += 1
            elif direction == 'v':
                santa_y -= 1
            elif direction == '>':
                santa_x += 1
            elif direction == '<':
                santa_x -= 1
            visited.add((santa_x, santa_y))
        else:  # Robo-Santa's turn
            if direction == '^':
                robo_y += 1
            elif direction == 'v':
                robo_y -= 1
            elif direction == '>':
                robo_x += 1
            elif direction == '<':
                robo_x -= 1
            visited.add((robo_x, robo_y))

    return len(visited)

# Read input from file
try:
    with open('input.txt', 'r') as file:
        directions = file.readline().strip()
except FileNotFoundError:
    print("Error: Unable to open input file")
    exit(1)

# Part 1: Count houses with only Santa
part1 = count_houses(directions)

# Part 2: Count houses with Santa and Robo-Santa
part2 = count_houses_with_robo(directions)

# Output results
print(f"Part 1: Houses with at least one present = {part1}")
print(f"Part 2: Houses with at least one present = {part2}")
