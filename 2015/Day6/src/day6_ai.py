import re

def parse_instruction(line):
    match = re.match(r'(turn on|turn off|toggle) (\d+),(\d+) through (\d+),(\d+)', line)
    if not match:
        return None
    action, x1, y1, x2, y2 = match.groups()
    return action, int(x1), int(y1), int(x2), int(y2)

def part1(instructions):
    grid = [[False] * 1000 for _ in range(1000)]
    for action, x1, y1, x2, y2 in instructions:
        for i in range(x1, x2 + 1):
            for j in range(y1, y2 + 1):
                if action == 'turn on':
                    grid[i][j] = True
                elif action == 'turn off':
                    grid[i][j] = False
                else:  # toggle
                    grid[i][j] = not grid[i][j]
    return sum(row.count(True) for row in grid)

def part2(instructions):
    grid = [[0] * 1000 for _ in range(1000)]
    for action, x1, y1, x2, y2 in instructions:
        for i in range(x1, x2 + 1):
            for j in range(y1, y2 + 1):
                if action == 'turn on':
                    grid[i][j] += 1
                elif action == 'turn off':
                    grid[i][j] = max(0, grid[i][j] - 1)
                else:  # toggle
                    grid[i][j] += 2
    return sum(sum(row) for row in grid)

def main():
    with open('input.txt') as f:
        instructions = [parse_instruction(line.strip()) for line in f if parse_instruction(line.strip())]
    
    print("Part 1:", part1(instructions))  # Expected: 569999
    print("Part 2:", part2(instructions))  # Expected: 17836115

if __name__ == "__main__":
    main()