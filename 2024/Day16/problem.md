# [Advent of Code](/)

-   [\[About\]](/2024/about)
-   [\[Events\]](/2024/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2024/settings)
-   [\[Log Out\]](/2024/auth/logout)

irongiant33 <span class="star-count">19\*</span>

#       <span class="title-event-wrap">/^</span>[2024](/2024)<span class="title-event-wrap">$/</span>

-   [\[Calendar\]](/2024)
-   [\[AoC++\]](/2024/support)
-   [\[Sponsors\]](/2024/sponsors)
-   [\[Leaderboard\]](/2024/leaderboard)
-   [\[Stats\]](/2024/stats)

Our [sponsors](/2024/sponsors) help make Advent of Code possible:

<a
href="/2024/sponsors/redirect?url=https%3A%2F%2Flinks%2Ezerotomastery%2Eio%2Faoc2024"
target="_blank"
onclick="if(ga)ga(&#39;send&#39;,&#39;event&#39;,&#39;sponsor&#39;,&#39;sidebar&#39;,this.href);"
rel="noopener">Zero To Mastery</a> - Ready to upgrade your earning
power? If you like AoC, you'll like our courses built by programmers
(not influencers), for programmers. ZTM helps you get a better job, and
earn more with one trick: quality, not gimmicks.

## --- Day 16: Reindeer Maze ---

It's time again for the [Reindeer Olympics](/2015/day/14)! This year,
the big event is the *Reindeer Maze*, where the Reindeer compete for the
*<span title="I would say it's like Reindeer Golf, but knowing Reindeer, it's almost certainly nothing like Reindeer Golf.">lowest
score</span>*.

You and The Historians arrive to search for the Chief right as the event
is about to start. It wouldn't hurt to watch a little, right?

The Reindeer start on the Start Tile (marked `S`) facing *East* and need
to reach the End Tile (marked `E`). They can move forward one tile at a
time (increasing their score by `1` point), but never into a wall (`#`).
They can also rotate clockwise or counterclockwise 90 degrees at a time
(increasing their score by `1000` points).

To figure out the best place to sit, you start by grabbing a map (your
puzzle input) from a nearby kiosk. For example:

    ###############
    #.......#....E#
    #.#.###.#.###.#
    #.....#.#...#.#
    #.###.#####.#.#
    #.#.#.......#.#
    #.#.#####.###.#
    #...........#.#
    ###.#.#####.#.#
    #...#.....#.#.#
    #.#.#.###.#.#.#
    #.....#...#.#.#
    #.###.#.#.#.#.#
    #S..#.....#...#
    ###############

There are many paths through this maze, but taking any of the best paths
would incur a score of only *`7036`*. This can be achieved by taking a
total of `36` steps forward and turning 90 degrees a total of `7` times:

    ###############
    #.......#....E#
    #.#.###.#.###^#
    #.....#.#...#^#
    #.###.#####.#^#
    #.#.#.......#^#
    #.#.#####.###^#
    #..>>>>>>>>v#^#
    ###^#.#####v#^#
    #>>^#.....#v#^#
    #^#.#.###.#v#^#
    #^....#...#v#^#
    #^###.#.#.#v#^#
    #S..#.....#>>^#
    ###############

Here's a second example:

    #################
    #...#...#...#..E#
    #.#.#.#.#.#.#.#.#
    #.#.#.#...#...#.#
    #.#.#.#.###.#.#.#
    #...#.#.#.....#.#
    #.#.#.#.#.#####.#
    #.#...#.#.#.....#
    #.#.#####.#.###.#
    #.#.#.......#...#
    #.#.###.#####.###
    #.#.#...#.....#.#
    #.#.#.#####.###.#
    #.#.#.........#.#
    #.#.#.#########.#
    #S#.............#
    #################

In this maze, the best paths cost *`11048`* points; following one such
path would look like this:

    #################
    #...#...#...#..E#
    #.#.#.#.#.#.#.#^#
    #.#.#.#...#...#^#
    #.#.#.#.###.#.#^#
    #>>v#.#.#.....#^#
    #^#v#.#.#.#####^#
    #^#v..#.#.#>>>>^#
    #^#v#####.#^###.#
    #^#v#..>>>>^#...#
    #^#v###^#####.###
    #^#v#>>^#.....#.#
    #^#v#^#####.###.#
    #^#v#^........#.#
    #^#v#^#########.#
    #S#>>^..........#
    #################

Note that the path shown above includes one 90 degree turn as the very
first move, rotating the Reindeer from facing East to facing North.

Analyze your map carefully. *What is the lowest score a Reindeer could
possibly get?*

To begin, <a href="16/input" target="_blank">get your puzzle input</a>.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22Reindeer+Maze%22+%2D+Day+16+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F16"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22Reindeer+Maze%22+%2D+Day+16+%2D+Advent+of+Code+2024&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F16&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22Reindeer+Maze%22+%2D+Day+16+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F16&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
