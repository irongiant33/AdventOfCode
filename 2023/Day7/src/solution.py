FIVEOFAKIND = 5
FOUROFAKIND = 4
FULLHOUSE = 3
THREEOFAKIND = 2
TWOPAIR = 1
ONEPAIR = 0
HIGHCARD = -1

def is_fiveofakind(sortedhand):
    card = sortedhand[0]
    fiveofakind = True
    index = 1
    while(fiveofakind and index < len(sortedhand)):
        fiveofakind = (card == sortedhand[index])
        index += 1
    return fiveofakind

def is_fourofakind(sortedhand):
    card = sortedhand[0]
    fourofakind = True
    index = 1
    while(index < 4):
        if(sortedhand[index] != card):
            fourofakind = False
            break
        index += 1
    if(not fourofakind):
        fourofakind = True
        card = sortedhand[1]
        index = 2
        while(index < 5):
            if(sortedhand[index] != card):
                fourofakind = False
                break
            index +=1 
    return fourofakind

def is_fullhouse(sortedhand):
    firstcard = sortedhand[0]
    lastcard = sortedhand[-1]
    if(firstcard == sortedhand[1] and firstcard == sortedhand[2] and lastcard == sortedhand[3]):
        return True
    if(firstcard == sortedhand[1] and lastcard == sortedhand[2] and lastcard == sortedhand[3]):
        return True
    return False

def is_threeofakind(sortedhand):
    consecutive = 1
    card = sortedhand[0]
    threeofakind = False
    for i in range(1, len(sortedhand)):
        if(sortedhand[i] == card):
            consecutive += 1
        else:
            card = sortedhand[i]
            consecutive = 1
        if(consecutive == 3):
            threeofakind = True
    return threeofakind

def part1(infilename):
    card_value_map = {
        'A':15,
        'K':14,
        'Q':13,
        'J':12,
        'T':11,
        '9':9,
        '8':8,
        '7':7,
        '6':6,
        '5':5,
        '4':4,
        '3':3,
        '2':2
    }
    hand_list = []
    debug = False
    debugcount = 0
    with open(infilename) as infile:
        for line in infile:
            hand, value = line.rstrip().split(" ")
            # original hand, sorted hand, hand rank (5 for 5 of a kind, 4 for 4 of a kind, 
            # 3 for full house, 2 for 3 of a kind, 1 for two pair, 0 for 1 pair, -1 for high card), value (i.e. bet)
            hand = list(hand)
            highcard_list = [card_value_map[item] for item in hand]
            hand.sort()
            sorted_list = [item for item in hand]
            hand_metadata = [highcard_list, sorted_list, HIGHCARD, int(value)]
            hand_list.append(hand_metadata)
    
    # determine the type of each hand
    for i in range(len(hand_list)):
        sorted_hand = hand_list[i][1]
        if(is_fiveofakind(sorted_hand)):
            hand_list[i][2] = FIVEOFAKIND
        elif(is_fourofakind(sorted_hand)):
            hand_list[i][2] = FOUROFAKIND
        elif(is_fullhouse(sorted_hand)):
            hand_list[i][2] = FULLHOUSE
        elif(is_threeofakind(sorted_hand)):
            hand_list[i][2] = THREEOFAKIND
        elif(len(set(sorted_hand)) == 3):
            hand_list[i][2] = TWOPAIR
        elif(len(set(sorted_hand)) == 4):
            hand_list[i][2] = ONEPAIR

    # sort based off of hand types
    sorted_types = sorted(hand_list, key=lambda x: (x[2], x[0]), reverse=True)
    if(debug):
        for hand in sorted_types:
            print(hand)

    sum = 0
    for i in range(len(sorted_types)):
        sum += sorted_types[i][3] * (len(sorted_types) - i)
    return sum

def part2(infilename):
    card_value_map = {
        'A':15,
        'K':14,
        'Q':13,
        'J':1,
        'T':11,
        '9':9,
        '8':8,
        '7':7,
        '6':6,
        '5':5,
        '4':4,
        '3':3,
        '2':2
    }
    hand_list = []
    debug = False
    debugcount = 0
    with open(infilename) as infile:
        for line in infile:
            hand, value = line.rstrip().split(" ")
            # original hand, sorted hand, hand rank (5 for 5 of a kind, 4 for 4 of a kind, 
            # 3 for full house, 2 for 3 of a kind, 1 for two pair, 0 for 1 pair, -1 for high card), value (i.e. bet)
            hand = list(hand)
            highcard_list = [card_value_map[item] for item in hand]
            hand.sort()
            sorted_list = [item for item in hand]
            hand_metadata = [highcard_list, sorted_list, HIGHCARD, int(value)]
            hand_list.append(hand_metadata)
    
    # determine the type of each hand
    for i in range(len(hand_list)):
        sorted_hand = hand_list[i][1]
        if(is_fiveofakind(sorted_hand)):
            hand_list[i][2] = FIVEOFAKIND
        elif(is_fourofakind(sorted_hand)):
            hand_list[i][2] = FOUROFAKIND
        elif(is_fullhouse(sorted_hand)):
            hand_list[i][2] = FULLHOUSE
        elif(is_threeofakind(sorted_hand)):
            hand_list[i][2] = THREEOFAKIND
        elif(len(set(sorted_hand)) == 3):
            hand_list[i][2] = TWOPAIR
        elif(len(set(sorted_hand)) == 4):
            hand_list[i][2] = ONEPAIR

    # sort based off of hand types
    sorted_types = sorted(hand_list, key=lambda x: (x[2], x[0]), reverse=True)
    if(debug):
        for hand in sorted_types:
            print(hand)

    sum = 0
    for i in range(len(sorted_types)):
        sum += sorted_types[i][3] * (len(sorted_types) - i)
    return sum

if __name__ == "__main__":
    part1ans = part1("input.txt")
    print(f"the answer to part 1 is: {part1ans}")

    part2ans = part2("input.txt")
    print(f"the answer to part 2 is: {part2ans}")