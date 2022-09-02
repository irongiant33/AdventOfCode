#include "../include/day3.h"

#define DEBUG_PRINT false
#define MAX_NUM_BITS 100

/**
 * @brief code to solve part 1 of Day 3 AoC
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

    //find number of bits on each line
    char end_char = '\n';
    puzzle_input_t * first_line = read_file(filename, NULL, 0, &end_char);
    int num_bits = first_line->num_items;
    free_puzzle_input(first_line);

    //read in file
    int num_delimiters = 1;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = '\n';
    delimiters[0] = &delimiter1;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, num_delimiters, NULL);

    // initialize array of ints to store bit counts
    int num_lines = puzzle_input->num_items;
    int * bit_count = calloc(num_bits, sizeof(int));
    for(int i = 0; i < num_bits; i++)
    {
        bit_count[i] = 0;
    }

    //count bits in each position
    for(int i = 0; i < num_lines; i++)
    {
        for(int j = 0; j < num_bits; j++)
        {
            switch(puzzle_input->puzzle_items[i]->char_val[j])
            {
                case '1':
                    bit_count[j] = bit_count[j] + 1;
                    break;
                case '0':
                    bit_count[j] = bit_count[j] - 1;
                    break;
                default:
                    fprintf(stderr, "unrecognized value\n");
                    break;
            }
        }
    }

    //find the gamma and epsilon rate
    long gamma_rate = 0;
    long epsilon_rate = 0;
    for(int i = 0; i < num_bits; i++)
    {
        long shift_amount = 1 << (num_bits - i - 1);

        if(DEBUG_PRINT)
        {
            printf("bit count in position %d = %d, shift amount = %ld\n", i, bit_count[i], shift_amount);
        }

        //more 1's than 0's
        if(bit_count[i] > 0)
        {
            gamma_rate = gamma_rate + shift_amount;
        }
        else
        {
            epsilon_rate = epsilon_rate + shift_amount;
        }
    }

    if(DEBUG_PRINT)
    {
        printf("num_bits: %d\n", num_bits);
        printf("epsilon: %ld\ngamma: %ld\n", gamma_rate, epsilon_rate);
    }

    //free and end
    free(delimiters);
    delimiters = NULL;
    free(bit_count);
    bit_count = NULL;
    free_puzzle_input(puzzle_input);
    return gamma_rate * epsilon_rate;
}

/**
 * @brief convert from unsigned binary string to long value
 * 
 * @param bin_str of format XXXXXX where X is 0 or 1.
 * @param num_bits number of bits in the binary string
 * @return long - value of binary string, or -1 if there is an error
 */
long
convert_from_bin_str(char * bin_str, int num_bits)
{
    if(NULL == bin_str)
    {
        fprintf(stderr, "bin_str cannot be NULL\n");
        return ERROR;
    }
    if(strnlen(bin_str, MAX_NUM_BITS) != (size_t) num_bits)
    {
        fprintf(stderr, "the specified number of bits is not equal to the actual number of bits\n");
    }

    long value = 0;
    for(int i = 0; i < num_bits; i++)
    {
        char high_bit = '1';
        if(0 == strncmp(&bin_str[i], &high_bit, 1))
        {
            value += 1 << (num_bits - i - 1);
        }
    }
    return value;
}

/**
 * @brief remove items from the list if they do not meet the bit criteria
 *        specified in the part 2 problem statement
 * 
 * @param puzzle_input - the puzzle input to add to the doubly ll
 * @param bit_frequency - int array containing a positive value if 1 is most
 *                        frequent and a negative value if 0 is most frequent.
 * @param num_bits - number of bits in each puzzle item
 * @param most_common - true if you want to find the most frequent value, false
 *                      to find least frequent.
 * @return puzzle_item_t * - pointer to the puzzle item that is associated with
 *                           the frequency selected value 
 */
puzzle_item_t *
frequency_selective_filter(puzzle_input_t * puzzle_input, int * bit_frequency, int num_bits, bool most_common)
{
    if(NULL == bit_frequency)
    {
        fprintf(stderr, "bit frequency cannot be NULL\n");
        return NULL;
    }
    if(NULL == puzzle_input)
    {
        fprintf(stderr, "puzzle input cannot be NULL\n");
        return NULL;
    }

    //add the puzzle input to a doubly linked list
    doubly_ll_t * list = doubly_ll_init(puzzle_input->num_items);
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        doubly_ll_add(list, (void *) puzzle_input->puzzle_items[i], NULL);
    }
    if(DEBUG_PRINT)
    {
        printf("doubly_ll_size=%d\n", list->num_items);
    }

    //remove items from the list that don't comply with the bit criteria
    int bit_position = 0;
    while(list->num_items > 1 && bit_position < num_bits)
    {
        int list_index = 0;
        if(DEBUG_PRINT)
        {
            printf("Checking bit position %d against value %d\n", bit_position, bit_frequency[bit_position]);
        }
        while(list_index < list->num_items)
        {
            doubly_ll_item_t * fetched_item = doubly_ll_fetch(list, list_index);
            puzzle_item_t * item = ((puzzle_item_t *) fetched_item->item);
            puzzle_item_t * removed = NULL;
            switch(item->char_val[bit_position])
            {
                case '1':
                    //1 was most common
                    if(most_common && 0 < bit_frequency[bit_position])
                    {
                        list_index += 1;
                    }
                    //1 was least common
                    else if(!most_common && 0 > bit_frequency[bit_position])
                    {
                        list_index += 1;
                    }
                    else
                    {
                        removed = (puzzle_item_t *) doubly_ll_remove(list, list_index);
                    }
                    break;
                case '0':
                    //0 was most common
                    if(most_common && 0 > bit_frequency[bit_position])
                    {
                        list_index += 1;
                    }
                    //0 was least common
                    else if(!most_common && 0 < bit_frequency[bit_position])
                    {
                        list_index += 1;
                    }
                    else
                    {
                        removed = doubly_ll_remove(list, list_index);
                    }
                    break;
                default:
                    fprintf(stderr, "unrecognized bit at %d in %s", bit_position, item->char_val);
                    break;
            }
            if(DEBUG_PRINT)
            {
                if(NULL != removed)
                {
                    printf("Removed %s\n", removed->char_val);
                }
            }
        }
        if(DEBUG_PRINT)
        {
            printf("%d values remain in list\n\n", list->num_items);
        }

        //increment bit position
        bit_position++;

        //re-evaluate bit frequencies
        for(int j = bit_position; j < num_bits; j++)
        {
            bit_frequency[j] = 0;
            for(int i = 0; i < list->num_items; i++)
            {
                doubly_ll_item_t * dll_item = doubly_ll_fetch(list, i);
                puzzle_item_t * item = (puzzle_item_t *) dll_item->item;

                switch (item->char_val[j])
                {
                case '1':
                    bit_frequency[j] += 1;
                    break;
                case '0':
                    bit_frequency[j] -= 1;
                    break;
                default:
                    fprintf(stderr, "unregonized value\n");
                    break;
                }
            }

            //ties concede to high bit
            if(0 == bit_frequency[j])
            {
                bit_frequency[j] += 1;
            }
        }
    }

    //check to make sure there is just 1 item left in the list
    if(list->num_items > 1)
    {
        fprintf(stderr, "there are more than 1 items that meet the criteria\n");
        return NULL;
    }

    //free the list and return the remaining item
    puzzle_item_t * last_item = (puzzle_item_t *) doubly_ll_remove(list, 0);
    if(DEBUG_PRINT)
    {
        printf("last item is %s\n", last_item->char_val);
    }
    doubly_ll_destroy(list);
    return last_item;
}

/**
 * @brief solves part 2 of day 3 AOC 2021
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

    //find number of bits on each line
    char end_char = '\n';
    puzzle_input_t * first_line = read_file(filename, NULL, 0, &end_char);
    int num_bits = first_line->num_items;
    free_puzzle_input(first_line);

    //read in file
    int num_delimiters = 1;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = '\n';
    delimiters[0] = &delimiter1;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, num_delimiters, NULL);

    // initialize array of ints to store bit counts
    int num_lines = puzzle_input->num_items;
    int * bit_count = calloc(num_bits, sizeof(int));
    for(int i = 0; i < num_bits; i++)
    {
        bit_count[i] = 0;
    }

    //count bits in each position
    for(int i = 0; i < num_lines; i++)
    {
        for(int j = 0; j < num_bits; j++)
        {
            switch(puzzle_input->puzzle_items[i]->char_val[j])
            {
                case '1':
                    bit_count[j] = bit_count[j] + 1;
                    break;
                case '0':
                    bit_count[j] = bit_count[j] - 1;
                    break;
                default:
                    fprintf(stderr, "unrecognized value\n");
                    break;
            }
        }
    }

    //find the oxygen and carbon rating
    long oxygen_rate = 0;
    long carbon_rate = 0;
    puzzle_item_t * oxygen_item = frequency_selective_filter(puzzle_input, bit_count, num_bits, true);
    puzzle_item_t * carbon_item = frequency_selective_filter(puzzle_input, bit_count, num_bits, false);
    oxygen_rate = convert_from_bin_str(oxygen_item->char_val, num_bits);
    carbon_rate = convert_from_bin_str(carbon_item->char_val, num_bits);
    

    if(DEBUG_PRINT)
    {
        printf("oxygen rate: %ld\ncarbon rate: %ld\n", oxygen_rate, carbon_rate);
    }

    //free and end
    free(delimiters);
    delimiters = NULL;
    free(bit_count);
    bit_count = NULL;
    free_puzzle_input(puzzle_input);
    return oxygen_rate * carbon_rate;
}