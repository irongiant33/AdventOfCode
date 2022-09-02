#include "CUnit/Basic.h"

#include "../include/day14.h"

void
test_part1_example(void)
{
    int test_part1 = part1("../src/test_input.txt", 10);
    printf("Part 1 example 1 answer is: %d\n", test_part1);
    CU_ASSERT_EQUAL(test_part1, 1588);
}

void
test_part1(void)
{
    int part1_ans = part1("../src/input.txt", 10);
    printf("Part 1 answer is: %d\n", part1_ans);
}

void
test_part2_example(void)
{
    uint64_t test_part2 = part2("../src/test_input.txt", 40);
    printf("Part 2 example answer is: %lu\n", test_part2);
    CU_ASSERT_EQUAL(test_part2, 2188189693529);
}

void
test_part2(void)
{
    uint64_t part2_ans = part2("../src/input.txt", 40);
    printf("Part 2 answer is: %lu\n", part2_ans);
}