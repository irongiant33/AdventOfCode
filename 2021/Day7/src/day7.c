#include "../include/day7.h"

#define DEBUG_PRINT false
#define SEARCH_WINDOW 1000

/**
 * @brief retrieve the puzzle input
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename)
{
    int num_delimiters = 1;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = ',';
    delimiters[0] = &delimiter1;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, num_delimiters, NULL);

    convert_input_to_long(puzzle_input);

    free(delimiters);
    delimiters = NULL;
    return puzzle_input;
}

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
compare(doubly_ll_item_t * item_a, doubly_ll_item_t * item_b)
{
    if(NULL == item_a || NULL == item_b)
    {
        fprintf(stderr, "cannot compare NULL values\n");
        return COMPARE_ERROR;
    }
    puzzle_item_t * puzzle_item_a = (puzzle_item_t *) item_a->item;
    puzzle_item_t * puzzle_item_b = (puzzle_item_t *) item_b->item;

    if(puzzle_item_a->value < puzzle_item_b->value)
    {
        return -1;
    }
    else if(puzzle_item_a->value == puzzle_item_b->value)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief find the median of a sorted list
 * 
 * @param list - a sorted list
 * @return int - median index. If the list is even, it returns the lower index.
 */
int
find_median(doubly_ll_t * list)
{
    if(NULL == list)
    {
        fprintf(stderr, "cannot find median in NULL list\n");
        return ERROR;
    }

    if(0 == list->max_size % 2)
    {
        return (list->max_size / 2) - 1;
    }
    else
    {
        return (list->max_size - 1) /2;
    }
}

/**
 * @brief calculate the fuel cost to reposition at index
 * 
 * @param puzzle_items - list of puzzle items
 * @param num_items - number of puzzle items
 * @param index - repositioning index
 * @return long - fuel cost
 */
long
calculate_fuel_cost(puzzle_item_t ** puzzle_items, int num_items, int index)
{
    if(NULL == puzzle_items)
    {
        fprintf(stderr, "puzzle items cannot be null to calculate cost\n");
        return ERROR;
    }

    long reposition_value = puzzle_items[index]->value;
    long cost = 0;
    for(int i = 0; i < num_items; i++)
    {
        long diff = puzzle_items[i]->value - reposition_value;
        if(diff < 0)
        {
            diff *= -1;
        }
        cost += diff;
    }
    return cost;
}

/**
 * @brief calculate the fuel cost to reposition at index, but the cost is increasing
 * 
 * @param puzzle_items - list of puzzle items
 * @param num_items - number of puzzle items
 * @param reposition_value - integer location to reposition to 
 * @return long - fuel cost
 */
long
calculate_fuel_cost_pt2(puzzle_item_t ** puzzle_items, int num_items, int reposition_value)
{
    if(NULL == puzzle_items)
    {
        fprintf(stderr, "puzzle items cannot be null to calculate cost\n");
        return ERROR;
    }

    int cost = 0;
    for(int i = 0; i < num_items; i++)
    {
        long diff = puzzle_items[i]->value - reposition_value;
        if(diff < 0)
        {
            diff *= -1;
        }
        float diff_fp = (float) diff;
        float extra_cost = (diff_fp / 2.0) * (1.0 + diff_fp);
        cost += (int) extra_cost;
    }
    return cost;
}

/**
 * @brief code to solve part 1 of Day 7 AoC
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
    
    //create doubly ll
    doubly_ll_t * list = doubly_ll_init(puzzle_input->num_items);
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        doubly_ll_add(list, (void *) puzzle_input->puzzle_items[i], 0);
    }
    
    if(DEBUG_PRINT)
    {
        printf("size of puzzle input: %d\n", puzzle_input->num_items);
        doubly_ll_item_t * fetched = doubly_ll_fetch(list, list->num_items - 1);
        puzzle_item_t * fetched_item = (puzzle_item_t *) fetched->item;
        puzzle_item_t * other_item = (puzzle_item_t *) list->head->item;
        printf("item %d value = %ld\n", list->num_items - 1, fetched_item->value);
        printf("item %d value = %ld\n", 0, other_item->value);
        printf("compare result %d\n", compare(fetched, list->head));
    }

    //sort doubly ll
    doubly_ll_sort(list, compare, 0, list->num_items - 1);

    //find the median
    int median_index = find_median(list);

    if(DEBUG_PRINT)
    {
        printf("median is %d\n", median_index);
    }

    //find minimum cost at indexes around the median
    long min_cost = __LONG_MAX__;
    int min_index = -1;
    for(int i = -SEARCH_WINDOW; i <= SEARCH_WINDOW; i ++)
    {
        int search_index = median_index + i;
        if(search_index >= 0 && search_index < puzzle_input->num_items)
        {
            long cost = calculate_fuel_cost(puzzle_input->puzzle_items, puzzle_input->num_items, search_index);
            if(cost < min_cost)
            {
                min_cost = cost;
                min_index = search_index;
            }
        }
    }

    if(DEBUG_PRINT)
    {
        printf("Min Index: %d, Min Cost %ld\n", min_index, min_cost);
    }

    //free and return running total
    free_puzzle_input(puzzle_input);
    doubly_ll_destroy(list);
    return (int) min_cost;
}

/**
 * @brief solves part 2 of day 7 AOC 2021
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
    
    //create doubly ll
    doubly_ll_t * list = doubly_ll_init(puzzle_input->num_items);
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        doubly_ll_add(list, (void *) puzzle_input->puzzle_items[i], 0);
    }

    //sort doubly ll
    doubly_ll_sort(list, compare, 0, list->num_items - 1);

    //find the median
    int median_index = find_median(list);

    //find minimum cost at indexes around the median
    long min_cost = __LONG_MAX__;
    int min_pos = -1;
    for(int i = -SEARCH_WINDOW; i <= SEARCH_WINDOW; i ++)
    {
        int search_pos = (int) puzzle_input->puzzle_items[median_index]->value + i;
        if(search_pos >= 0 && search_pos < puzzle_input->num_items)
        {
            long cost = calculate_fuel_cost_pt2(puzzle_input->puzzle_items, puzzle_input->num_items, search_pos);
            if(cost < min_cost)
            {
                min_cost = cost;
                min_pos = search_pos;
            }
        }
    }

    if(DEBUG_PRINT)
    {
        printf("Min Pos: %d, Min Cost %ld\n", min_pos, min_cost);
        long pos5cost = calculate_fuel_cost_pt2(puzzle_input->puzzle_items, puzzle_input->num_items, 5);
        printf("pos5cost %ld\n", pos5cost);
    }

    //free and return running total
    free_puzzle_input(puzzle_input);
    doubly_ll_destroy(list);
    return (int) min_cost;
}