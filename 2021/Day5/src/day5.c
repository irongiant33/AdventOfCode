#include "../include/day5.h"

/**
 * @brief retrieve the puzzle input
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename)
{
    int num_delimiters = 3;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = '\n';
    char delimiter2 = ',';
    char delimiter3 = ' ';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    delimiters[2] = &delimiter3;
    puzzle_input_t * dirty_puzzle_input = read_file(filename, delimiters, num_delimiters, NULL);

    //remove all `->` from the puzzle input
    puzzle_input_t * puzzle_input = filter_by_index(dirty_puzzle_input, 2, 5);

    convert_input_to_long(puzzle_input);

    free(delimiters);
    delimiters = NULL;
    return puzzle_input;
}

/**
 * @brief convert the puzzle input to a list of vents
 * 
 * @param puzzle_input - puzzle input
 * @param num_vents - number of vents to assign
 * @return vent_t** - list of vent structures
 */
vent_t **
assign_input_to_vents(puzzle_input_t * puzzle_input, int num_vents)
{
    vent_t ** vents = calloc(num_vents, sizeof(vent_t *));
    for(int i = 0; i < num_vents; i++)
    {
        vent_t * vent = calloc(1, sizeof(vent_t));
        
        //assign inputs to variables
        int x1 = (int) puzzle_input->puzzle_items[i*INPUTS_PER_VENT + 0]->value;
        int y1 = (int) puzzle_input->puzzle_items[i*INPUTS_PER_VENT + 1]->value;
        int x2 = (int) puzzle_input->puzzle_items[i*INPUTS_PER_VENT + 2]->value;
        int y2 = (int) puzzle_input->puzzle_items[i*INPUTS_PER_VENT + 3]->value;

        //calculate dx
        int dx = 0;
        if(x2 < x1)
        {
            dx = -1;
        }
        else if(x2 > x1)
        {
            dx = 1;
        }

        //calculate dy
        int dy = 0;
        if(y2 < y1)
        {
            dy = -1;
        }
        else if(y2 > y1)
        {
            dy = 1;
        }

        //calculate length
        int length = (x2 - x1) * dx + 1;
        if(0 == dx)
        {
            length = (y2 - y1) * dy + 1;
        }

        //determine if vent is diagonal
        bool is_diag = false;
        if(dx !=0 && dy != 0)
        {
            is_diag = true;
        }

        //assign to vent
        vent->x_pos = x1;
        vent->y_pos = y1;
        vent->dx = dx;
        vent->dy = dy;
        vent->length = length;
        vent->is_diag = is_diag;

        vents[i] = vent;
    }
    return vents;
}

/**
 * @brief code to solve part 1 of Day 5 AoC
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

    //get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //assign puzzle input to list of vents
    int num_vents = puzzle_input->num_items / INPUTS_PER_VENT;
    vent_t ** vents = assign_input_to_vents(puzzle_input, num_vents);

    //create 2D grid and variable to track overlaps
    int num_overlaps = 0;
    int ** vent_grid = calloc(GRID_DIM, sizeof(int *));
    for(int i = 0; i < GRID_DIM; i++)
    {
        vent_grid[i] = calloc(GRID_DIM, sizeof(int));
        for(int j = 0; j < GRID_DIM; j++)
        {
            vent_grid[i][j] = 0;
        }
    }

    //count the number of overlaps for all non-diagonal vents
    for(int i = 0; i < num_vents; i++)
    {
        if(!vents[i]->is_diag)
        {
            int x_pos = vents[i]->x_pos;
            int y_pos = vents[i]->y_pos;
            for(int j = 0; j < vents[i]->length; j++)
            {
                vent_grid[y_pos][x_pos] += 1;
                if(2 == vent_grid[y_pos][x_pos])
                {
                    num_overlaps += 1;
                }
                x_pos += vents[i]->dx;
                y_pos += vents[i]->dy;
            }
        }
    }
    
    //free and return
    free_puzzle_input(puzzle_input);
    for(int i = 0; i < num_vents; i++)
    {
        free(vents[i]);
        vents[i] = NULL;
    }
    free(vents);
    for(int i = 0; i < GRID_DIM; i++)
    {
        free(vent_grid[i]);
        vent_grid[i] = NULL;
    }
    free(vent_grid);
    vent_grid = NULL;
    vents = NULL;
    return num_overlaps;
}

/**
 * @brief solves part 2 of day 4 AOC 2021
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

    //get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //assign puzzle input to list of vents
    int num_vents = puzzle_input->num_items / INPUTS_PER_VENT;
    vent_t ** vents = assign_input_to_vents(puzzle_input, num_vents);

    //create 2D grid and variable to track overlaps
    int num_overlaps = 0;
    int ** vent_grid = calloc(GRID_DIM, sizeof(int *));
    for(int i = 0; i < GRID_DIM; i++)
    {
        vent_grid[i] = calloc(GRID_DIM, sizeof(int));
        for(int j = 0; j < GRID_DIM; j++)
        {
            vent_grid[i][j] = 0;
        }
    }

    //count the number of overlaps for all non-diagonal vents
    for(int i = 0; i < num_vents; i++)
    {
        int x_pos = vents[i]->x_pos;
        int y_pos = vents[i]->y_pos;
        for(int j = 0; j < vents[i]->length; j++)
        {
            vent_grid[y_pos][x_pos] += 1;
            if(2 == vent_grid[y_pos][x_pos])
            {
                num_overlaps += 1;
            }
            x_pos += vents[i]->dx;
            y_pos += vents[i]->dy;
        }
    }
    
    //free and return
    free_puzzle_input(puzzle_input);
    for(int i = 0; i < num_vents; i++)
    {
        free(vents[i]);
        vents[i] = NULL;
    }
    free(vents);
    for(int i = 0; i < GRID_DIM; i++)
    {
        free(vent_grid[i]);
        vent_grid[i] = NULL;
    }
    free(vent_grid);
    vent_grid = NULL;
    vents = NULL;
    return num_overlaps;
}