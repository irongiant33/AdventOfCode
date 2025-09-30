# [Advent of Code](/)

-   [\[About\]](/2015/about)
-   [\[Events\]](/2015/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2015/settings)
-   [\[Log Out\]](/2015/auth/logout)

irongiant33 <span class="star-count">20\*</span>

#   <span class="title-event-wrap">0.0.0.0:</span>[2015](/2015)<span class="title-event-wrap"></span>

-   [\[Calendar\]](/2015)
-   [\[AoC++\]](/2015/support)
-   [\[Sponsors\]](/2015/sponsors)
-   [\[Leaderboard\]](/2015/leaderboard)
-   [\[Stats\]](/2015/stats)

## --- Day 11: Corporate Policy ---

Santa's previous password expired, and he needs help choosing a new one.

To help him remember his new password after the old one expires, Santa
has devised a method of coming up with a password based on the previous
one. Corporate policy dictates that passwords must be exactly eight
lowercase letters (for security reasons), so he finds his new password
by *incrementing* his old password string repeatedly until it is valid.

Incrementing is just like counting with numbers: `xx`, `xy`, `xz`, `ya`,
`yb`, and so on. Increase the rightmost letter one step; if it was `z`,
it wraps around to `a`, and repeat with the next letter to the left
until one doesn't wrap around.

Unfortunately for Santa, a new Security-Elf recently started, and he has
imposed some additional password requirements:

-   Passwords must include one increasing straight of at least three
    letters, like `abc`, `bcd`, `cde`, and so on, up to `xyz`. They
    cannot skip letters; `abd` doesn't count.
-   Passwords may not contain the letters `i`, `o`, or `l`, as these
    letters can be mistaken for other characters and are therefore
    confusing.
-   Passwords must contain at least two different, non-overlapping pairs
    of letters, like `aa`, `bb`, or `zz`.

For example:

-   `hijklmmn` meets the first requirement (because it contains the
    straight `hij`) but fails the second requirement requirement
    (because it contains `i` and `l`).
-   `abbceffg` meets the third requirement (because it repeats `bb` and
    `ff`) but fails the first requirement.
-   `abbcegjk` fails the third requirement, because it only has one
    double letter (`bb`).
-   The next password after `abcdefgh` is `abcdffaa`.
-   The next password after `ghijklmn` is `ghjaabcc`, because you
    eventually skip all the passwords that start with `ghi...`, since
    `i` is not allowed.

Given Santa's current password (your puzzle input), what should his
*next password* be?

Your puzzle input is `hxbxwxba`.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22Corporate+Policy%22+%2D+Day+11+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F11"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22Corporate+Policy%22+%2D+Day+11+%2D+Advent+of+Code+2015&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F11&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22Corporate+Policy%22+%2D+Day+11+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F11&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
