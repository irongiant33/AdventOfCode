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
 * @brief function to use to compare values for sort
 * 
 * @param item_a
 * @param item_b 
 * @return int -1 if item_a < item_b
 *              0 if item_a == item_b
 *              1 if item_a > item_b
 */
int
compare(doubly_ll_item_t * item_a, doubly_ll_item_t * item_b);

/**
 * @brief find the median of a sorted list
 * 
 * @param list - a sorted list
 * @return int - median index. If the list is even, it returns the lower index.
 */
int
find_median(doubly_ll_t * list);

/**
 * @brief calculate the fuel cost to reposition at index
 * 
 * @param puzzle_items - list of puzzle items
 * @param num_items - number of puzzle items
 * @param index - repositioning index
 * @return long - fuel cost
 */
long
calculate_fuel_cost(puzzle_item_t ** puzzle_items, int num_items, int index);

/**
 * @brief calculate the fuel cost to reposition at index, but the cost is increasing
 * 
 * @param puzzle_items - list of puzzle items
 * @param num_items - number of puzzle items
 * @param reposition_value - integer location to reposition to 
 * @return long - fuel cost
 */
long
calculate_fuel_cost_pt2(puzzle_item_t ** puzzle_items, int num_items, int reposition_value);

/**
 * @brief code to solve part 1 of Day 7 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename);

/**
 * @brief solves part 2 of day 7 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename);