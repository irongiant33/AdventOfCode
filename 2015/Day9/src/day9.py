import copy
import re
import sys
import itertools

DEBUG = 0

if __name__ == "__main__":
    if(len(sys.argv) != 2):
        print("Usage: python3 day9.py input.txt")
        exit(1)
    pattern = r"(\w+) to (\w+) = (\d+)" 

    # build mappings
    unique_nodes = {}
    with open(sys.argv[1], "r") as fileobj:
        for line in fileobj:
            matches = re.match(pattern, line.rstrip())
            if(matches.groups()[0] not in unique_nodes):
                unique_nodes[matches.groups()[0]] = {matches.groups()[1]:int(matches.groups()[2])}
            else:
                unique_nodes[matches.groups()[0]][matches.groups()[1]] = int(matches.groups()[2])
            if(matches.groups()[1] not in unique_nodes):
                unique_nodes[matches.groups()[1]] = {matches.groups()[0]:int(matches.groups()[2])}
            else:
                unique_nodes[matches.groups()[1]][matches.groups()[0]] = int(matches.groups()[2])
    if(DEBUG):
        print(unique_nodes)

    # calculate cost for all paths - only works if all nodes have paths to every other node
    path_costs = []
    permutations = itertools.permutations(unique_nodes.keys())
    for permutation in permutations:
        cost = 0
        for i in range(len(permutation) - 1):
            cost += unique_nodes[permutation[i]][permutation[i + 1]]
            current_node = permutation[i]
        path_costs.append(cost)
        if(DEBUG):
            print(f"{permutation}, {cost=}")
    print(f"The answer to part 1 is {min(path_costs)}")
    print(f"The answer to part 2 is {max(path_costs)}")
