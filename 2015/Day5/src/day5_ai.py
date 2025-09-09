def has_three_vowels(s: str) -> bool:
    """Check if string has at least three vowels (aeiou)."""
    vowels = 'aeiou'
    return sum(1 for char in s if char in vowels) >= 3

def has_double_letter(s: str) -> bool:
    """Check if string has at least one letter appearing twice in a row."""
    for i in range(len(s) - 1):
        if s[i] == s[i + 1]:
            return True
    return False

def has_no_disallowed(s: str) -> bool:
    """Check if string does not contain ab, cd, pq, or xy."""
    disallowed = {'ab', 'cd', 'pq', 'xy'}
    for i in range(len(s) - 1):
        if s[i:i + 2] in disallowed:
            return False
    return True

def is_nice_part1(s: str) -> bool:
    """Check if string is nice under Part 1 rules."""
    return has_three_vowels(s) and has_double_letter(s) and has_no_disallowed(s)

def has_pair_twice(s: str) -> bool:
    """Check if string has a pair of letters appearing at least twice without overlap."""
    seen_pairs = {}
    for i in range(len(s) - 1):
        pair = s[i:i + 2]
        if pair in seen_pairs:
            # Check for overlap (pair must not start at the previous pair's end)
            if i > seen_pairs[pair] + 1:
                return True
        else:
            seen_pairs[pair] = i
    return False

def has_repeat_with_one_between(s: str) -> bool:
    """Check if string has a letter repeating with exactly one letter between."""
    for i in range(len(s) - 2):
        if s[i] == s[i + 2]:
            return True
    return False

def is_nice_part2(s: str) -> bool:
    """Check if string is nice under Part 2 rules."""
    return has_pair_twice(s) and has_repeat_with_one_between(s)

def count_nice_strings(filename: str) -> tuple[int, int]:
    """Count nice strings for both parts from the input file."""
    nice_count_part1 = 0
    nice_count_part2 = 0
    
    with open(filename, 'r') as file:
        for line in file:
            s = line.strip()
            if is_nice_part1(s):
                nice_count_part1 += 1
            if is_nice_part2(s):
                nice_count_part2 += 1
                
    return nice_count_part1, nice_count_part2

# Replace 'input.txt' with the path to your input file
filename = 'input.txt'
part1_count, part2_count = count_nice_strings(filename)
print(f"Part 1: {part1_count} nice strings")
print(f"Part 2: {part2_count} nice strings")