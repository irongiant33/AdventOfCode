# [Advent of Code](/)

-   [\[About\]](/2024/about)
-   [\[Events\]](/2024/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2024/settings)
-   [\[Log Out\]](/2024/auth/logout)

irongiant33 <span class="star-count">13\*</span>

#   <span class="title-event-wrap">0.0.0.0:</span>[2024](/2024)<span class="title-event-wrap"></span>

-   [\[Calendar\]](/2024)
-   [\[AoC++\]](/2024/support)
-   [\[Sponsors\]](/2024/sponsors)
-   [\[Leaderboard\]](/2024/leaderboard)
-   [\[Stats\]](/2024/stats)

Our [sponsors](/2024/sponsors) help make Advent of Code possible:

<a
href="/2024/sponsors/redirect?url=https%3A%2F%2Faoc%2Einfi%2Enl%2F%3Fmtm%5Fcampaign%3Daoc2024%26mtm%5Fsource%3Daoc"
target="_blank"
onclick="if(ga)ga(&#39;send&#39;,&#39;event&#39;,&#39;sponsor&#39;,&#39;sidebar&#39;,this.href);"
rel="noopener">Infi</a> - Er is slecht weer op komst en het is een lange
tocht vanaf de Noordpool... Help jij de kerstman veilig door het
luchtruim te navigeren?

## --- Day 9: Disk Fragmenter ---

Another push of the button leaves you in the familiar hallways of some
friendly [amphipods](/2021/day/23)! Good thing you each somehow got your
own personal mini submarine. The Historians jet away in search of the
Chief, mostly by driving directly into walls.

While The Historians quickly figure out how to pilot these things, you
notice an amphipod in the corner struggling with his computer. He's
trying to make more contiguous free space by compacting all of the
files, but his program isn't working; you offer to help.

He shows you the *disk map* (your puzzle input) he's already generated.
For example:

    2333133121414131402

The disk map uses a dense format to represent the layout of *files* and
*free space* on the disk. The digits alternate between indicating the
length of a file and the length of free space.

So, a disk map like `12345` would represent a one-block file, two blocks
of free space, a three-block file, four blocks of free space, and then a
five-block file. A disk map like `90909` would represent three
nine-block files in a row (with no free space between them).

Each file on disk also has an *ID number* based on the order of the
files as they appear *before* they are rearranged, starting with ID `0`.
So, the disk map `12345` has three files: a one-block file with ID `0`,
a three-block file with ID `1`, and a five-block file with ID `2`. Using
one character for each block where digits are the file ID and `.` is
free space, the disk map `12345` represents these individual blocks:

    0..111....22222

The first example above, `2333133121414131402`, represents these
individual blocks:

    00...111...2...333.44.5555.6666.777.888899

The amphipod would like to *move file blocks one at a time* from the end
of the disk to the leftmost free space block (until there are no gaps
remaining between file blocks). For the disk map `12345`, the process
looks like this:

    0..111....22222
    02.111....2222.
    022111....222..
    0221112...22...
    02211122..2....
    022111222......

The first example requires a few more steps:

    00...111...2...333.44.5555.6666.777.888899
    009..111...2...333.44.5555.6666.777.88889.
    0099.111...2...333.44.5555.6666.777.8888..
    00998111...2...333.44.5555.6666.777.888...
    009981118..2...333.44.5555.6666.777.88....
    0099811188.2...333.44.5555.6666.777.8.....
    009981118882...333.44.5555.6666.777.......
    0099811188827..333.44.5555.6666.77........
    00998111888277.333.44.5555.6666.7.........
    009981118882777333.44.5555.6666...........
    009981118882777333644.5555.666............
    00998111888277733364465555.66.............
    0099811188827773336446555566..............

The final step of this file-compacting process is to update the
*filesystem checksum*. To calculate the checksum, add up the result of
multiplying each of these blocks' position with the file ID number it
contains. The leftmost block is in position `0`. If a block contains
free space, skip it instead.

Continuing the first example, the first few blocks' position multiplied
by its file ID number are `0 * 0 = 0`, `1 * 0 = 0`, `2 * 9 = 18`,
`3 * 9 = 27`, `4 * 8 = 32`, and so on. In this example, the checksum is
the sum of these, *`1928`*.

<span title="Bonus points if you make a cool animation of this process.">Compact
the amphipod's hard drive</span> using the process he requested. *What
is the resulting filesystem checksum?* <span class="quiet">(Be careful
copy/pasting the input for this puzzle; it is a single, very long
line.)</span>

Your puzzle answer was `6359213660505`.

The first half of this puzzle is complete! It provides one gold star: \*

## --- Part Two ---

Upon completion, two things immediately become clear. First, the disk
definitely has a lot more contiguous free space, just like the amphipod
hoped. Second, the computer is running much more slowly! Maybe
introducing all of that
<a href="https://en.wikipedia.org/wiki/File_system_fragmentation"
target="_blank">file system fragmentation</a> was a bad idea?

The eager amphipod already has a new plan: rather than move individual
blocks, he'd like to try compacting the files on his disk by moving
*whole files* instead.

This time, attempt to move whole files to the leftmost span of free
space blocks that could fit the file. Attempt to move each file exactly
once in order of *decreasing file ID number* starting with the file with
the highest file ID number. If there is no span of free space to the
left of a file that is large enough to fit the file, the file does not
move.

The first example from above now proceeds differently:

    00...111...2...333.44.5555.6666.777.888899
    0099.111...2...333.44.5555.6666.777.8888..
    0099.1117772...333.44.5555.6666.....8888..
    0099.111777244.333....5555.6666.....8888..
    00992111777.44.333....5555.6666.....8888..

The process of updating the filesystem checksum is the same; now, this
example's checksum would be *`2858`*.

Start over, now compacting the amphipod's hard drive using this new
method instead. *What is the resulting filesystem checksum?*

Answer:

Although it hasn't changed, you can still
<a href="9/input" target="_blank">get your puzzle input</a>.

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=I%27ve+completed+Part+One+of+%22Disk+Fragmenter%22+%2D+Day+9+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F9"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=I%27ve+completed+Part+One+of+%22Disk+Fragmenter%22+%2D+Day+9+%2D+Advent+of+Code+2024&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F9&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=I%27ve+completed+Part+One+of+%22Disk+Fragmenter%22+%2D+Day+9+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F9&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
