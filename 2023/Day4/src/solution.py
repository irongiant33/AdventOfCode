import re

def part1(infilename):
    winningpattern = "(\d+)\s*|\s*(\d+)"
    cardpattern = re.compile("(?=\| )(\d+)*")
    sum = 0
    debug = True
    debugcount = 0
    with open(infilename) as infile:
        for line in infile:
            gamesum =0
            winningnums = re.findall(winningpattern, line.rstrip())
            cardnums = cardpattern.match(line.rstrip())
            if debug and debugcount < 7:
                print(winningnums)
                print(cardnums)
            for winningnum in winningnums:
                if winningnum in cardnums:
                    gamesum *= 2
                    if gamesum == 0:
                        gamesum = 1
            sum += gamesum
            if debug and debugcount < 7:
                debugcount += 1
                print(gamesum)
    return sum
   
def part2(infilename):
            pass
           
if __name__=="__main__":
    part1ans = part1("day4.txt")
    print(f"part 1 answer is {part1ans}")
   
    part2ans = part2("day4.txt")
    print(f"The answer to part 2 is {part2ans}") 