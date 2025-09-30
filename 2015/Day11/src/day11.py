import re
import sys

DEBUG = False

def reqt1(string):
    for i in range(len(string) - 3):
        if(chr(ord(string[i]) + 1) != string[i + 1]):
            continue
        if(chr(ord(string[i]) + 2) != string[i + 2]):
            continue
        return True
    return False

def reqt2(string):
    if("i" in string or "o" in string or "l" in string):
        return False
    return True

def reqt3(string):
    pattern = r"((.)\2)"
    if(len(re.findall(pattern, string)) >= 2):
        return True
    return False

def increment(string):
    last_char = chr(ord(string[-1]) + 1)
    if(ord(last_char) >= ord("{")):
        string = increment(string[:-1]) + "a" 
        return string
    else:
        return string[:-1] + last_char

def solve_password(string):
    if(DEBUG):
        print(f"solving {string=}")
    conditions = [reqt1(string), reqt2(string), reqt3(string)]
    while(not conditions[0] or not conditions[1] or not conditions[2]):
        while(not conditions[1]):
            for i in range(len(string)):
                char = string[i]
                if(char == "i" or char == "o" or char == "l"):
                    prev_len = len(string[i+1:])
                    string = string[:i] + chr(ord(char) + 1)
                    string = string + "a"*prev_len
                    break
            if(DEBUG):
                print(f"Fixing reqt2, {string=}")
            conditions[1] = reqt2(string)
        string = increment(string)
        if(DEBUG):
            print(f"Incrementing {string=}")
        conditions = [reqt1(string), reqt2(string), reqt3(string)]
    return string

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day11.py testinput.txt")
    if(DEBUG):
        test_strings = {"hijklmmn":[True,False,False], "abbceffg":[False,True,True], "abbcegjk":[False,True,False], "abcdffaa":[True,True,True], "ghjaabcc":[True, True, True]}
        for string in test_strings:
            test_vals = [reqt1(string), reqt2(string), reqt3(string)]
            is_valid = test_vals == test_strings[string]
            print(f"Testing {string}: {test_vals=}, {'correct' if is_valid else 'incorrect'}")
            solve_password("ghjaabcb")
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            new_password = solve_password(line.rstrip())
            print(f"New password is {new_password}")
            new_new_password = solve_password(increment(new_password))
            print(f"New new password is {new_new_password}")
