# Problem Solving Approach

## Part 1

1. Determine how many bits are on a line and call it $N$
2. Use newline as an input delimiter
3. Initialize an array of ints with length $N$ to track the most common bit in each position
4. For each input:
    1. For every bit in the input:
        1. If the bit is 1, add 1 to the same index in the int array
        2. If the bit is 0, subtract 1 from the same index in the int array
5. Initialize the gamma and epsilon values to 0
6. For each index $i$ in the int array:
    1. If the value at $i$ is positive, there were more 1's than 0's. Add $2^{N - i -1}$ to the gamma value
    2. If the value is negative, there were more 0's than 1's. Add $2^{N - i -1}$ to the epsilon value.
7. Multiply the gamma and epsilon values

## Part 2

### Main

1. Use steps 1-4 of above process.
2. Create a function called "frequency_selective_filter" that takes the int array & most/least common flag as input and returns a single puzzle_item_t pointer.
3. Obtain value from frequency_selective_filter with most common flag set, call it $m$
4. Obtain value from frequency_selective_filter with least common flag set, call it $l$
5. Convert $l$ and $m$ from binary and multiply them together

### from frequency_selective_filter

1. Accept most/least common flag & int array of which value is most/least common at each bit position
2. Read in the input file and store each input as an item in a doubly linked list
3. While there are more than 1 item in the doubly linked list and the bit position is less than $N$:
    1. remove all items from the list if the current bit position is not equal to the most/least common flag
    2. increment the bit position
    3. re-evaluate the bit frequencies from the current bit position forward. concede ties to high bit (1)
4. If there is more than 1 item in the list, throw an error
5. Otherwise return the only remaining value
