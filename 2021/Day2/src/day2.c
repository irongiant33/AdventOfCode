#include "../include/day2.h"

#define DEBUG_PRINT false

/**
 * @brief code to solve part 1 of Day 2 AoC
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

    //read in file
    char ** delimiters = calloc(2, sizeof(char *));
    char delimiter1 = '\n';
    char delimiter2 = ' ';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, 2, NULL);

    //solve part 1
    printf("solving\n");
    long x_pos = 0;
    long depth = 0;
    for(int i = 2; i < puzzle_input->num_items; i+=2)
    {
        char * end_ptr;
        long movement_amount = strtol(puzzle_input->puzzle_items[i - 1]->char_val, &end_ptr, 10);
	if (errno != 0) {
            perror("strtol");
            return ERROR;
        }

        if (end_ptr == puzzle_input->puzzle_items[i - 1]->char_val) {
            fprintf(stderr, "No digits were found\n");
            return ERROR;
        }

        switch (puzzle_input->puzzle_items[i - 2]->char_val[0])
        {
        case 'f':
            x_pos = x_pos + movement_amount;
            break;
        case 'u':
            depth = depth - movement_amount;
            break;
        case 'd':
            depth = depth + movement_amount;
            break;
        default:
            fprintf(stderr, "unrecognized command %s\n", puzzle_input->puzzle_items[i]->char_val);
            break;
        }

        if(DEBUG_PRINT)
        {
            printf("X: %ld, D: %ld\n", x_pos, depth);
        }
    }

    //free and end
    free(delimiters);
    delimiters = NULL;
    free_puzzle_input(puzzle_input);
    return x_pos * depth;
}

/**
 * @brief solves part 2 of day 2 AOC 2021
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

    //read in file
    char ** delimiters = calloc(2, sizeof(char *));
    char delimiter1 = '\n';
    char delimiter2 = ' ';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, 2, NULL);

    //solve part 1
    long x_pos = 0;
    long depth = 0;
    long aim = 0;
    for(int i = 2; i < puzzle_input->num_items; i+=2)
    {
        char * end_ptr;
        long movement_amount = strtol(puzzle_input->puzzle_items[i - 1]->char_val, &end_ptr, 10);
        if (errno != 0) {
            perror("strtol");
            return ERROR;
        }

        if (end_ptr == puzzle_input->puzzle_items[i - 1]->char_val) {
            fprintf(stderr, "No digits were found\n");
            return ERROR;
        }

        switch (puzzle_input->puzzle_items[i - 2]->char_val[0])
        {
        case 'f':
            x_pos = x_pos + movement_amount;
            depth = depth + aim * movement_amount;
            break;
        case 'u':
            aim = aim - movement_amount;
            break;
        case 'd':
            aim = aim + movement_amount;
            break;
        default:
            fprintf(stderr, "unrecognized command %s\n", puzzle_input->puzzle_items[i]->char_val);
            break;
        }

        if(DEBUG_PRINT)
        {
            printf("X: %ld, D: %ld\n", x_pos, depth);
        }
    }

    //free and end
    free(delimiters);
    delimiters = NULL;
    free_puzzle_input(puzzle_input);
    return x_pos * depth;
}
