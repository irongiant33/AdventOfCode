# Problem Solving Approach

## Part 1

This sounds like classic A*. If I can only remember how to implement it. I want
to say that it needs a priority queue. The order of the queue is determined by
a cost function `f(n) = g(n) + h(n)` where `f(n)` is the cost, `g(n)` is the
total risk of the path, and `h(n)` is the distance to the goal.

## Part 2