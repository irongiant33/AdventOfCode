import hashlib
import sys

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print('usage: python3 day4.py')
        exit(1)
    digit = 0
    hashstring = sys.argv[1]
    hashresult = hashlib.md5((hashstring + str(digit)).encode('utf-8'))
    while(hashresult.hexdigest()[0:5] != '00000'):
        digit += 1
        hashresult = hashlib.md5((hashstring + str(digit)).encode('utf-8'))
    print(f"The answer to part 1 is {digit}")

    digit = 0
    hashresult = hashlib.md5((hashstring + str(digit)).encode('utf-8'))
    while(hashresult.hexdigest()[0:6] != '000000'):
        digit += 1
        hashresult = hashlib.md5((hashstring + str(digit)).encode('utf-8'))
    print(f"The answer to part 2 is {digit}")
