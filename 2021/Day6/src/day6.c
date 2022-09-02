#include "../include/day6.h"

#define MAX_INITIAL_AGE  5
#define DEBUG_PRINT   false

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
 * @brief recursive function to find the number of sub-births
 * 
 * @param birthday_list 
 * @return int 
 */
long
find_sub_births(int birth_date, int age, int final_day)
{
    int birthday_index = age + birth_date + 1;
    long num_sub_births = 0;
    while(birthday_index <= final_day)
    {
        num_sub_births += 1;
        num_sub_births += find_sub_births(birthday_index, 8, final_day);
        birthday_index += 7;
    }
    return num_sub_births;
}

/**
 * @brief code to solve part 1 of Day 6 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
long
part1(char * filename, int final_day)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }

    //get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //find the number of fish born per initial age
    long * num_fish = calloc(MAX_INITIAL_AGE + 1, sizeof(long));
    for(int age = 1; age < (MAX_INITIAL_AGE + 1); age++)
    {
        long num_births = 1;
        num_births += find_sub_births(0, age, final_day);

        if(DEBUG_PRINT)
        {
            printf("fish initial age %d, num births %ld\n", age, num_births);
        }

        num_fish[age] = num_births;
    }

    //loop through the input and add the number of fish born for that age to the running total
    long total_num_fish = 0;
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        int age_index = (int) puzzle_input->puzzle_items[i]->value;
        total_num_fish += num_fish[age_index];
    }
    
    //free and return running total
    free_puzzle_input(puzzle_input);
    free(num_fish);
    num_fish = 0;
    return total_num_fish;
}

/**
 * @brief solves part 2 of day 6 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
long
part2(char * filename)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }

    //get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //generated these numbers by running the Day 6 executable for part 1 with the input
    //of 256 without valgrind
    long num_fish[6] = {0, 6206821033, 5617089148, 5217223242, 4726100874, 4368232009};

    //loop through the input and add the number of fish born for that age to the running total
    long total_num_fish = 0;
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        int age_index = (int) puzzle_input->puzzle_items[i]->value;
        total_num_fish += num_fish[age_index];
    }
    
    //free and return running total
    free_puzzle_input(puzzle_input);
    return total_num_fish;
}