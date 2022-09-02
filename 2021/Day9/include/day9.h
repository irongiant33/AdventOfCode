#include "../../common/common.h"

typedef struct grid_item
{
    int row;
    int col;
    int value;
} grid_item_t;

/**
 * @brief code to solve part 1 of Day 9 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename);

/**
 * @brief solves part 2 of day 9 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename);