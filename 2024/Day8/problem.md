# [Advent of Code](/)

-   [\[About\]](/2024/about)
-   [\[Events\]](/2024/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2024/settings)
-   [\[Log Out\]](/2024/auth/logout)

irongiant33 <span class="star-count">12\*</span>

#        <span class="title-event-wrap">λy.</span>[2024](/2024)<span class="title-event-wrap"></span>

-   [\[Calendar\]](/2024)
-   [\[AoC++\]](/2024/support)
-   [\[Sponsors\]](/2024/sponsors)
-   [\[Leaderboard\]](/2024/leaderboard)
-   [\[Stats\]](/2024/stats)

Our [sponsors](/2024/sponsors) help make Advent of Code possible:

<a
href="/2024/sponsors/redirect?url=https%3A%2F%2Fwww%2Elightricks%2Ecom%2Fltxv"
target="_blank"
onclick="if(ga)ga(&#39;send&#39;,&#39;event&#39;,&#39;sponsor&#39;,&#39;sidebar&#39;,this.href);"
rel="noopener">Lightricks</a> - Are you nerdy but also creative? Do you
love AI, but truly believe the human hand doesn’t have six fingers? If
you answered yes and want to help the future of creation, we’re hiring
software engineers, developers, and more.

## --- Day 8: Resonant Collinearity ---

You find yourselves on the [roof](/2016/day/25) of a top-secret Easter
Bunny installation.

While The Historians do their thing, you take a look at the familiar
*huge antenna*. Much to your surprise, it seems to have been
reconfigured to emit a signal that makes people 0.1% more likely to buy
Easter Bunny brand
<span title="They could have imitated delicious chocolate, but the mediocre chocolate is WAY easier to imitate.">Imitation
Mediocre</span> Chocolate as a Christmas gift! Unthinkable!

Scanning across the city, you find that there are actually many such
antennas. Each antenna is tuned to a specific *frequency* indicated by a
single lowercase letter, uppercase letter, or digit. You create a map
(your puzzle input) of these antennas. For example:

    ............
    ........0...
    .....0......
    .......0....
    ....0.......
    ......A.....
    ............
    ............
    ........A...
    .........A..
    ............
    ............

The signal only applies its nefarious effect at specific *antinodes*
based on the resonant frequencies of the antennas. In particular, an
antinode occurs at any point that is perfectly in line with two antennas
of the same frequency - but only when one of the antennas is twice as
far away as the other. This means that for any pair of antennas with the
same frequency, there are two antinodes, one on either side of them.

So, for these two antennas with frequency `a`, they create the two
antinodes marked with `#`:

    ..........
    ...#......
    ..........
    ....a.....
    ..........
    .....a....
    ..........
    ......#...
    ..........
    ..........

Adding a third antenna with the same frequency creates several more
antinodes. It would ideally add four antinodes, but two are off the
right side of the map, so instead it adds only two:

    ..........
    ...#......
    #.........
    ....a.....
    ........a.
    .....a....
    ..#.......
    ......#...
    ..........
    ..........

Antennas with different frequencies don't create antinodes; `A` and `a`
count as different frequencies. However, antinodes *can* occur at
locations that contain antennas. In this diagram, the lone antenna with
frequency capital `A` creates no antinodes but has a
lowercase-`a`-frequency antinode at its location:

    ..........
    ...#......
    #.........
    ....a.....
    ........a.
    .....a....
    ..#.......
    ......A...
    ..........
    ..........

The first example has antennas with two different frequencies, so the
antinodes they create look like this, plus an antinode overlapping the
topmost `A`-frequency antenna:

    ......#....#
    ...#....0...
    ....#0....#.
    ..#....0....
    ....0....#..
    .#....A.....
    ...#........
    #......#....
    ........A...
    .........A..
    ..........#.
    ..........#.

Because the topmost `A`-frequency antenna overlaps with a `0`-frequency
antinode, there are *`14`* total unique locations that contain an
antinode within the bounds of the map.

Calculate the impact of the signal. *How many unique locations within
the bounds of the map contain an antinode?*

Your puzzle answer was `379`.

The first half of this puzzle is complete! It provides one gold star: \*

## --- Part Two ---

Watching over your shoulder as you work, one of The Historians asks if
you took the effects of resonant harmonics into your calculations.

Whoops!

After updating your model, it turns out that an antinode occurs at *any
grid position* exactly in line with at least two antennas of the same
frequency, regardless of distance. This means that some of the new
antinodes will occur at the position of each antenna (unless that
antenna is the only one of its frequency).

So, these three `T`-frequency antennas now create many antinodes:

    T....#....
    ...T......
    .T....#...
    .........#
    ..#.......
    ..........
    ...#......
    ..........
    ....#.....
    ..........

In fact, the three `T`-frequency antennas are all exactly in line with
two antennas, so they are all also antinodes! This brings the total
number of antinodes in the above example to *`9`*.

The original example now has *`34`* antinodes, including the antinodes
that appear on every antenna:

    ##....#....#
    .#.#....0...
    ..#.#0....#.
    ..##...0....
    ....0....#..
    .#...#A....#
    ...#..#.....
    #....#.#....
    ..#.....A...
    ....#....A..
    .#........#.
    ...#......##

Calculate the impact of the signal using this updated model. *How many
unique locations within the bounds of the map contain an antinode?*

Answer:

Although it hasn't changed, you can still
<a href="8/input" target="_blank">get your puzzle input</a>.

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=I%27ve+completed+Part+One+of+%22Resonant+Collinearity%22+%2D+Day+8+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F8"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=I%27ve+completed+Part+One+of+%22Resonant+Collinearity%22+%2D+Day+8+%2D+Advent+of+Code+2024&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F8&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=I%27ve+completed+Part+One+of+%22Resonant+Collinearity%22+%2D+Day+8+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F8&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
