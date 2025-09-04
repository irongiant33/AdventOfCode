# [Advent of Code](/)

-   [\[About\]](/2015/about)
-   [\[Events\]](/2015/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2015/settings)
-   [\[Log Out\]](/2015/auth/logout)

irongiant33 <span class="star-count">2\*</span>

#    <span class="title-event-wrap">0xffff&</span>[2015](/2015)<span class="title-event-wrap"></span>

-   [\[Calendar\]](/2015)
-   [\[AoC++\]](/2015/support)
-   [\[Sponsors\]](/2015/sponsors)
-   [\[Leaderboard\]](/2015/leaderboard)
-   [\[Stats\]](/2015/stats)

## --- Day 1: Not Quite Lisp ---

Santa was hoping for a white Christmas, but his weather machine's "snow"
function is powered by stars, and he's fresh out! To save Christmas, he
needs you to collect *fifty stars* by December 25th.

Collect stars by helping Santa solve puzzles. Two puzzles will be made
available on each day in the Advent calendar; the second puzzle is
unlocked when you complete the first. Each puzzle grants *one star*.
<span title="Also, some puzzles contain Easter eggs like this one. Yes, I know it's not traditional to do Advent calendars for Easter.">Good
luck!</span>

Here's an easy puzzle to warm you up.

Santa is trying to deliver presents in a large apartment building, but
he can't find the right floor - the directions he got are a little
confusing. He starts on the ground floor (floor `0`) and then follows
the instructions one character at a time.

An opening parenthesis, `(`, means he should go up one floor, and a
closing parenthesis, `)`, means he should go down one floor.

The apartment building is very tall, and the basement is very deep; he
will never find the top or bottom floors.

For example:

-   `(())` and `()()` both result in floor `0`.
-   `(((` and `(()(()(` both result in floor `3`.
-   `))(((((` also results in floor `3`.
-   `())` and `))(` both result in floor `-1` (the first basement
    level).
-   `)))` and `)())())` both result in floor `-3`.

To *what floor* do the instructions take Santa?

Your puzzle answer was `138`.

## --- Part Two ---

Now, given the same instructions, find the *position* of the first
character that causes him to enter the basement (floor `-1`). The first
character in the instructions has position `1`, the second character has
position `2`, and so on.

For example:

-   `)` causes him to enter the basement at character position `1`.
-   `()())` causes him to enter the basement at character position `5`.

What is the *position* of the character that causes Santa to first enter
the basement?

Your puzzle answer was `1771`.

Both parts of this puzzle are complete! They provide two gold stars:
\*\*

At this point, you should [return to your Advent calendar](/2015) and
try another puzzle.

If you still want to see it, you can
<a href="1/input" target="_blank">get your puzzle input</a>.

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=I%27ve+completed+%22Not+Quite+Lisp%22+%2D+Day+1+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F1"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=I%27ve+completed+%22Not+Quite+Lisp%22+%2D+Day+1+%2D+Advent+of+Code+2015&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F1&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=I%27ve+completed+%22Not+Quite+Lisp%22+%2D+Day+1+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F1&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
