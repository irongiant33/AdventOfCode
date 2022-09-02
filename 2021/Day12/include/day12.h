#include "../../common/common.h"

typedef struct cave
{
    char * label;
    bool is_big;
    bool is_end;
}cave_t;

/**
 * @brief code to solve part 1 of Day 12 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename);

/**
 * @brief solves part 2 of day 12 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename);