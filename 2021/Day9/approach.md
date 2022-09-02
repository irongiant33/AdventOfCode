# Problem Solving Approach

## Part 1

1. use no delimiters so that each value is read separately as its own puzzle input, but use a newline as the stop search to find how many inputs are on a line
2. use no delimiters and no stop search to read in the puzzle input. convert to long
3. create 2D long matrix and assign puzzle input values to it.
4. for every item in the matrix, add the (value + 1) to a running sum if that value is less than the value above, to the left, and to the right.
5. return the running sum

TODO: for the actual test, I needed to go back into common.h and increase the default number of puzzle items to 100000 because there is a memory error if there are more puzzle items than the default number of puzzle items.

## Part 2

1. same way to get input as part 1
2. find all of the low points.
3. for each low point, add the low point to an "unsearched" list & initialize an empty basin
4. while there are items in the unsearched list:
    1. for each item in the unsearched list:
        1. add neighbors that don't have a value of 9 to the unsearched list if they are not in the basin or unsearched list
        2. add the item to the basin
5. add the basin size to a linked list. and repeat step 3, 4, 5 for every low point
6. find the maximum 3 basin sizes by sorting the list and taking the last 3 values. multiply these values together
7. return the product.
