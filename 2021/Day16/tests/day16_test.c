#include "CUnit/Basic.h"

#include "../include/day16.h"

void
test_part1_example(void)
{
    int test_part1 = part1("../src/test_input.txt");
    printf("Part 1 example 1 answer is: %d\n", test_part1);
    CU_ASSERT_EQUAL(test_part1, 16);
}

void
test_part1(void)
{
    int part1_ans = part1("../src/input.txt");
    printf("Part 1 answer is: %d\n", part1_ans);
}

void
test_part2_example(void)
{
    int test_part2 = part2("../src/test_input.txt");
    printf("Part 2 example answer is: %d\n", test_part2);
    CU_ASSERT_EQUAL(test_part2, 0);
}

void
test_part2(void)
{
    int part2_ans = part2("../src/input.txt");
    printf("Part 2 answer is: %d\n", part2_ans);
}