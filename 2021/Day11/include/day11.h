#include "../../common/common.h"

typedef struct octopus
{
    long value;
    int row;
    int col;
} octopus_t;

/**
 * @brief code to solve part 1 of Day 11 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename, int num_steps);

/**
 * @brief solves part 2 of day 11 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename);