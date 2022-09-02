#include "../../common/common.h"

typedef struct path
{
    doubly_ll_t * list;
    int * visited;
    long cost;
    long heuristic;
}path_t;

typedef struct graph_data
{
    long index;
    puzzle_item_t * data;
}graph_data_t;

/**
 * @brief code to solve part 1 of Day 14 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename);

/**
 * @brief solves part 2 of day 14 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename);