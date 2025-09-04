# [Advent of Code](/)

-   [\[About\]](/2024/about)
-   [\[Events\]](/2024/events)
-   <a href="https://cottonbureau.com/people/advent-of-code"
    target="_blank">[Shop]</a>
-   [\[Settings\]](/2024/settings)
-   [\[Log Out\]](/2024/auth/logout)

irongiant33 <span class="star-count">14\*</span>

#   <span class="title-event-wrap">0.0.0.0:</span>[2024](/2024)<span class="title-event-wrap"></span>

-   [\[Calendar\]](/2024)
-   [\[AoC++\]](/2024/support)
-   [\[Sponsors\]](/2024/sponsors)
-   [\[Leaderboard\]](/2024/leaderboard)
-   [\[Stats\]](/2024/stats)

Our [sponsors](/2024/sponsors) help make Advent of Code possible:

<a
href="/2024/sponsors/redirect?url=https%3A%2F%2Fwww%2Eshopify%2Ecom%2Fcareers"
target="_blank"
onclick="if(ga)ga(&#39;send&#39;,&#39;event&#39;,&#39;sponsor&#39;,&#39;sidebar&#39;,this.href);"
rel="noopener">Shopify</a> - We are a company of world-class crafters.
Our developers experiment and iterate at high speeds with high rates of
improvement.

## --- Day 13: Claw Contraption ---

Next up: the [lobby](/2020/day/24) of a resort on a tropical island. The
Historians take a moment to admire the hexagonal floor tiles before
spreading out.

Fortunately, it looks like the resort has a new
[arcade](https://en.wikipedia.org/wiki/Amusement_arcade)! Maybe you can
win some prizes from the
<a href="https://en.wikipedia.org/wiki/Claw_machine"
target="_blank">claw machines</a>?

The claw machines here are a little unusual. Instead of a joystick or
directional buttons to control the claw, these machines have two buttons
labeled `A` and `B`. Worse, you can't just put in a token and play; it
costs *3 tokens* to push the `A` button and *1 token* to push the `B`
button.

With a little experimentation, you figure out that each machine's
buttons are configured to move the claw a specific amount to the *right*
(along the `X` axis) and a specific amount *forward* (along the `Y`
axis) each time that button is pressed.

Each machine contains one *prize*; to win the prize, the claw must be
positioned *exactly* above the prize on both the `X` and `Y` axes.

You wonder: what is the smallest number of tokens you would have to
spend to win as many prizes as possible? You assemble a list of every
machine's button behavior and prize location (your puzzle input). For
example:

    Button A: X+94, Y+34
    Button B: X+22, Y+67
    Prize: X=8400, Y=5400

    Button A: X+26, Y+66
    Button B: X+67, Y+21
    Prize: X=12748, Y=12176

    Button A: X+17, Y+86
    Button B: X+84, Y+37
    Prize: X=7870, Y=6450

    Button A: X+69, Y+23
    Button B: X+27, Y+71
    Prize: X=18641, Y=10279

This list describes the button configuration and prize location of four
different claw machines.

For now, consider just the first claw machine in the list:

-   Pushing the machine's `A` button would move the claw `94` units
    along the `X` axis and `34` units along the `Y` axis.
-   Pushing the `B` button would move the claw `22` units along the `X`
    axis and `67` units along the `Y` axis.
-   The prize is located at `X=8400`, `Y=5400`; this means that from the
    claw's initial position, it would need to move exactly `8400` units
    along the `X` axis and exactly `5400` units along the `Y` axis to be
    perfectly aligned with the prize in this machine.

The cheapest way to win the prize is by pushing the `A` button `80`
times and the `B` button `40` times. This would line up the claw along
the `X` axis (because `80*94 + 40*22 = 8400`) and along the `Y` axis
(because `80*34 + 40*67 = 5400`). Doing this would cost `80*3` tokens
for the <span title="Half A presses are not allowed.">`A` presses</span>
and `40*1` for the `B` presses, a total of *`280`* tokens.

For the second and fourth claw machines, there is no combination of A
and B presses that will ever win a prize.

For the third claw machine, the cheapest way to win the prize is by
pushing the `A` button `38` times and the `B` button `86` times. Doing
this would cost a total of *`200`* tokens.

So, the most prizes you could possibly win is two; the minimum tokens
you would have to spend to win all (two) prizes is *`480`*.

You estimate that each button would need to be pressed *no more than
`100` times* to win a prize. How else would someone be expected to play?

Figure out how to win as many prizes as possible. *What is the fewest
tokens you would have to spend to win all possible prizes?*

To begin, <a href="13/input" target="_blank">get your puzzle input</a>.

Answer:

You can also <span class="share">\[Share<span class="share-content">on
<a
href="https://bsky.app/intent/compose?text=%22Claw+Contraption%22+%2D+Day+13+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F13"
target="_blank">Bluesky</a> <a
href="https://twitter.com/intent/tweet?text=%22Claw+Contraption%22+%2D+Day+13+%2D+Advent+of+Code+2024&amp;url=https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F13&amp;related=ericwastl&amp;hashtags=AdventOfCode"
target="_blank">Twitter</a> <a href="javascript:void(0);"
onclick="var ms; try{ms=localStorage.getItem(&#39;mastodon.server&#39;)}finally{} if(typeof ms!==&#39;string&#39;)ms=&#39;&#39;; ms=prompt(&#39;Mastodon Server?&#39;,ms); if(typeof ms===&#39;string&#39; &amp;&amp; ms.length){this.href=&#39;https://&#39;+ms+&#39;/share?text=%22Claw+Contraption%22+%2D+Day+13+%2D+Advent+of+Code+2024+%23AdventOfCode+https%3A%2F%2Fadventofcode%2Ecom%2F2024%2Fday%2F13&#39;;try{localStorage.setItem(&#39;mastodon.server&#39;,ms);}finally{}}else{return false;}"
target="_blank">Mastodon</a></span>\]</span> this puzzle.
