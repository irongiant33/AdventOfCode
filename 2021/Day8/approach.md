# Problem Solving Approach

## Part 1

1. Delimit the input with `_` and `\n`. Filter by index to omit all index 11 at increments of 15
2. For now, count all of the puzzle input at multiples of indexes 10, 11, 12, 13 if the length is equal to 2, 3, 4, or 7 (corresponding to displays 1, 7, 4, and 8)
3. Return the count.

## Part 2

Let's break down the decoded display into regions:

```
 0000
1    2
1    2
 3333
4    5
4    5
 6666
```

Each index corresponds to a unique region on the decoded 7 segment display. Therefore, we can think of our problem as trying to solve for the character `a` though `g` associated with each region.

Now, let's group each displayed number into "length groups":

|Lengths: | 2 | 3 | 4 | 5 | 6 | 7 |
|---------|---|---|---|---|---|---|
|         | 1 | 7 | 4 | 2 | 0 | 8 |
|         |   |   |   | 3 | 6 |   |
|         |   |   |   | 5 | 9 |   |

And each displayed number into "display regions"

|Region #: | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|----------|---|---|---|---|---|---|---|
|          | 0 | 0 | 0 |   | 0 | 0 | 0 |
|          |   |   | 1 |   |   | 1 |   |
|          | 2 |   | 2 | 2 | 2 |   | 2 |
|          | 3 |   | 3 | 3 |   | 3 | 3 |
|          |   | 4 | 4 | 4 |   | 4 |   |
|          | 5 | 5 |   | 5 |   | 5 | 5 |
|          | 6 | 6 |   | 6 | 6 | 6 | 6 |
|          | 7 |   | 7 |   |   | 7 |   |
|          | 8 | 8 | 8 | 8 | 8 | 8 | 8 |
|          | 9 | 9 | 9 | 9 |   | 9 | 9 |

We can make an overlay of the hint lengths that correspond to each region:

|Region #: | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|----------|---|---|---|---|---|---|---|
|          | 3 | 4 | 2 | 4 | 5 | 2 | 5 |
|          | 5 | 5 | 3 | 5 | 6 | 3 | 6 |
|          | 6 | 6 | 4 | 6 |   | 4 |   |
|          |   |   | 5 |   |   | 5 |   |
|          |   |   | 6 |   |   | 6 |   |

|Region #: | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| Length   |   |   |   |   |   |   |   |
|----------|---|---|---|---|---|---|---|
|     2    |   |   | 1 |   |   | 1 |   |
|     3    | 7 |   | 7 |   |   | 7 |   |
|     4    |   | 4 | 4 | 4 |   | 4 |   |
|     5    | 5 |   | 5 |   |   | 5 |   |
|     6    |   |   | 6 |   |   | 6 |   |

Since 8 occupies every region, its appearance in the "hint" list offers us no information, so I have omitted it from the above list. But this table makes it easy to see that regions 2 and 5 should be the easiest to infer due to the large number of lengths that correspond to that position.

Given a test input:

```
acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab |
cdfeb fcadb cdfeb cdbaf
```

We can rearrange the "hints" into bitfields that correspond to whether `a` is present or not.
The bitfield looks like the following for `ab`

```
abcdefg
1100000
```

And like the following for `abe`:

```
abcdefg
1100100
```

By XOR'ing these values together, we obtain `0000100`, identifying `e` as being the wire tied to segment 0. Similarly, we can derive logic to determine every other position:

```
i_2 ^ i_3 = p_0
```

```
i_4 & i_{5, 0} & i_{5, 1} & i_{5, 2} = p_3
```

```
(i_4 ^ p_3) ^ i_2 = p_1
```

```
(i_{5, 0} & i_{5, 1} & i_{5, 2}) ^ p_0 ^ p_3 = p_6
```

```
(!i_4) ^ (p_0 | p_6) = p_4
```

```
(i_{6, 0} ^ i_{6, 1}) | (i_{6, 0} ^ i_{6, 2}) | (i_{6, 1} ^ i_{6, 2}) ^ (p_3 | p_4) = p_2
```

```
i_2 ^ p_2 = p_5
```