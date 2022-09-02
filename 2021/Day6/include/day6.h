#include "../../common/common.h"

/**
 * @brief retrieve the puzzle input
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename);

/**
 * @brief code to solve part 1 of Day 6 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
long
part1(char * filename, int final_day);

/**
 * @brief solves part 2 of day 6 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
long
part2(char * filename);