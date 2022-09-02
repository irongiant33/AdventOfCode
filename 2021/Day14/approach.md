# Problem Solving Approach

## Part 1

1. use `\n` and ` ` as a delimiter. Filter by input of length 0, then by index starting at 2 and incrementing by 3.
2. create a hash map using the inputs 1, 3, 5, 7 ...etc. The values are the inputs 2, 4, 6, 8...etc.
3. create an int list of size 26 to contain the letter frequencies
4. initialize a character array with length one longer than the 0th puzzle input and add to the letter frequencies
5. for every step...
    1. allocate a character list double the previous length
    2. for every character except for the last in the previous character list...
        1. look up the pairs in the list using the hash function (current and next character)
        2. add the current character and the looked up character to the list
        3. add to the letter frequencies
    3. free the previous list and point the previous list to the new list
6. find the min and max values in the list, subtract them, and return

### hash function

26 * first value + second value

values are 0-25, 0=A, 25=Z. 

## Part 2

---
### Incomplete approach

Increasing the step size to 40, I feel like there is an issue with the sizes. Don't know if I can responsibly allocate memory for the whole string.

Instead, I will keep track of the transitions (similar to the lanternfish problem)

Keep a 676x1 matrix of values corresponding to the frequency of AA, AB, AC...ZZ compounds. Then there is a 676x676 matrix of transitions where each row is state N+1 and each column is state N. If there is a 1 in column 0, row 2, that means that state AA transitions to state AC. For each column, there will be two rows active because AA will generate an intermediate letter, say C. So AA will transition to AC and CA.

The result of multiplying the transition matrix by the frequency vector yields the frequency vector for state N+1. To learn the frequencies at state 40, either do this same operation 40 times or find the 40th order transition matrix and multiply by the initial frequncy state.

Then, given the frequencies, you know everything except for the first and last letter are represented twice. We can then build the individual letter frequencies by subtracting...?

---
### Implemented approach

Keep an array of 676 compound structs. Within each struct, we have the frequency of the compound, as well as the element that it generates. We also have the frequency of the compound at the next state.

There is also an array of 26 integers corresponding to individual element frequencies.

Upon reading the input, we populate the initial states of both of these arrays. Then with each step, iterate through each compound. Set the current frequency to the next frequency. Set the next frequency to 0. Add the current frequency to the letter frequency that it generates. Then add the current frequency to both the compound's next state frequency that it generates.

Find the minimum and maximum individual letter frequencies and subtract them (this will be a long matrix).

