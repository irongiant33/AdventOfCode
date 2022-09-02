#include "../../common/common.h"

#define INPUTS_PER_VENT    4
#define GRID_DIM        1000

typedef struct vent
{
    int x_pos;
    int y_pos;
    int dx;
    int dy;
    int length;
    bool is_diag;
}vent_t;

/**
 * @brief retrieve the puzzle input
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename);

/**
 * @brief code to solve part 1 of Day 5 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename);

/**
 * @brief solves part 2 of day 5 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename);