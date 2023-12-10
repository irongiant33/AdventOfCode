import re

rule_list = []

def part1(infilename):
    seed_pattern = "seeds:\s+(\d+(?:\s+\d+)*)"
    rule_pattern = "(\d+(?:\s+\d+)*)"
    nextseeds = [-1]
    with open(infilename) as infile:
        startingseed_match = re.search(seed_pattern, infile.readline().rstrip())
        if not startingseed_match:
            print("starting seed match not found ,exiting")
            exit
        startingseeds = list(map(int, startingseed_match.group(1).split()))
        nextseeds = [startingseeds[i] for i in range(len(startingseeds))]
        rules_complete = False
        for line in infile:
            rule_match = re.search(rule_pattern, line.rstrip())
            if(rule_match):
                rule_values = list(map(int, rule_match.group(1).split()))
                # assume that each of the original seed values can only fall within one rule range
                for i in range(len(startingseeds)):
                    if(startingseeds[i] >= rule_values[1] and startingseeds[i] < (rule_values[1] + rule_values[2])):
                        nextseeds[i] += rule_values[0] - rule_values[1]
            else:
                rules_complete = True

            if(rules_complete):
                startingseeds = [nextseeds[i] for i in range(len(nextseeds))]
                rules_complete = False
    return min(nextseeds)

def update_rule_list(newrule, debug=False):
    if(newrule[1] - newrule[0] <= 0):
        return
    
    # philosophy is you queue rules up, copy the rule list over to a new list given the rule you're working on, and then keep going through the queue. This avoids recursion
    # for interior: add surrounding ranges to the new list, update the current rule delta value
    # for full: add the range to the new list updating its delta value, update the range of your current rule, and queue another rule with the other range
    # for overlap: add nonoverlapping range to the new list, queue the overlapping range with updated delta value, update the range of your current rule.
    rule_queue = [newrule]
    while(len(rule_queue) > 0):

        for rule in rule_list:
            # upper half overlap, update old upperbound, new lowerbound, create new rule - creates 3 rules
            if(newrule[0] >  rule[0] and newrule[0] < rule[1] and newrule[1] > rule[1]):
                if(debug):
                    print('upper overlap',flush=True)
                newupperbound = rule[1]
                newlowerbound = newrule[0]
                rule[1] = newlowerbound
                newrule[0] = newupperbound
                update_rule_list([newlowerbound, newupperbound, rule[2] + newrule[2]])

            # lower half overlap, update old lowerbound, new upperbound, create new rule - creates 3 rules
            if(newrule[1] > rule[0] and newrule[1] < rule[1] and newrule[0] < rule[0]):
                if(debug):
                    print('lower overlap',flush=True)
                newupperbound = newrule[1]
                newlowerbound = rule[0]
                rule[0] = newupperbound
                newrule[1] = newlowerbound
                update_rule_list([newlowerbound, newupperbound, rule[2] + newrule[2]])

            # full overlap - creates 3 rules
            if(rule[0] >= newrule[0] and rule[1] <= newrule[1]):
                if(debug):
                    print(f'full overlap {rule} {newrule}',flush=True)
                rule[2] = rule[2] + newrule[2]
                update_rule_list([newrule[0], rule[0], newrule[2]])
                update_rule_list([rule[1], newrule[1], newrule[2]])

            # interior overlap - creates 3 rules
            if((rule[0] < newrule[0] and rule[1] >= newrule[1]) or (rule[0] <= newrule[0] and rule[1] > newrule[1])):
                if(debug):
                    print('interior overlap',flush=True)
                temp = rule[1]
                rule[1] = newrule[0]
                if(rule[1] - rule[0] <= 0):
                    rule_list.remove(rule)
                newrule[2] = rule[2] + newrule[2]
                update_rule_list([newrule[1], temp, rule[2]])

    if(newrule[1] - newrule[0] > 0):
        rule_list.append(newrule)
    return

def part2(infilename):
    seed_pattern = "seeds:\s+(\d+(?:\s+\d+)*)"
    rule_pattern = "(\d+(?:\s+\d+)*)"
    lowest_number = -1
    debug = True
    debugcount = 0
    with open(infilename) as infile:
        startingseed_match = re.search(seed_pattern, infile.readline().rstrip())
        if not startingseed_match:
            print("starting seed match not found ,exiting")
            exit
        startingseeds = list(map(int, startingseed_match.group(1).split()))
        lowest_number = max(startingseeds)
        for line in infile:
            rule_match = re.search(rule_pattern, line.rstrip())
            if(rule_match):
                rule_values = list(map(int, rule_match.group(1).split()))
                rule = [rule_values[1], (rule_values[1]+rule_values[2]), (rule_values[0]-rule_values[1])] # start, stop, step
                update_rule_list(rule, debug=debug)
            if(debug and debugcount < 15):
                print(rule_list)
                debugcount += 1
            elif(debug):
                exit

        sorted_rule_list = sorted(rule_list, key=lambda x: x[0])

        for i in range(0, len(startingseeds), 2):
            for j in range(startingseeds[i], startingseeds[i+1]):
                rule_index = 0
                while(not (j >= sorted_rule_list[rule_index][0] and j < sorted_rule_list[rule_index][1])):
                    rule_index += 1
                location = sorted_rule_list[rule_index][2] + j
                if(location < lowest_number):
                    lowest_number = location
    return lowest_number

if __name__ == "__main__":
    part1_ans = part1("input.txt")
    print(f"the answer to part 1 is: {part1_ans}")

    part2_ans = part2("testinput.txt")
    print(f"the answer to part 2 is: {part2_ans}")