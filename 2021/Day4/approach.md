# Problem Solving Approach

## Part 1

1. This puzzle input will require more input parsing than previous puzzle inputs. Here will be the input parsing approach:
    1. Use the end character `\n` with the `,` delimiter to read in the "called out" numbers.
    2. Use a NULL end character with `_` and `\n` delimiters to read in the puzzle input.
    3. Remove the first item in the returned list because these will be the callouts
    4. Due to the fact that the puzzle input used spaces to keep all of the numbers justified in their columns, I will have to parse the list of inputs and remove any puzzle items with a length of 0.
    5. convert the remaining items from string to long and store in the `long value` of each puzzle_item.

2. Initialize an array of Bingo Board Structs with size equal to the bingo board input divided by $M^2$ where M is the dimension of the board.
3. For every $M^2$ values, convert each puzzle item into a bingo item struct and assign to the appropriate bingo board. Also insert every bingo item into a hash table.
4. For every number in the "called out" list:
    1. Find the hash key for that value and for every value in that key's bucket, turn the `is_on` property to 1.
    2. If you are at the 5th called out number or higher:
        1. For every bingo board in the list, sum the rows and columns.
        2. If any row or column sums to 5, add this board's index to the winner list.
    3. If the number of winners is 0, keep going. If it is greater than 1, signal an error. If it is equal to 1, save the last called out number and exit.
5. Sum all values on the winning board with the `is_on` property equal to 0
6. Multiply this sum by the last called out number and return

### Bingo Item Struct

- `int value`: int representation of the number on the board (assuming all numbers are less than 100 we can cast from long)
- `int is_on`: 0 if the number has not been selected, 1 if the number has been selected

### Bingo Board Struct

- `bingo_item_t ** bingo_items`: 2D array of bingo items.
- `is_winner`: boolean variable to indicate if the board is a winner

## Part 2

1. Keep steps 1-3 the same as part 1, as well as the same structures
2. keep all of step 4 the same except for the break condition which is as follows:
    1. exit the loop if the number of winners is equal to the number of boards and save the last called number
3. Sum all the values on the last winning board who's `is_on` property is equal to 0
4. multiply this sum by the last called number