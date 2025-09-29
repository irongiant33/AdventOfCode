# [Advent of Code](/)

-   [\[About\]](/2015/about)
-   [\[Events\]](/2015/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2015/settings)
-   [\[Log Out\]](/2015/auth/logout)

irongiant33 <span class="star-count">16\*</span>

#   <span class="title-event-wrap">0.0.0.0:</span>[2015](/2015)<span class="title-event-wrap"></span>

-   [\[Calendar\]](/2015)
-   [\[AoC++\]](/2015/support)
-   [\[Sponsors\]](/2015/sponsors)
-   [\[Leaderboard\]](/2015/leaderboard)
-   [\[Stats\]](/2015/stats)

## --- Day 9: All in a Single Night ---

Every year, Santa manages to deliver all of his presents in a single
night.

This year, however, he has some
<span title="Bonus points if you recognize all of the locations.">new
locations</span> to visit; his elves have provided him the distances
between every pair of locations. He can start and end at any two
(different) locations he wants, but he must visit each location exactly
once. What is the *shortest distance* he can travel to achieve this?

For example, given the following distances:

    London to Dublin = 464
    London to Belfast = 518
    Dublin to Belfast = 141

The possible routes are therefore:

    Dublin -> London -> Belfast = 982
    London -> Dublin -> Belfast = 605
    London -> Belfast -> Dublin = 659
    Dublin -> Belfast -> London = 659
    Belfast -> Dublin -> London = 605
    Belfast -> London -> Dublin = 982

The shortest of these is `London -> Dublin -> Belfast = 605`, and so the
answer is `605` in this example.

What is the distance of the shortest route?

To begin, <a href="9/input" target="_blank">get your puzzle input</a>.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22All+in+a+Single+Night%22+%2D+Day+9+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F9"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22All+in+a+Single+Night%22+%2D+Day+9+%2D+Advent+of+Code+2015&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F9&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22All+in+a+Single+Night%22+%2D+Day+9+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F9&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
