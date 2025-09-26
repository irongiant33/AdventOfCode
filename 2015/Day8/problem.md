# [Advent of Code](/)

-   [\[About\]](/2015/about)
-   [\[Events\]](/2015/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2015/settings)
-   [\[Log Out\]](/2015/auth/logout)

irongiant33 <span class="star-count">14\*</span>

#    <span class="title-event-wrap">int y=</span>[2015](/2015)<span class="title-event-wrap">;</span>

-   [\[Calendar\]](/2015)
-   [\[AoC++\]](/2015/support)
-   [\[Sponsors\]](/2015/sponsors)
-   [\[Leaderboard\]](/2015/leaderboard)
-   [\[Stats\]](/2015/stats)

## --- Day 8: Matchsticks ---

Space on the sleigh is limited this year, and so Santa will be bringing
his list as a digital copy. He needs to know how much space it will take
up when stored.

It is common in many programming languages to provide a way to
<span title="It is common for many programmers to try to escape from string escaping.  No such luck here.">escape</span>
special characters in strings. For example,
[C](https://en.wikipedia.org/wiki/Escape_sequences_in_C),
[JavaScript](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String),
[Perl](http://perldoc.perl.org/perlop.html#Quote-and-Quote-like-Operators),
[Python](https://docs.python.org/2.0/ref/strings.html), and even
[PHP](http://php.net/manual/en/language.types.string.php#language.types.string.syntax.double)
handle special characters in very similar ways.

However, it is important to realize the difference between the number of
characters *in the code representation of the string literal* and the
number of characters *in the in-memory string itself*.

For example:

-   `""` is `2` characters of code (the two double quotes), but the
    string contains zero characters.
-   `"abc"` is `5` characters of code, but `3` characters in the string
    data.
-   `"aaa\"aaa"` is `10` characters of code, but the string itself
    contains six "a" characters and a single, escaped quote character,
    for a total of `7` characters in the string data.
-   `"\x27"` is `6` characters of code, but the string itself contains
    just one - an apostrophe (`'`), escaped using hexadecimal notation.

Santa's list is a file that contains many double-quoted string literals,
one on each line. The only escape sequences used are `\\` (which
represents a single backslash), `\"` (which represents a lone
double-quote character), and `\x` plus two hexadecimal characters (which
represents a single character with that ASCII code).

Disregarding the whitespace in the file, what is *the number of
characters of code for string literals* minus *the number of characters
in memory for the values of the strings* in total for the entire file?

For example, given the four strings above, the total number of
characters of string code (`2 + 5 + 10 + 6 = 23`) minus the total number
of characters in memory for string values (`0 + 3 + 7 + 1 = 11`) is
`23 - 11 = 12`.

To begin, <a href="8/input" target="_blank">get your puzzle input</a>.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22Matchsticks%22+%2D+Day+8+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F8"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22Matchsticks%22+%2D+Day+8+%2D+Advent+of+Code+2015&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F8&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22Matchsticks%22+%2D+Day+8+%2D+Advent+of+Code+2015+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2015%2Fday%2F8&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
