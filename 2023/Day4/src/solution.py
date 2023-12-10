import re

def part1(infilename):
    winningpattern = "Card\s+\d+:\s+(\d+(?:\s+\d+)*) \|"
    cardpattern = "\|\s+(\d+(?:\s+\d+)*)$"
    sum = 0
    debug = False
    debugcount = 0
    with open(infilename) as infile:
        for line in infile:
            gamesum =0
            winningnums_match = re.search(winningpattern, line.rstrip())
            cardnums_match = re.search(cardpattern, line.rstrip())
            winningnums = []
            cardnums = []
            if winningnums_match:
                winningnums = list(map(int, winningnums_match.group(1).split()))
            else:
                print("no match detected, exiting")
                exit
            if cardnums_match:
                cardnums = list(map(int, cardnums_match.group(1).split()))
            else:
                 print("no match detected, exiting")
                 exit
            
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
    winningpattern = "Card\s+\d+:\s+(\d+(?:\s+\d+)*) \|"
    cardpattern = "\|\s+(\d+(?:\s+\d+)*)$"
    card_dict = {}
    card_count = 1
    sum = 0
    debug = False
    debugcount = 0
    with open(infilename) as infile:
        for line in infile:
            gamesum =0
            winningnums_match = re.search(winningpattern, line.rstrip())
            cardnums_match = re.search(cardpattern, line.rstrip())
            winningnums = []
            cardnums = []
            if winningnums_match:
                winningnums = list(map(int, winningnums_match.group(1).split()))
            else:
                print("no match detected, exiting")
                exit
            if cardnums_match:
                cardnums = list(map(int, cardnums_match.group(1).split()))
            else:
                 print("no match detected, exiting")
                 exit
            
            num_wins = 0
            for winningnum in winningnums:
                if winningnum in cardnums:
                    num_wins += 1
            sum += gamesum
            card_dict[card_count] = [1, num_wins]
            card_count += 1
    total_copies = 0
    for i in range(1, card_count):
        if debug and debugcount < 6:
            print(card_dict[i])
            debugcount += 1
        elif debug:
            break
        total_copies += card_dict[i][0]
        for j in range(card_dict[i][1]):
            if(i + j + 1 < card_count):
                card_dict[i + j + 1][0] += card_dict[i][0]
    return total_copies
           
if __name__=="__main__":
    part1ans = part1("input.txt")
    print(f"part 1 answer is {part1ans}")
   
    part2ans = part2("input.txt")
    print(f"The answer to part 2 is {part2ans}") 