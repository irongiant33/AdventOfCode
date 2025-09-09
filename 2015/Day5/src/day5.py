import sys
debug = False

def check_nice(line : str)->int:
    if(debug):
        print(f"Line: {line}")
    num_vowels = 0
    for vowel in ['a','e','i','o','u']:
        if vowel in line:
            num_vowels += line.count(vowel)
    last_char = ''
    has_consecutive_chars = False
    for char in line:
        if char == last_char:
            has_consecutive_chars = True
            break
        last_char = char
    has_bad_strings = False
    bad_strings = ['ab', 'cd', 'pq', 'xy']
    for bad_string in bad_strings:
        if bad_string in line:
            has_bad_strings = True
            break
    if(debug):
        print(f"{has_bad_strings=}, {has_consecutive_chars=}, {num_vowels=}")
    if(not has_bad_strings and has_consecutive_chars and num_vowels >= 3):
        return 1
    return 0

def check_other_nice(line : str) -> int:
    if(debug):
        print(f"{line=}")
    has_multiple_nonconsecutive = False
    for i in range(len(line) - 3):
        first_pair = line[i] + line[i+1]
        for j in range(i + 2, len(line) - 1):
            second_pair = line[j] + line[j+1]
            if(first_pair == second_pair):
                has_multiple_nonconsecutive = True
                if(debug):
                    print(f"{first_pair=} {i=}, {second_pair=} {j=}")
                break
        if(has_multiple_nonconsecutive):
            break

    has_sandwich_letters = False
    for i in range(len(line) - 2):
        if line[i] == line[i + 2]:
            has_sandwich_letters = True
            break

    if(debug):
        print(f"{has_sandwich_letters=}, {has_multiple_nonconsecutive=}\n")
    if(has_sandwich_letters and has_multiple_nonconsecutive):
        return 1
    return 0

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day5.py input.txt")
        exit(1)
    num_nice_part1 = 0
    num_nice_part2 = 0
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            num_nice_part1 += check_nice(line.rstrip())
            num_nice_part2 += check_other_nice(line.rstrip())
    print(f"Answer to part 1 is {num_nice_part1}")
    print(f"Answer to part 2 is {num_nice_part2}")

