# Problem Solving Approach

## Part 1

1. Read input with delimiter `,` and no end character. convert the input to long. This will yield a puzzle input where each item is the age of a fish
2. The number of fish that are born as a result of the starting fish is independent of the other starting fish. Therefore, given the number of days $N$ you need to simulate, you can find the number of fish that a starting age between 1 and 5 inclusive (the oldest age of any starting fish in the puzzle input) would create. Then, the process of finding the total number of fish after $N$ days would be to look up the age of each fish and add its corresponding birth rate to the running total.
3. Initialize fish count to 1.
4. To find the number of fish that are born from a starting fish with age $k$:
    1. The birth days are: $$\vec{b} = k + 1 + 7 \vec{n} \quad s.t. \quad \vec{n} = [0, 1, 2, 3 ...] \quad s.t . \quad k + 1 + 7n \le N$$
    2. add the number of birthdays to the total number of fish. Repeat step 4 for each birthday until there are no more birthdays
5. Repeat step 3 and 4 for $k \in [1, 2, 3, 4, 5]$ so that you get a fish count for each of these starting values
6. Loop through the input and map the fish age to a starting value and add to the running sum.


## Part 2

I could not think of a way to speed up part 1, so I resorted to running part 1 with the input of 256 and `DEBUG_PRINT` set to true. I ran the executable without valgrind to print the values and then I entered the values manually into an array for part 2. Not the optimal solution, but it is a solution. Not the fastest solution, but I didn't wait for hours.

After looking up some alternative approaches I found quite a genius solution. I would love to be able to think in linear algebra forms.

$$
\begin{bmatrix}
f_0^{(k)} \\
f_1^{(k)} \\
\vdots \\
f_n^{(k)}
\end{bmatrix}

\begin{bmatrix}
t_{0,0} && t_{1,0} && \dots && t_{n,0} \\
t_{0,1} && \ddots && && \vdots \\
\vdots && && \ddots && \vdots \\
t_{0,n} && \dots && \dots && t_{n,n}
\end{bmatrix}
=
\begin{bmatrix}
f_0^{(k + 1)} \\
f_1^{(k + 1)} \\
\vdots \\
f_n^{(k + 1)}
\end{bmatrix}
$$

The matrix above shows a transition from day $k$ to day $k+1$. If you want to make a transition from the initial state to day $N$, you need to just raise the transition matrix to the power of $N$ and set the initial frequency matrix to the frequency of each fish input. For example, if your input is `1, 2, 3, 3, 4` the matrix will look like this:

$$
\begin{bmatrix}
0 \\
1 \\
1 \\
2 \\
1 \\
0 \\
0 \\
0 \\
0
\end{bmatrix}
$$

Then the final matrix will just be the frequency of every fish at the final day. To get the answer, just sum the matrix. Any element in the transition matrix will be `1` if a fish at state $a$ will produce a fish at state $b$ for the element $t_{a, b}$. The transition matrix will look like this:

$$
\begin{bmatrix}
0 && 1 && 0 && 0 && 0 && 0 && 0 && 0 && 0 \\
0 && 0 && 1 && 0 && 0 && 0 && 0 && 0 && 0 \\
0 && 0 && 0 && 1 && 0 && 0 && 0 && 0 && 0 \\
0 && 0 && 0 && 0 && 1 && 0 && 0 && 0 && 0 \\
0 && 0 && 0 && 0 && 0 && 1 && 0 && 0 && 0 \\
0 && 0 && 0 && 0 && 0 && 0 && 1 && 0 && 0 \\
1 && 0 && 0 && 0 && 0 && 0 && 0 && 1 && 0 \\
0 && 0 && 0 && 0 && 0 && 0 && 0 && 0 && 1 \\
1 && 0 && 0 && 0 && 0 && 0 && 0 && 0 && 0
\end{bmatrix}
$$