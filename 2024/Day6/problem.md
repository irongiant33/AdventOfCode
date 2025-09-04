# [Advent of Code](/)

-   [\[About\]](/2024/about)
-   [\[Events\]](/2024/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2024/settings)
-   [\[Log Out\]](/2024/auth/logout)

irongiant33 <span class="star-count">8\*</span>

#   <span class="title-event-wrap">{:year </span>[2024](/2024)<span class="title-event-wrap">}</span>

-   [\[Calendar\]](/2024)
-   [\[AoC++\]](/2024/support)
-   [\[Sponsors\]](/2024/sponsors)
-   [\[Leaderboard\]](/2024/leaderboard)
-   [\[Stats\]](/2024/stats)

Our [sponsors](/2024/sponsors) help make Advent of Code possible:

<a href="/2024/sponsors/redirect?url=https%3A%2F%2Fahrefs%2Ecom%2Fabout"
target="_blank"
onclick="if(ga)ga(&#39;send&#39;,&#39;event&#39;,&#39;sponsor&#39;,&#39;sidebar&#39;,this.href);"
rel="noopener">Ahrefs</a> - We crawl the internet, all of it. Then we
parse, store, index and query, all of it. And that's how we build web
analytics and a search engine. What else could we do with 400 billion
htmls? :thinking\_face: BTW we use OCaml

## --- Day 6: Guard Gallivant ---

The Historians use their fancy [device](4) again, this time to whisk you
all away to the North Pole prototype suit manufacturing lab... in the
year [1518](/2018/day/5)! It turns out that having direct access to
history is very convenient for a group of historians.

You still have to be careful of time paradoxes, and so it will be
important to avoid anyone from 1518 while The Historians search for the
Chief. Unfortunately, a single *guard* is patrolling this part of the
lab.

Maybe you can work out where the guard will go ahead of time so that The
Historians can search safely?

You start by making a map (your puzzle input) of the situation. For
example:

    ....#.....
    .........#
    ..........
    ..#.......
    .......#..
    ..........
    .#..^.....
    ........#.
    #.........
    ......#...

The map shows the current position of the guard with `^` (to indicate
the guard is currently facing *up* from the perspective of the map). Any
*obstructions* - crates, desks, alchemical reactors, etc. - are shown as
`#`.

Lab guards in 1518 follow a very strict patrol protocol which involves
repeatedly following these steps:

-   If there is something directly in front of you, turn right 90
    degrees.
-   Otherwise, take a step forward.

Following the above protocol, the guard moves up several times until she
reaches an obstacle (in this case, a pile of failed suit prototypes):

    ....#.....
    ....^....#
    ..........
    ..#.......
    .......#..
    ..........
    .#........
    ........#.
    #.........
    ......#...

Because there is now an obstacle in front of the guard, she turns right
before continuing straight in her new facing direction:

    ....#.....
    ........>#
    ..........
    ..#.......
    .......#..
    ..........
    .#........
    ........#.
    #.........
    ......#...

Reaching another obstacle (a spool of several *very* long polymers), she
turns right again and continues downward:

    ....#.....
    .........#
    ..........
    ..#.......
    .......#..
    ..........
    .#......v.
    ........#.
    #.........
    ......#...

This process continues for a while, but the guard eventually leaves the
mapped area (after walking past a tank of universal solvent):

    ....#.....
    .........#
    ..........
    ..#.......
    .......#..
    ..........
    .#........
    ........#.
    #.........
    ......#v..

By predicting the guard's route, you can determine which specific
positions in the lab will be in the patrol path. *Including the guard's
starting position*, the positions visited by the guard before leaving
the area are marked with an `X`:

    ....#.....
    ....XXXXX#
    ....X...X.
    ..#.X...X.
    ..XXXXX#X.
    ..X.X.X.X.
    .#XXXXXXX.
    .XXXXXXX#.
    #XXXXXXX..
    ......#X..

In this example, the guard will visit *`41`* distinct positions on your
map.

Predict the path of the guard. *How many distinct positions will the
guard visit before leaving the mapped area?*

To begin, <a href="6/input" target="_blank">get your puzzle input</a>.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22Guard+Gallivant%22+%2D+Day+6+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F6"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22Guard+Gallivant%22+%2D+Day+6+%2D+Advent+of+Code+2024&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F6&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22Guard+Gallivant%22+%2D+Day+6+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F6&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
