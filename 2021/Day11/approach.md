# Problem Solving Approach

## Part 1

1. read in input with no delimiters, but filter by index such that you filter out every `\n` character.
2. create doubly linked list of nodes that contain octopuses that have flashed for that step. create a 2D matrix of graph nodes corresponding to the octopus input
3. Initialize the number of flashes to 0 and then for each step:
    1. if the value of the node is greater than 9, set the value to 0.
    2. increase the value of all nodes by 1. if the value is greater than 9, then add this octopus to the flashed list
    3. for all octopuses in the flashed list, add 1 to their neighbors. if their value exceeds 9, add them to the flashed list if they are not already in it.
    4. add the size of the flashed list to the running number of flashes and remove all items from the flashed list
4. return the number of flashes and free

## Part 2

1. repeat the same process in part 1, except use a while loop instead of a for loop for the number of steps. set the while loop condition to break if the size of the flashed list equals the size of the input.
2. return the index at which this occurred.
