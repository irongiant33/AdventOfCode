#include "../include/day1.h"

#define WINDOW_LEN 3

/**
 * @brief code to solve part 1 of Day 1 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename)
{
    //read in file
    char ** delimiters = calloc(1, sizeof(char *));
    char delimiter = '\n';
    delimiters[0] = &delimiter;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, 1, NULL);


    //solve part 1
    int num_increases = 0;
    char * end_ptr;
    long prev_value = strtol(puzzle_input->puzzle_items[0]->char_val, &end_ptr, 10);
    if (errno != 0) {
        perror("strtol");
        return ERROR;
    }

    if (end_ptr == puzzle_input->puzzle_items[0]->char_val) {
        fprintf(stderr, "No digits were found\n");
        return ERROR;
    }

    for(int i = 1; i < puzzle_input->num_items; i++)
    {
        long next_val = strtol(puzzle_input->puzzle_items[i]->char_val, &end_ptr, 10);
        if (errno != 0) {
            perror("strtol");
            return ERROR;
        }

        if (end_ptr == puzzle_input->puzzle_items[0]->char_val) {
            fprintf(stderr, "No digits were found\n");
            return ERROR;
        }

        if(next_val > prev_value)
        {
            num_increases += 1;
        }
        prev_value = next_val;
    }

    //free and end
    free(delimiters);
    delimiters = NULL;
    free_puzzle_input(puzzle_input);
    return num_increases;
}

/**
 * @brief calculates the sum of a range of long values
 * 
 * @param puzzle_items - list of puzzle items to average
 * @param start - starting index of the window
 * @param length - amount of values to sum
 * @return long - the sum of a window of values
 */
long
calc_window_sum(puzzle_item_t ** puzzle_items, int start, int length)
{
    if(NULL == puzzle_items)
    {
        fprintf(stderr, "puzzle items cannot be null\n");
        return ERROR;
    }

    long average = 0;
    char * end_ptr;
    for(int i = start; i < (start + length); i++)
    {
        if(NULL == puzzle_items[i])
        {
            fprintf(stderr, "puzzle item at index %d is NULL\n", i);
            return ERROR;
        }

        long val = strtol(puzzle_items[i]->char_val, &end_ptr, 10);
        if (errno != 0) {
            perror("strtol");
            return ERROR;
        }

        if (end_ptr == puzzle_items[i]->char_val) {
            fprintf(stderr, "No digits were found\n");
            return ERROR;
        }

        average += val;
    }
    return average;
}


/**
 * @brief solves part 2 of day 1 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename)
{
    //read in file
    char ** delimiters = calloc(1, sizeof(char *));
    char delimiter = '\n';
    delimiters[0] = &delimiter;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, 1, NULL);


    //solve part 2
    int num_increases = 0;
    long prev_average = calc_window_sum(puzzle_input->puzzle_items, 0, WINDOW_LEN);

    for(int i = 1; i < (puzzle_input->num_items - WINDOW_LEN + 1); i++)
    {
        long next_average = calc_window_sum(puzzle_input->puzzle_items, i, WINDOW_LEN);

        if(next_average > prev_average)
        {
            num_increases += 1;
        }
        prev_average = next_average;
    }

    //free and end
    free(delimiters);
    delimiters = NULL;
    free_puzzle_input(puzzle_input);
    return num_increases;   
}