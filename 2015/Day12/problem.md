# [Advent of Code](/)

-   [\[About\]](/2015/about)
-   [\[Events\]](/2015/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2015/settings)
-   [\[Log Out\]](/2015/auth/logout)

irongiant33 <span class="star-count">22\*</span>

#  <span class="title-event-wrap">{'year':</span>[2015](/2015)<span class="title-event-wrap">}</span>

-   [\[Calendar\]](/2015)
-   [\[AoC++\]](/2015/support)
-   [\[Sponsors\]](/2015/sponsors)
-   [\[Leaderboard\]](/2015/leaderboard)
-   [\[Stats\]](/2015/stats)

## --- Day 12: JSAbacusFramework.io ---

Santa's Accounting-Elves need help balancing the books after a recent
order. Unfortunately, their accounting software uses a peculiar storage
format. That's where you come in.

They have a [JSON](http://json.org/) document which contains a variety
of things: arrays (`[1,2,3]`), objects (`{"a":1, "b":2}`), numbers, and
strings. Your first job is to simply find all of the *numbers*
throughout the document and add them together.

For example:

-   `[1,2,3]` and `{"a":2,"b":4}` both have a sum of `6`.
-   `[[[3]]]` and `{"a":{"b":4},"c":-1}` both have a sum of `3`.
-   `{"a":[-1,1]}` and `[-1,{"a":1}]` both have a sum of `0`.
-   `[]` and `{}` both have a sum of `0`.

You will not
<span title="Nor are you likely to be eaten by a grue... during *this* puzzle, anyway.">encounter</span>
any strings containing numbers.

What is the *sum of all numbers* in the document?

To begin, <a href="12/input" target="_blank">get your puzzle input</a>.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22JSAbacusFramework%2Eio%22+%2D+Day+12+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F12"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22JSAbacusFramework%2Eio%22+%2D+Day+12+%2D+Advent+of+Code+2015&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F12&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22JSAbacusFramework%2Eio%22+%2D+Day+12+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F12&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
