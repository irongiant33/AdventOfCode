#include "../include/day9.h"

#define DEBUG_PRINT false

#define NUM_ADJACENT 4
#define MAX_NUM_LOW_POINTS 1000
#define DEFAULT_BASIN_SIZE 10000

/**
 * @brief retrieve the puzzle input
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename, int num_cols)
{
    int num_delimiters = 0;
    puzzle_input_t * dirty_puzzle_input = read_file(filename, NULL, num_delimiters, NULL);
    puzzle_input_t * puzzle_input = filter_by_index(dirty_puzzle_input, num_cols, num_cols + 1);
    convert_input_to_long(puzzle_input);
    return puzzle_input;
}

/**
 * @brief check if the item at (row, col) is less than the item at (row_c, col_c)
 *        return true if this is the case. return true if there is no value at
 *        the check position.
 * 
 * @param grid - grid to check on
 * @param num_rows - number of rows in the grid
 * @param num_cols - number of cols in the grid
 * @param row - origin row index
 * @param col - origin col index
 * @param row_c - check row index
 * @param col_c - check col index
 * @return true 
 */
bool
check(long ** grid, int num_rows, int num_cols, int row, int col, int row_c, int col_c)
{
    if(NULL == grid)
    {
        fprintf(stderr, "cannot check NULL grid\n");
        return false;
    }

    //return true if the checks are out of bounds
    if(row_c < 0 || row_c >= num_rows)
    {
        return true;
    }
    if(col_c < 0 || col_c >= num_cols)
    {
        return true;
    }

    //do actual comparison
    bool comparison = false;
    if(grid[row][col] < grid[row_c][col_c])
    {
        comparison = true;
    }
    return comparison;
}

/**
 * @brief code to solve part 1 of Day 9 AoC
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

    //find # of inputs on one line, then get puzzle input
    char end_char = '\n';
    int num_cols = 0;
    int num_rows = 0;
    puzzle_input_t * first_line = read_file(filename, NULL, 0, &end_char);
    num_cols = first_line->num_items;
    puzzle_input_t * puzzle_input = get_puzzle_input(filename, num_cols);
    num_rows = puzzle_input->num_items / num_cols;

    //assign puzzle input to 2D long matrix
    long ** grid = calloc(num_rows, sizeof(long *));
    int puzzle_index = 0;
    for(int i = 0; i < num_rows; i++)
    {
        grid[i] = calloc(num_cols, sizeof(long));
        for(int j = 0; j < num_cols; j++)
        {
            grid[i][j] = puzzle_input->puzzle_items[puzzle_index]->value;
            puzzle_index++;
        }
    }

    //calculate risk levels
    int risk_level = 0;
    for(int i = 0; i < num_rows; i++)
    {
        for(int j = 0; j < num_cols; j++)
        {
            bool left_check  = check(grid, num_rows, num_cols, i, j, i - 1, j    );
            bool up_check    = check(grid, num_rows, num_cols, i, j, i    , j - 1);
            bool right_check = check(grid, num_rows, num_cols, i, j, i + 1, j    );
            bool down_check  = check(grid, num_rows, num_cols, i, j, i    , j + 1);
            if(left_check && up_check && right_check && down_check)
            {
                risk_level += (int) grid[i][j];
                risk_level += 1;
            }
        }
    }

    //free and return running total
    free_puzzle_input(puzzle_input);
    free_puzzle_input(first_line);
    for(int i = 0; i < num_rows; i++)
    {
        free(grid[i]);
        grid[i] = NULL;
    }
    free(grid);
    return risk_level;
}

/**
 * @brief compare function for doubly ll to help it sort values
 * 
 * @param item_a 
 * @param item_b 
 * @return int 
 */
int
compare(doubly_ll_item_t * item_a, doubly_ll_item_t * item_b)
{
    if(NULL == item_a || NULL == item_b)
    {
        fprintf(stderr, "cannot compare null items\n");
        return COMPARE_ERROR;
    }

    int * value_a = (int *) item_a->item;
    int * value_b = (int *) item_b->item;

    if(*value_a < *value_b)
    {
        return -1;
    }
    else if(*value_a == *value_b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief check to see if the row, col is already in a list
 * 
 * @param list - list to check
 * @param row - row index to check
 * @param col - col index to check
 * @return true - if row, col in list
 * @return false - if row, col not in list or if error exists
 */
bool
check_in_list(doubly_ll_t * list, int row, int col)
{
    if(NULL == list)
    {
        fprintf(stderr, "cannot check contents of NULL list\n");
        return false;
    }

    bool in_list = false;
    int index = 0;
    while(!in_list && index < list->num_items)
    {
        doubly_ll_item_t * item = doubly_ll_fetch(list, index);
        grid_item_t * grid_item = (grid_item_t *) item->item;
        if(grid_item->row == row && grid_item->col == col)
        {
            in_list = true;
        }
        index++;
    }
    return in_list;
}

/**
 * @brief add the item at (row , col) to the unsearched list if it is not
 *        in the basin
 * 
 * @param basin 
 * @param unsearched 
 * @param grid 
 * @param row 
 * @param col 
 * @return int status code
 */
int
add_to_unsearched(doubly_ll_t * basin, doubly_ll_t * unsearched, long ** grid, int num_rows, int num_cols, int row, int col)
{
    if(NULL == basin || NULL == unsearched)
    {
        fprintf(stderr, "cannot add to unsearched with NULL basin or unsearched list\n");
        return ERROR;
    }

    //do not add out of bound value to unsearched
    if(0 > row || num_rows <= row)
    {
        return SUCCESS;
    }
    if(0 > col || num_cols <= col)
    {
        return SUCCESS;
    }

    //do not add value of 9 to unsearched
    if(9 == grid[row][col])
    {
        return SUCCESS;
    }

    //check to see if the item is already in the basin
    bool in_basin = check_in_list(basin, row, col);

    //check to see if the item is already in unsearched
    bool in_unsearched = check_in_list(unsearched, row, col);

    //if not in basin, add to unsearched
    if(!in_basin && !in_unsearched)
    {
        grid_item_t * new_item = calloc(1, sizeof(grid_item_t));
        new_item->row = row;
        new_item->col = col;
        new_item->value = (int) grid[row][col];
        doubly_ll_add(unsearched, (void *) new_item, NULL);
    }
    return SUCCESS;
}

/**
 * @brief find the number of items in the grid within the basin
 * 
 * @param grid - grid to search
 * @param num_rows - number of rows in the grid
 * @param num_cols - number of columns in the grid
 * @param row - row index of the low point
 * @param col - col index of the low point
 * @return int - number of items in the basin
 */
int
find_basin_size(long ** grid, int num_rows, int num_cols, int row, int col)
{
    if(NULL == grid)
    {
        fprintf(stderr, "cannot find the basin size for a null grid\n");
        return ERROR;
    }

    //initialize unsearched list and basin
    int basin_size = 0;
    doubly_ll_t * unsearched = doubly_ll_init(DEFAULT_BASIN_SIZE);
    doubly_ll_t * basin = doubly_ll_init(DEFAULT_BASIN_SIZE);

    //add low point to unsearched and start building out basin
    grid_item_t * low_point = calloc(1, sizeof(grid_item_t));
    low_point->row = row;
    low_point->col = col;
    low_point->value = (int) grid[row][col];
    doubly_ll_add(unsearched, (void *) low_point, NULL);

    while(0 < unsearched->num_items)
    {
        int num_unsearched = unsearched->num_items;
        for(int i = 0; i < num_unsearched; i++)
        {
            doubly_ll_item_t * unsearched_item = doubly_ll_fetch(unsearched, i);
            grid_item_t * unsearched_grid = (grid_item_t *) unsearched_item->item;
            if(DEBUG_PRINT)
            {
                //print unsearched item
                printf("searching around (%d, %d)\n", unsearched_grid->row, unsearched_grid->col);
            }

            //add neighbors to unsearched list if they are not already in the list or in the basin
            int left_add  = add_to_unsearched(basin, unsearched, grid, num_rows, num_cols, unsearched_grid->row - 1, unsearched_grid->col    );
            int up_add    = add_to_unsearched(basin, unsearched, grid, num_rows, num_cols, unsearched_grid->row    , unsearched_grid->col - 1);
            int right_add = add_to_unsearched(basin, unsearched, grid, num_rows, num_cols, unsearched_grid->row + 1, unsearched_grid->col    );
            int down_add  = add_to_unsearched(basin, unsearched, grid, num_rows, num_cols, unsearched_grid->row    , unsearched_grid->col + 1);

            if(left_add + right_add + up_add + down_add != 0)
            {
                fprintf(stderr, "error adding to unsearched!\n");
                return ERROR;
            }

            //add unsearched item to basin
            doubly_ll_add(basin, (void *) unsearched_grid, NULL);
        }

        //remove searched items from the unsearched list
        for(int i = 0; i < num_unsearched; i++)
        {
            doubly_ll_remove(unsearched, 0);
        }
    }
    basin_size = basin->num_items;

    //free each item within the basin. The unsearched list is empty by this point.
    doubly_ll_destroy(unsearched);
    while(0 < basin->num_items)
    {
        grid_item_t * grid_item = (grid_item_t *) doubly_ll_remove(basin, 0);
        free(grid_item);
        grid_item = NULL;
    }
    doubly_ll_destroy(basin);
    return basin_size;
}

/**
 * @brief solves part 2 of day 9 AOC 2021
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
    char end_char = '\n';
    int num_cols = 0;
    int num_rows = 0;
    puzzle_input_t * first_line = read_file(filename, NULL, 0, &end_char);
    num_cols = first_line->num_items;
    puzzle_input_t * puzzle_input = get_puzzle_input(filename, num_cols);
    num_rows = puzzle_input->num_items / num_cols;

    //assign puzzle input to 2D long matrix
    long ** grid = calloc(num_rows, sizeof(long *));
    int puzzle_index = 0;
    for(int i = 0; i < num_rows; i++)
    {
        grid[i] = calloc(num_cols, sizeof(long));
        for(int j = 0; j < num_cols; j++)
        {
            grid[i][j] = puzzle_input->puzzle_items[puzzle_index]->value;
            puzzle_index++;
        }
    }

    //calculate basin sizes for every low point
    doubly_ll_t * basin_sizes = doubly_ll_init(MAX_NUM_LOW_POINTS);
    for(int i = 0; i < num_rows; i++)
    {
        for(int j = 0; j < num_cols; j++)
        {
            bool left_check  = check(grid, num_rows, num_cols, i, j, i - 1, j    );
            bool up_check    = check(grid, num_rows, num_cols, i, j, i    , j - 1);
            bool right_check = check(grid, num_rows, num_cols, i, j, i + 1, j    );
            bool down_check  = check(grid, num_rows, num_cols, i, j, i    , j + 1);
            //check to see if you are in a low point
            if(left_check && up_check && right_check && down_check)
            {
                int * basin_size = calloc(1, sizeof(int));
                *basin_size = find_basin_size(grid, num_rows, num_cols, i, j);
                doubly_ll_add(basin_sizes, (void *) basin_size, NULL);
            }
        }
    }

    //find largest 3 basins
    doubly_ll_sort(basin_sizes, compare, 0, basin_sizes->num_items - 1);
    int basin_product = 1;
    //get top 3 basin sizes
    for(int i = 1; i <= 3; i ++)
    {
        doubly_ll_item_t * max_item = doubly_ll_fetch(basin_sizes, basin_sizes->num_items - i);
        int * max_value = (int *) max_item->item;
        basin_product *= *max_value;
    }

    //free and return running total
    free_puzzle_input(puzzle_input);
    free_puzzle_input(first_line);
    for(int i = 0; i < num_rows; i++)
    {
        free(grid[i]);
        grid[i] = NULL;
    }
    free(grid);
    while(0 < basin_sizes->num_items)
    {
        int * basin_size = (int *) doubly_ll_remove(basin_sizes, 0);
        free(basin_size);
        basin_size = NULL;
    }
    doubly_ll_destroy(basin_sizes);
    return basin_product;
}