# [Advent of Code](/)

-   [\[About\]](/2015/about)
-   [\[Events\]](/2015/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2015/settings)
-   [\[Log Out\]](/2015/auth/logout)

irongiant33 <span class="star-count">12\*</span>

#    <span class="title-event-wrap">0xffff&</span>[2015](/2015)<span class="title-event-wrap"></span>

-   [\[Calendar\]](/2015)
-   [\[AoC++\]](/2015/support)
-   [\[Sponsors\]](/2015/sponsors)
-   [\[Leaderboard\]](/2015/leaderboard)
-   [\[Stats\]](/2015/stats)

## --- Day 5: Doesn't He Have Intern-Elves For This? ---

Santa needs help figuring out which strings in his text file are naughty
or nice.

A *nice string* is one with all of the following properties:

-   It contains at least three vowels (`aeiou` only), like `aei`,
    `xazegov`, or `aeiouaeiouaeiou`.
-   It contains at least one letter that appears twice in a row, like
    `xx`, `abcdde` (`dd`), or `aabbccdd` (`aa`, `bb`, `cc`, or `dd`).
-   It does *not* contain the strings `ab`, `cd`, `pq`, or `xy`, even if
    they are part of one of the other requirements.

For example:

-   `ugknbfddgicrmopn` is nice because it has at least three vowels
    (`u...i...o...`), a double letter (`...dd...`), and none of the
    disallowed substrings.
-   `aaa` is nice because it has at least three vowels and a double
    letter, even though the letters used by different rules overlap.
-   `jchzalrnumimnmhp` is naughty because it has no double letter.
-   `haegwjzuvuyypxyu` is naughty because it contains the string `xy`.
-   `dvszwmarrgswjxmb` is naughty because it contains only one vowel.

How many strings are nice?

Your puzzle answer was `255`.

## --- Part Two ---

Realizing the error of his ways, Santa has switched to a better model of
determining whether a string is naughty or nice. None of the old rules
apply, as they are all clearly ridiculous.

Now, a nice string is one with all of the following properties:

-   It contains a pair of any two letters that appears at least twice in
    the string without overlapping, like `xyxy` (`xy`) or `aabcdefgaa`
    (`aa`), but not like `aaa` (`aa`, but it overlaps).
-   It contains at least one letter which repeats with exactly one
    letter between them, like `xyx`, `abcdefeghi` (`efe`), or even
    `aaa`.

For example:

-   `qjhvhtzxzqqjkmpb` is nice because is has a pair that appears twice
    (`qj`) and a letter that repeats with exactly one letter between
    them (`zxz`).
-   `xxyxx` is nice because it has a pair that appears twice and a
    letter that repeats with one between, even though the letters used
    by each rule overlap.
-   `uurcxstgmygtbstg` is naughty because it has a pair (`tg`) but no
    repeat with a single letter between them.
-   `ieodomkazucvgmuy` is naughty because it has a repeating letter with
    one between (`odo`), but no pair that appears twice.

How many strings are nice under these new rules?

Your puzzle answer was `55`.

Both parts of this puzzle are complete! They provide two gold stars:
\*\*

At this point, you should [return to your Advent calendar](/2015) and
try another puzzle.

If you still want to see it, you can
<a href="5/input" target="_blank">get your puzzle input</a>.

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=I%27ve+completed+%22Doesn%27t+He+Have+Intern%2DElves+For+This%3F%22+%2D+Day+5+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F5"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=I%27ve+completed+%22Doesn%27t+He+Have+Intern%2DElves+For+This%3F%22+%2D+Day+5+%2D+Advent+of+Code+2015&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F5&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=I%27ve+completed+%22Doesn%27t+He+Have+Intern%2DElves+For+This%3F%22+%2D+Day+5+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F5&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
