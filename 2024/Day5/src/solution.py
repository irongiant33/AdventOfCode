FILENAME = "testinput.txt"

class Node:
    def __init__(self, value):
        self.next_nodes = []
        self.prev_nodes = []
        self.value = value
        self.cost = 0 # total number of previous nodes

    def add_next_node(self, node):
        self.next_nodes.append(node)

    def add_prev_node(self, node):
        self.prev_nodes.append(node)

    def has_value(self, value: int):
        return ((self == value) or (value in self.next_nodes))

    def __eq__(self, value: int):
        return self.value == value

    def __lt__(self, node):
        return self.cost < node.cost

    def __gt__(self, node):
        return self.cost > node.cost

    def __repr__(self):
        return f'Node {self.value} cost {self.cost}\nPrev {[node.value for node in self.prev_nodes]}\nNode {self.value} next {[node.value for node in self.next_nodes]}\n'

def count_prev(node):
    """
    count the number of nodes that come before this one
    """
    cost = 1
    if(len(node.prev_nodes) == 0):
        return cost
    for prev_node in node.prev_nodes:
        cost = cost + count_prev(prev_node)
    return cost

def parse_input():
    make_rules = True
    rules = {} # all Nodes with prev & next page numbers
    checks = [] # list of page numbers to check
    with open(FILENAME, "r") as fileobj:
        for line in fileobj:
            if(line.rstrip() == ''):
                make_rules = False
                continue
            if(make_rules):
                rule = [int(value) for value in line.rstrip().split('|')] # 0th index is first page, 1st index is next page
                base_node = None
                next_node = None
                if(rule[0] not in rules):
                    base_node = Node(rule[0])
                    rules[rule[0]] = base_node
                else:
                    base_node = rules[rule[0]]
                if(rule[1] not in rules):
                    next_node = Node(rule[1])
                    rules[rule[1]] = next_node
                else:
                    next_node = rules[rule[1]]

                base_node.add_next_node(next_node)
                next_node.add_prev_node(base_node)
            else:
                checks.append([int(value) for value in line.rstrip().split(',')])
    # assign cost
    for rule in rules:
        cost = count_prev(rules[rule])
        rules[rule].cost = cost
    return rules, checks

def check_ordering(rules: dict, ordering: list) -> bool:
    valid = True
    ordering = ordering[-1::-1]
    for i in range(0, len(ordering) - 1):
        try:
            node = rules[ordering[i]]
            for j in range(i + 1, len(ordering)):
                if(ordering[j] in node.next_nodes):
                    valid = False
                    break
        except KeyError:
            continue
    return valid

def part1():
    rules, checks = parse_input()
    middle_sum = 0
    for check in checks:
        valid = check_ordering(rules, check)
        if(valid):
            middle_sum = middle_sum + check[len(check) // 2]
    return middle_sum

def part2():
    rules, checks = parse_input()
    cost_sorted_nodes = sorted([rules[rule] for rule in rules]) 
    print(cost_sorted_nodes)
    middle_sum = 0
    for check in checks:
        valid = check_ordering(rules, check)
        if(not valid):
            for node in cost_sorted_nodes:
                if(node.value in check):
                    new_ordering = [node.value]
                    is_valid = True
                    while(len(new_ordering) < len(check) and is_valid):
                        for next_node in rules[new_ordering[-1]].next_nodes:
                            if(next_node.value in check):
                                new_ordering.append(next_node.value)
                                continue
                        is_valid = False
                    if(len(new_ordering) == len(check) and check_ordering(rules, new_ordering)):
                        middle_sum = middle_sum + new_ordering[len(new_ordering) // 2]
    return middle_sum

if __name__ == "__main__":
    part1_ans = part1()
    print(f"part 1 ans is {part1_ans}")
    part2_ans = part2()
    print(f"part 2 ans is {part2_ans}")
