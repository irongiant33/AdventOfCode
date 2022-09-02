# Problem Solving Approach

## Part 1

1. Delimit the puzzle input with `,` and convert to long
2. Insert all items of puzzle input into a data structure like a tree and sort it
3. Find the median. If there are an even number of values, consider the crab positions to the left and right of the median. If there is an odd number of values, only consider the median.
    - you could also consider splitting the set into a lower and upper half. Find the median of each half. Whichever median is closer to the original median, use that crab value. (jump to 5)
4. Calculate the distance of every puzzle value to the considered values. Pick the smaller considered value
5. Return the distance

Unfortunately, my approach was not correct. My efforts of sorting the list were somewhat in vain. To get the correct value, I increased the SEARCH_WINDOW until the fuel cost stopped decreasing. I settled on a value ~100 so the program still ran fast enough and generated the right output.

## Part 2

Steps now have varying costs. It is still going to be imperative to search around the median so we'll keep everything and just try to adjust the cost calculating function. I also misinterpreted the instructions by assuming one crab had to stay in place, but in fact they can move to any position. So I'll adjust this as well.

$cost = (1 + step) * (step / 2)$

In order to implement this cost function, I will have to convert in and out of floating point. Everything else will be the same from part 1.

Similar to part 1, I had to widen my search window in order to find the answer. Found the correct answer with a search window of 1000.