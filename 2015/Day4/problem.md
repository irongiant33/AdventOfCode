# [Advent of Code](/)

-   [\[About\]](/2015/about)
-   [\[Events\]](/2015/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2015/settings)
-   [\[Log Out\]](/2015/auth/logout)

irongiant33 <span class="star-count">6\*</span>

#    <span class="title-event-wrap">sub y{</span>[2015](/2015)<span class="title-event-wrap">}</span>

-   [\[Calendar\]](/2015)
-   [\[AoC++\]](/2015/support)
-   [\[Sponsors\]](/2015/sponsors)
-   [\[Leaderboard\]](/2015/leaderboard)
-   [\[Stats\]](/2015/stats)

## --- Day 4: The Ideal Stocking Stuffer ---

Santa needs help [mining](https://en.wikipedia.org/wiki/Bitcoin#Mining)
some <span title="Hey, mined your own business!">AdventCoins</span>
(very similar to [bitcoins](https://en.wikipedia.org/wiki/Bitcoin)) to
use as gifts for all the economically forward-thinking little girls and
boys.

To do this, he needs to find [MD5](https://en.wikipedia.org/wiki/MD5)
hashes which, in
[hexadecimal](https://en.wikipedia.org/wiki/Hexadecimal), start with at
least *five zeroes*. The input to the MD5 hash is some secret key (your
puzzle input, given below) followed by a number in decimal. To mine
AdventCoins, you must find Santa the lowest positive number (no leading
zeroes: `1`, `2`, `3`, ...) that produces such a hash.

For example:

-   If your secret key is `abcdef`, the answer is `609043`, because the
    MD5 hash of `abcdef609043` starts with five zeroes
    (`000001dbbfa...`), and it is the lowest such number to do so.
-   If your secret key is `pqrstuv`, the lowest number it combines with
    to make an MD5 hash starting with five zeroes is `1048970`; that is,
    the MD5 hash of `pqrstuv1048970` looks like `000006136ef...`.

Your puzzle input is `ckczppom`.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22The+Ideal+Stocking+Stuffer%22+%2D+Day+4+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F4"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22The+Ideal+Stocking+Stuffer%22+%2D+Day+4+%2D+Advent+of+Code+2015&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F4&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22The+Ideal+Stocking+Stuffer%22+%2D+Day+4+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F4&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
