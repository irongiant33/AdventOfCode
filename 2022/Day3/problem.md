[Advent of Code](/)
===================

-   [\[About\]](/2022/about)
-   [\[Events\]](/2022/events)
-   [\[Shop\]](https://teespring.com/stores/advent-of-code)
-   [\[Settings\]](/2022/settings)
-   [\[Log Out\]](/2022/auth/logout)

Samuel Miller <span class="star-count">2\*</span>

   <span class="title-event-wrap">var y=</span>[2022](/2022)<span class="title-event-wrap">;</span>
===================================================================================================

-   [\[Calendar\]](/2022)
-   [\[AoC++\]](/2022/support)
-   [\[Sponsors\]](/2022/sponsors)
-   [\[Leaderboard\]](/2022/leaderboard)
-   [\[Stats\]](/2022/stats)

Our [sponsors](/2022/sponsors) help make Advent of Code possible:

[Ahrefs](https://ahrefs.com/) - Work on the next general purpose search
engine, a world-class crawler, and real big data. Leveraging
bleeding-edge hardware and advanced programming technologies. From
anywhere in the world. OCaml, ReasonML, Dlang, C++

--- Day 3: Rucksack Reorganization ---
--------------------------------------

One Elf has the important job of loading all of the
[rucksacks](https://en.wikipedia.org/wiki/Rucksack) with supplies for
the <span title="Where there's jungle, there's hijinxs.">jungle</span>
journey. Unfortunately, that Elf didn't quite follow the packing
instructions, and so a few items now need to be rearranged.

Each rucksack has two large *compartments*. All items of a given type
are meant to go into exactly one of the two compartments. The Elf that
did the packing failed to follow this rule for exactly one item type per
rucksack.

The Elves have made a list of all of the items currently in each
rucksack (your puzzle input), but they need your help finding the
errors. Every item type is identified by a single lowercase or uppercase
letter (that is, `a` and `A` refer to different types of items).

The list of items for each rucksack is given as characters all on a
single line. A given rucksack always has the same number of items in
each of its two compartments, so the first half of the characters
represent items in the first compartment, while the second half of the
characters represent items in the second compartment.

For example, suppose you have the following list of contents from six
rucksacks:

    vJrwpWtwJgWrhcsFMMfFFhFp
    jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
    PmmdzqPrVvPwwTWBwg
    wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
    ttgJtRGJQctTZtZT
    CrZsJsPPZsGzwwsLwLmpwMDw

-   The first rucksack contains the items `vJrwpWtwJgWrhcsFMMfFFhFp`,
    which means its first compartment contains the items `vJrwpWtwJgWr`,
    while the second compartment contains the items `hcsFMMfFFhFp`. The
    only item type that appears in both compartments is lowercase `p`.
-   The second rucksack's compartments contain `jqHRNqRjqzjGDLGL` and
    `rsFMfFZSrLrFZsSL`. The only item type that appears in both
    compartments is uppercase `L`.
-   The third rucksack's compartments contain `PmmdzqPrV` and
    `vPwwTWBwg`; the only common item type is uppercase `P`.
-   The fourth rucksack's compartments only share item type `v`.
-   The fifth rucksack's compartments only share item type `t`.
-   The sixth rucksack's compartments only share item type `s`.

To help prioritize item rearrangement, every item type can be converted
to a *priority*:

-   Lowercase item types `a` through `z` have priorities 1 through 26.
-   Uppercase item types `A` through `Z` have priorities 27 through 52.

In the above example, the priority of the item type that appears in both
compartments of each rucksack is 16 (`p`), 38 (`L`), 42 (`P`), 22 (`v`),
20 (`t`), and 19 (`s`); the sum of these is `157`.

Find the item type that appears in both compartments of each rucksack.
*What is the sum of the priorities of those item types?*

To begin, [get your puzzle input](3/input).

Answer:

You can also <span class="share">\[Share<span class="share-content">on
[Twitter](https://twitter.com/intent/tweet?text=%22Rucksack+Reorganization%22+%2D+Day+3+%2D+Advent+of+Code+2022&url=https%3A%2F%2Fadventofcode%2Ecom%2F2022%2Fday%2F3&related=ericwastl&hashtags=AdventOfCode)
[Mastodon](javascript:void(0);)</span>\]</span> this puzzle.
