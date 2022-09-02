#include "CUnit/Basic.h"

#include "../include/day6.h"

void
test_part1_example(void)
{
    long test_part1 = part1("../src/test_input.txt", 80);
    printf("Part 1 example answer is: %ld\n", test_part1);
    CU_ASSERT_EQUAL(test_part1, 5934);
}

void
test_part1(void)
{
    long part1_ans = part1("../src/input.txt", 80);
    printf("Part 1 answer is: %ld\n", part1_ans);
}

void
test_part2_example(void)
{
    long test_part2 = part2("../src/test_input.txt");
    printf("Part 2 example answer is: %ld\n", test_part2);
    CU_ASSERT_EQUAL(test_part2, 26984457539);
}

void
test_part2(void)
{
    long part2_ans = part2("../src/input.txt");
    printf("Part 2 answer is: %ld\n", part2_ans);
}