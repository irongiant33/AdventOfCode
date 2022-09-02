# Problem Solving Approach

## Part 1

1. Read in input by using a `-` as well as a newline delimiter. The puzzle input at 0, 2, 4, 6... will be connected to the respective input at 1, 3, 5, 7...etc. on the graph.
2. For each puzzle input:
    1. determine if the puzzle input is already in the list of nodes
    2. if the puzzle is not in the list of nodes, create a new node pointing to a cave struct. Repeat sub-step 1 and 2 for its connected puzzle input. Add the connected puzzle input to the node's neighbor list.
3. Beginning with the node named "start" and an list of paths with 1 item `[start]`:
    1. create a new path for each neighbor that can be visited and add that path to the path list.
    2. if the next node is a small cave and it is already in the path, don't add it.
    3. if the current node is "end", do not add any more paths.
    4. while new nodes are being added to paths, repeat sub-step 1-3.
4. return the number of paths

### cave struct

```C
char * label;
bool is_big; //the cave can be visited multiple times
bool is_end; //the ending cave
```

### example 1 walkthrough

step 0:
path list: [
    [start]
    ]

step 1:
path list: [
    [start, A],
    [start, b]
    ]

step 2:
path list: [
    [start, A, c],
    [start, A, end],
    [start, A, b],
    [start, b, A],
    [start, b, end],
    [start, b, d]
    ]

step 3 (note [start, b, d] removed because no more valid nodes and the path does not terminate with `end`):
path list: [
    [start, A, c, A],
    [start, A, end],
    [start, A, b, A],
    [start, A, b, end],
    [start, A, b, d],
    [start, b, A, c],
    [start, b, A, end],
    [start, b, end]
    ]

step 4: (note [start, A, b, d] removed because there are no more searchable nodes and the path doesn't terminate with `end`)
path list: [
    [start, A, c, A, end],
    [start, A, c, A, b],
    [start, A, end],
    [start, A, b, A, c],
    [start, A, b, A, end],
    [start, A, b, end],
    [start, b, A, c, A],
    [start, b, A, end],
    [start, b, end]
    ]

step 5:
path list: [
    [start, A, c, A, end],
    [start, A, c, A, b, A],
    [start, A, c, A, b, d],
    [start, A, c, A, b, end],
    [start, A, end],
    [start, A, b, A, c, A],
    [start, A, b, A, end],
    [start, A, b, end],
    [start, b, A, c, A, end],
    [start, b, A, end],
    [start, b, end]
    ]

step 6: ([start, A, c, A, b, d] terminated)
path list: [
    [start, A, c, A, end],
    [start, A, c, A, b, A, end],
    [start, A, c, A, b, end],
    [start, A, end],
    [start, A, b, A, c, A, end],
    [start, A, b, A, end],
    [start, A, b, end],
    [start, b, A, c, A, end],
    [start, b, A, end],
    [start, b, end]
    ]

No more nodes to add in step 7. There are a total of 10 paths in the list.

## Part 2

My solution is TERRIBLY inefficient. It takes forever to run. I need to improve the performance of my data structures and even consider the design of the data structures when running these large programs.

One small cave can now be visited twice. Keep a linked list of flags in parallel
with the path list to keep track of whether a small cave has been visited twice or not.
Modify the add condition to check the following:
- if the cave is big, you can add it
- if the cave is small and it isn't in the list, add it
- if the cave is small, it isn't "start" or "end", it is in the list, and if the flag is not set, add it and set the flag

Example Walkthrough:

step 0 (1)
path list: [
    start
]

step 1 (2)
path list: [
    start, A
    start, b
]

step 2: (6)
path list: [
    start, A, c
    start, A, end
    start, A, b
    start, b, A
    start, b, end
    start, b, d
]

step 3: (10)
path list: [
    start, A, c, A
    start, A, end
    start, A, b, A
    start, A, b, end
    start, A, b, d
    start, b, A, c
    start, b, A, end
    start, b, A, b
    start, b, end
    start, b, d, b
]

step 4: (17)
path list: [
    start, A, c, A, c
    start, A, c, A, end
    start, A, c, A, b
    start, A, end
    start, A, b, A, c
    start, A, b, A, end
    start, A, b, A, b
    start, A, b, end
    start, A, b, d, b
    start, b, A, c, A
    start, b, A, end
    start, b, A, b, A
    start, b, A, b, end
    start, b, A, b, d
    start, b, end
    start, b, d, b, A
    start, b, d, b, end
]

step 5: (25)
path list: [
    start, A, c, A, c, A
    start, A, c, A, end
    start, A, c, A, b, A
    start, A, c, A, b, end
    start, A, c, A, b, d
    start, A, end
    start, A, b, A, c, A
    start, A, b, A, end
    start, A, b, A, b, A
    start, A, b, A, b, end
    start, A, b, A, b, d
    start, A, b, end
    start, A, b, d, b, A
    start, A, b, d, b, end
    start, b, A, c, A, c
    start, b, A, c, A, end
    start, b, A, c, A, b XXXXXX
    start, b, A, end
    start, b, A, b, A, c
    start, b, A, b, A, end
    start, b, A, b, end
    start, b, end
    start, b, d, b, A, c
    start, b, d, b, A, end
    start, b, d, b, end
]