[Advent of Code](/)
===================

-   [\[About\]](/2022/about)
-   [\[Events\]](/2022/events)
-   [\[Shop\]](https://teespring.com/stores/advent-of-code)
-   [\[Settings\]](/2022/settings)
-   [\[Log Out\]](/2022/auth/logout)

Samuel Miller

   <span class="title-event-wrap">&lt;y&gt;</span>[2022](/2022)<span class="title-event-wrap">&lt;/y&gt;</span>
===============================================================================================================

-   [\[Calendar\]](/2022)
-   [\[AoC++\]](/2022/support)
-   [\[Sponsors\]](/2022/sponsors)
-   [\[Leaderboard\]](/2022/leaderboard)
-   [\[Stats\]](/2022/stats)

Our [sponsors](/2022/sponsors) help make Advent of Code possible:

[Accenture Federal
Services](https://www.accenture.com/us-en/industries/afs-index) -
Technology & ingenuity moving missions forward – come solve problems
with us. Hiring software engineers, developers, and more now. Refer
someone to earn up to $20K.

--- Day 1: Calorie Counting ---
-------------------------------

Santa's reindeer typically eat regular reindeer food, but they need a
lot of [magical energy](/2018/day/25) to deliver presents on Christmas.
For that, their favorite snack is a special type of *star* fruit that
only grows deep in the jungle. The Elves have brought you on their
annual expedition to the grove where the fruit grows.

To supply enough magical energy, the expedition needs to retrieve a
minimum of *fifty stars* by December 25th. Although the Elves assure you
that the grove has plenty of fruit, you decide to grab any fruit you see
along the way, just in case.

Collect stars by solving puzzles. Two puzzles will be made available on
each day in the Advent calendar; the second puzzle is unlocked when you
complete the first. Each puzzle grants *one star*. Good luck!

The jungle must be too overgrown and difficult to navigate in vehicles
or access from the air; the Elves' expedition traditionally goes on
foot. As your boats approach land, the Elves begin taking inventory of
their supplies. One important consideration is food - in particular, the
number of *Calories* each Elf is carrying (your puzzle input).

The Elves take turns writing down the number of Calories contained by
the various meals, snacks, rations, <span
title="By &quot;etc&quot;, you're pretty sure they just mean &quot;more snacks&quot;.">etc.</span>
that they've brought with them, one item per line. Each Elf separates
their own inventory from the previous Elf's inventory (if any) by a
blank line.

For example, suppose the Elves finish writing their items' Calories and
end up with the following list:

    1000
    2000
    3000

    4000

    5000
    6000

    7000
    8000
    9000

    10000

This list represents the Calories of the food carried by five Elves:

-   The first Elf is carrying food with `1000`, `2000`, and `3000`
    Calories, a total of `6000` Calories.
-   The second Elf is carrying one food item with `4000` Calories.
-   The third Elf is carrying food with `5000` and `6000` Calories, a
    total of `11000` Calories.
-   The fourth Elf is carrying food with `7000`, `8000`, and `9000`
    Calories, a total of `24000` Calories.
-   The fifth Elf is carrying one food item with `10000` Calories.

In case the Elves get hungry and need extra snacks, they need to know
which Elf to ask: they'd like to know how many Calories are being
carried by the Elf carrying the *most* Calories. In the example above,
this is *`24000`* (carried by the fourth Elf).

Find the Elf carrying the most Calories. *How many total Calories is
that Elf carrying?*

To begin, [get your puzzle input](1/input).

Answer:

You can also <span class="share">\[Share<span class="share-content">on
[Twitter](https://twitter.com/intent/tweet?text=%22Calorie+Counting%22+%2D+Day+1+%2D+Advent+of+Code+2022&url=https%3A%2F%2Fadventofcode%2Ecom%2F2022%2Fday%2F1&related=ericwastl&hashtags=AdventOfCode)
[Mastodon](javascript:void(0);)</span>\]</span> this puzzle.