# Problem Solving Approach

## Part 1

1. Read in the "dirty" input with delimiters `,`, `_` and `\n`. Per line this will result in 5 values: x1, y1, `->`, x2, and y2. Filter out every 3rd value on each line at indexes 2, 7, 12, etc ($2 + 5n$) where $n$ is the line index starting at 0. Convert the remaining puzzle input to long.
2. Assign the puzzle input to a list of vent structures and track maximum x/y pos
3. Create a 2D grid of long values according to the maximum x/y pos from step #2 and initialize an "overlap" variable to track how many vents overlap
4. For every vent that isn't diagonal:
    1. Increment every value on the grid between the starting and stopping point of the vent
    2. Increment the overlap variable for any of those points that are now equal to 2. Do not increment for 3 or greater because we are finding the number of points where _at least 2_ lines overlap.
5. Return the number of overlaps

### Vent Struct

All of the inputs can be safely casted from `long` to `int` because they are less than 1000

- `int x1`: starting x position of vent
- `int y1`: starting y position of vent
- `int dx`: -1 if the vent moves to the left, 1 if it moves to the right, 0 if it doesn't move in X direction
- `int dy`: -1 if the vent moves **UP**, 1 if it moves **DOWN**, 0 if it doesn't move in Y direction
- `int length`: length of the vent. Ex: (0, 9) -> (5, 9) = 6. Ex: (8, 0) -> (0, 8) = 9. Obtain the length for any vent by subtracting 2 dissimilar values (either X or Y), adding 1, and taking the absolute value. 
- `is_diag`: boolean value indicating whether the vent is diagonal

## Part 2

1. Same exact approach as above except remove the condition to exclude diagonals in the loop at step #4.