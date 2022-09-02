#include "../include/day11.h"

#define DEBUG_PRINT false
#define NUM_COLS 10

/**
 * @brief retrieve the puzzle input
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename)
{
    int num_delimiters = 0;
    puzzle_input_t * dirty_puzzle_input = read_file(filename, NULL, num_delimiters, NULL);
    puzzle_input_t * puzzle_input = filter_by_index(dirty_puzzle_input, NUM_COLS, NUM_COLS + 1);
    convert_input_to_long(puzzle_input);

    return puzzle_input;
}

/**
 * @brief comparison function to allow an octopus to be found in the flashed list
 * 
 * @param item_a - octopus item
 * @param data - octopus to be found
 * @return int - success code
 */
int
compare(doubly_ll_item_t * item_a, void * data)
{
    if(NULL == item_a || NULL == data)
    {
        fprintf(stderr, "cannot compare if an item is NULL\n");
        return ERROR;
    }
    octopus_t * existing_octopus = (octopus_t *) item_a->item;
    octopus_t * find_octopus = (octopus_t *) data;

    if(existing_octopus->row == find_octopus->row && existing_octopus->col == find_octopus->col)
    {
        return SUCCESS;
    }
    return 1;
}

/**
 * @brief add 1 to all of the neighbors in the graph
 * 
 * @param graph - graph to check
 * @param row - row of the original node
 * @param col - col of the original node
 * @param flashed - list of nodes who have flashed
 * @return int - success code
 */
int
add_to_neighbors(octopus_t *** graph, int row, int col, doubly_ll_t * flashed)
{
    if(NULL == graph)
    {
        fprintf(stderr, "cannot add to NULL graph\n");
        return ERROR;
    }

    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            int new_row = row + i;
            int new_col = col + j;
            bool row_check = (new_row >= 0) && (new_row < NUM_COLS);
            bool col_check = (new_col >= 0) && (new_col < NUM_COLS);
            bool origin_check = (i == 0) && (j == 0);

            if(row_check && col_check && !origin_check)
            {
                graph[new_row][new_col]->value += 1;
                //check to see if it flashed
                if(9 < graph[new_row][new_col]->value)
                {
                    //if it hasn't flashed this step, add it to flashed list
                    doubly_ll_item_t * is_found = doubly_ll_find(flashed, graph[new_row][new_col], compare);
                    if(NULL == is_found)
                    {
                        doubly_ll_add(flashed, (void *) graph[new_row][new_col], NULL);
                    }
                }
            }
        }
    }
    return SUCCESS;
}

/**
 * @brief code to solve part 1 of Day 11 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename, int num_steps)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }

    //find # of inputs on one line, then get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //initialize graph
    doubly_ll_t * flashed = doubly_ll_init(NUM_COLS * NUM_COLS);
    octopus_t *** graph = calloc(NUM_COLS, sizeof(long *));
    for(int i = 0; i < NUM_COLS; i++)
    {
        graph[i] = calloc(NUM_COLS, sizeof(octopus_t *));
        for(int j = 0; j < NUM_COLS; j++)
        {
            graph[i][j] = calloc(1, sizeof(octopus_t));
            graph[i][j]->value = puzzle_input->puzzle_items[i * NUM_COLS + j]->value;
            graph[i][j]->row = i;
            graph[i][j]->col = j;
        }
    }

    //for every step
    int num_flashes = 0;
    for(int step = 0; step < num_steps; step++)
    {
        if(DEBUG_PRINT)
        {
            printf("step %d\n", step);
            for(int i = 0; i < NUM_COLS; i++)
            {
                for(int j = 0; j < NUM_COLS; j++)
                {
                    printf("%d ", (int) graph[i][j]->value);
                }
                printf("\n");
            }
        }
        // perform initial increment
        for(int i = 0; i < NUM_COLS; i++)
        {
            for(int j = 0; j < NUM_COLS; j++)
            {
                //check if node needs to be reset to 0
                if(9 < graph[i][j]->value)
                {
                    graph[i][j]->value = 0;
                }

                //increment node number
                graph[i][j]->value += 1;

                //add to the flashed list
                if(9 < graph[i][j]->value)
                {
                    doubly_ll_add(flashed, (void *) graph[i][j], NULL);
                }
            }
        }

        // increment everyone's neighbors in the flashed list
        int flashed_index = 0;
        while(flashed_index < flashed->num_items)
        {
            doubly_ll_item_t * flashed_item = doubly_ll_fetch(flashed, flashed_index);
            octopus_t * octopus = (octopus_t *) flashed_item->item;
            add_to_neighbors(graph, octopus->row, octopus->col, flashed);
            flashed_index++;
        }

        //clear flashed list
        num_flashes += flashed->num_items;
        while(0 < flashed->num_items)
        {
            doubly_ll_remove(flashed, 0);
        }
    }

    //free puzzle input
    for(int i = 0; i < NUM_COLS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            free(graph[i][j]);
            graph[i][j] = NULL;
        }
        free(graph[i]);
        graph[i] = NULL;
    }
    free(graph);
    graph = NULL;
    doubly_ll_destroy(flashed);
    free_puzzle_input(puzzle_input);
    return num_flashes;
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

    //find # of inputs on one line, then get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //initialize graph
    doubly_ll_t * flashed = doubly_ll_init(NUM_COLS * NUM_COLS);
    octopus_t *** graph = calloc(NUM_COLS, sizeof(long *));
    for(int i = 0; i < NUM_COLS; i++)
    {
        graph[i] = calloc(NUM_COLS, sizeof(octopus_t *));
        for(int j = 0; j < NUM_COLS; j++)
        {
            graph[i][j] = calloc(1, sizeof(octopus_t));
            graph[i][j]->value = puzzle_input->puzzle_items[i * NUM_COLS + j]->value;
            graph[i][j]->row = i;
            graph[i][j]->col = j;
        }
    }

    //for every step
    int first_step = 0;
    int step = 0;
    while(0 == first_step)
    {
        if(DEBUG_PRINT)
        {
            printf("step %d\n", step);
            for(int i = 0; i < NUM_COLS; i++)
            {
                for(int j = 0; j < NUM_COLS; j++)
                {
                    printf("%d ", (int) graph[i][j]->value);
                }
                printf("\n");
            }
        }
        // perform initial increment
        for(int i = 0; i < NUM_COLS; i++)
        {
            for(int j = 0; j < NUM_COLS; j++)
            {
                //check if node needs to be reset to 0
                if(9 < graph[i][j]->value)
                {
                    graph[i][j]->value = 0;
                }

                //increment node number
                graph[i][j]->value += 1;

                //add to the flashed list
                if(9 < graph[i][j]->value)
                {
                    doubly_ll_add(flashed, (void *) graph[i][j], NULL);
                }
            }
        }

        // increment everyone's neighbors in the flashed list
        int flashed_index = 0;
        while(flashed_index < flashed->num_items)
        {
            doubly_ll_item_t * flashed_item = doubly_ll_fetch(flashed, flashed_index);
            octopus_t * octopus = (octopus_t *) flashed_item->item;
            add_to_neighbors(graph, octopus->row, octopus->col, flashed);
            flashed_index++;
        }

        //clear flashed list
        if(flashed->num_items == NUM_COLS * NUM_COLS)
        {
            first_step = step;
        }
        while(0 < flashed->num_items)
        {
            doubly_ll_remove(flashed, 0);
        }
        step++;
    }

    //free puzzle input
    for(int i = 0; i < NUM_COLS; i++)
    {
        for(int j = 0; j < NUM_COLS; j++)
        {
            free(graph[i][j]);
            graph[i][j] = NULL;
        }
        free(graph[i]);
        graph[i] = NULL;
    }
    free(graph);
    graph = NULL;
    doubly_ll_destroy(flashed);
    free_puzzle_input(puzzle_input);
    return (first_step + 1);
}