#include "../include/day25.h"

#define DEBUG_PRINT false

/**
 * @brief retrieve the puzzle input that is the dot matrix
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename)
{
    int num_delimiters = 2;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = ',';
    char delimiter2 = '\n';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;

    char end_char = 'f';
    puzzle_input_t * dirty_puzzle_input = read_file(filename, delimiters, num_delimiters, &end_char);
    puzzle_input_t * puzzle_input = filter_by_length(dirty_puzzle_input, 0);
    convert_input_to_long(puzzle_input);

    free(delimiters);
    delimiters = NULL;
    return puzzle_input;
}

/**
 * @brief code to solve part 1 of Day 14 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }

    //get the coordinates of the dot inputs
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //free and return
    free_puzzle_input(puzzle_input);
    return 0;
}

/**
 * @brief solves part 2 of day 11 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }

    //get the coordinates of the dot inputs
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //free and return
    free_puzzle_input(puzzle_input);
    return 0;
}