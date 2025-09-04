FILENAME = "input.txt"

def part1():
    with open(FILENAME, "r") as fileobj:
        total_count = 0
        for line in fileobj:
            left, equation = line.rstrip().split(":")
            left_val = int(left)
            equation_vals = [int(value) for value in equation.strip().split(' ')]
            # print(f"{left_val}: {equation_vals}")
            math_instruction = 0 # map the gaps of the equation_vals to bits in this number. If the bit is 1, add. If the bit is 0, multiply.
            for i in range(2**(len(equation_vals) - 1)):
                # print(f"math_instruction: {math_instruction}")
                result = equation_vals[0]
                for j in range(len(equation_vals) - 1):
                    do_add = (math_instruction & 2**(len(equation_vals) - 2 - j)) >> (len(equation_vals) - 2 -j)
                    # print(f"do_add: {do_add}")
                    if(do_add):
                        result = result + equation_vals[j + 1]
                    else:
                        result = result * equation_vals[j + 1]
                if(result == left_val):
                    total_count = total_count + left_val
                    break
                else:
                    math_instruction = math_instruction + 1
        return total_count


def part2():
    return -1

if __name__ == "__main__":
    part1_ans = part1()
    print(f'part 1 answer is {part1_ans}')
    part2_ans = part2()
    print(f'part 2 answer is {part2_ans}')
