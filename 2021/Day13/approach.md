# Problem Solving Approach

## Part 1

1. read in input with delimiter `,`, `\n`, `=`.
2. find the input with length 0, this is the delimiter between the fold instructions and the points
3. find the maximum x and y input
4. create a 2d integer matrix that corresponds to the size of the maximum X and Y input that you've received in the puzzle.
5. for every 2 inputs, add 1 to the integer matrix at those coordinates.
6. parse through the fold instructions and make the following translations:
- x: decrease the x limit from the maximum to the prescribed value. for every column after the fold value, add that value to the position that is equidistant from the fold to the left. for example, at x=7, add the value at x=8 to x=6. x=9 to x=5. all the way until you reach the limit on either the right or the left.
- y: do the same as x except in the vertical direction
7. count the number of values that are greater than 0 between 0, X-lim and y-lim after the first fold. return this value.

## Part 2

Part 2 answer is printed to the console. There was only 1 condition where the fold was not directly in the middle and everything from part 1 applied. I just had to iterate over all of the folds.