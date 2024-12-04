# [Advent of Code](/)

-   [\[About\]](/2024/about)
-   [\[Events\]](/2024/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2024/settings)
-   [\[Log Out\]](/2024/auth/logout)

irongiant33 <span class="star-count">2\*</span>

#  <span class="title-event-wrap">{'year':</span>[2024](/2024)<span class="title-event-wrap">}</span>

-   [\[Calendar\]](/2024)
-   [\[AoC++\]](/2024/support)
-   [\[Sponsors\]](/2024/sponsors)
-   [\[Leaderboard\]](/2024/leaderboard)
-   [\[Stats\]](/2024/stats)

Our [sponsors](/2024/sponsors) help make Advent of Code possible:

<a href="/2024/sponsors/redirect?url=https%3A%2F%2Fwww%2Ebjss%2Ecom%2F"
target="_blank"
onclick="if(ga)ga(&#39;send&#39;,&#39;event&#39;,&#39;sponsor&#39;,&#39;sidebar&#39;,this.href);"
rel="noopener">BJSS</a> - Delivered by teams of passionate experts, we
provide brilliant software engineering that delivers transformative
outcomes for our clients.

## --- Day 3: Mull It Over ---

"Our computers are having issues, so I have no idea if we have any Chief
Historians
<span title="There's a spot reserved for Chief Historians between the green toboggans and the red toboggans. They've never actually had any Chief Historians in stock, but it's best to be prepared.">in
stock</span>! You're welcome to check the warehouse, though," says the
mildly flustered shopkeeper at the [North Pole Toboggan Rental
Shop](/2020/day/2). The Historians head out to take a look.

The shopkeeper turns to you. "Any chance you can see why our computers
are having issues again?"

The computer appears to be trying to run a program, but its memory (your
puzzle input) is *corrupted*. All of the instructions have been jumbled
up!

It seems like the goal of the program is just to *multiply some
numbers*. It does that with instructions like `mul(X,Y)`, where `X` and
`Y` are each 1-3 digit numbers. For instance, `mul(44,46)` multiplies
`44` by `46` to get a result of `2024`. Similarly, `mul(123,4)` would
multiply `123` by `4`.

However, because the program's memory has been corrupted, there are also
many invalid characters that should be *ignored*, even if they look like
part of a `mul` instruction. Sequences like `mul(4*`, `mul(6,9!`,
`?(12,34)`, or `mul ( 2 , 4 )` do *nothing*.

For example, consider the following section of corrupted memory:

    xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))

Only the four highlighted sections are real `mul` instructions. Adding
up the result of each instruction produces *`161`*
(`2*4 + 5*5 + 11*8 + 8*5`).

Scan the corrupted memory for uncorrupted `mul` instructions. *What do
you get if you add up all of the results of the multiplications?*

To begin, <a href="3/input" target="_blank">get your puzzle input</a>.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22Mull+It+Over%22+%2D+Day+3+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F3"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22Mull+It+Over%22+%2D+Day+3+%2D+Advent+of+Code+2024&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F3&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22Mull+It+Over%22+%2D+Day+3+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F3&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
