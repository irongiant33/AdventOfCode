#include "../../common/common.h"


typedef struct compound
{
    uint64_t    curr_freq;
    uint64_t    next_freq;
    int  element_ids[3]; //index 0 is the index of the generated element
                         //index 1 is the index of the first generated compound
                         //index 2 is the index of the second generated compound
}compound_t;

/**
 * @brief code to solve part 1 of Day 14 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename, int num_steps);

/**
 * @brief solves part 2 of day 14 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
uint64_t
part2(char * filename, int num_steps);