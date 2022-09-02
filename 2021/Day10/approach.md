# Problem Solving Approach

## Part 1

1. Read in the puzzle input with no delimiters and no ending characters.
2. Keep track of puzzle input index. Iterate the index and add every item to a doubly linked list, in order, until you reach a `\n` character. Once you do this, proceed with the next steps.
3. Read forward in the linked list until you reach any one of the "ending" characters `}`, `]`, `)`, or `>`. Once you do this, compare this character to the character immediately before it. If the character immediately before matches it pair (`{}`, `[]`, `()`, or `<>`), remove both the previous item and the current item from the linked list.
4. Continue iterating through the linked list until you've reached the end. If you've reached the end without error, this is an incomplete line. If the characters don't match their pairs, perform a lookup of the error-inducing ending character. Add the value corresponding to the character to the running sum: `)` = 3, `]` = 57, `}` = 1197, `>` = 25137.
5. Repeat steps 2-5 until you have reached the end of the puzzle input.
6. Return the running sum.

## Part 2

Now we have to autocomplete the incomplete strings. This will be easy, we will apply the same process as above. 
As long as an error value isn't returned, we will calculate the string value in reverse order of the remaining values in the linked list by doing the following:

1. Initialize a linked list that will contain the results of the string scores.
2. Going through the linked list in reverse order, start with a score of 0. For each character, multiply the score by 5 and add the character value: `)` = 1, `]` = 2, `}` = 3, `>` = 4.
3. Add the score to the linked list and repeat step 2 for all lines
4. sort the linked list and return the middle score.