#include "../include/day14.h"

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
    char delimiter1 = ' ';
    char delimiter2 = '\n';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;

    char end_char = 'f';
    puzzle_input_t * dirty_puzzle_input = read_file(filename, delimiters, num_delimiters, &end_char);
    puzzle_input_t * dirt_puzzle_input = filter_by_length(dirty_puzzle_input, 0);
    puzzle_input_t * puzzle_input = filter_by_index(dirt_puzzle_input, 2, 3);

    free(delimiters);
    delimiters = NULL;
    return puzzle_input;
}

int
convert_to_key(char * val1, char * val2)
{
    int value1 = (*val1 - 'A') * 26;
    int value2 = (*val2 - 'A');
    return value1 + value2;
}

/**
 * @brief converts from a key to a compound character
 * 
 * @param key 
 * @return int 
 */
char *
convert_from_key(int key)
{
    int remainder = key / 26;
    char first = 'A' + remainder;
    int leftover = (key - remainder * 26);
    char second = 'A' + leftover;
    char * compound = calloc(2, sizeof(char));
    compound[0] = first;
    compound[1] = second;
    return compound;
}

/**
 * @brief code to solve part 1 of Day 14 AoC
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
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //create hash map and letter frequencies
    char * compound_dict = calloc(26 * 26, sizeof(char));
    int * letter_freqs = calloc(26, sizeof(int));

    //fill out hash map
    for(int i = 1; i < puzzle_input->num_items; i+=2)
    {
        char * compound = puzzle_input->puzzle_items[i]->char_val;
        int compound_value = convert_to_key(&compound[0], &compound[1]);
        compound_dict[compound_value] = puzzle_input->puzzle_items[i + 1]->char_val[0];
    }

    //initialize letter frequencies and compound
    int prev_len = strnlen(puzzle_input->puzzle_items[0]->char_val, MAX_STRN_LEN);
    char * prev_compound = calloc(prev_len + 1, sizeof(char));
    for(int i = 0; i < prev_len; i++)
    {
        int key = puzzle_input->puzzle_items[0]->char_val[i] - 'A';
        letter_freqs[key] += 1;
        strncpy(prev_compound, puzzle_input->puzzle_items[0]->char_val, prev_len + 1);
    }

    //debug print
    if(DEBUG_PRINT)
    {
        printf("%s\n", prev_compound);
    }

    //perform insertions
    for(int i = 0; i < num_steps; i++)
    {
        if(DEBUG_PRINT)
        {
            printf("step %d:\n%s\n\n", i, prev_compound);
        }
        char * next_compound = calloc(2 * prev_len, sizeof(char));
        int index = 0;
        for(int j = 0; j < (prev_len - 1); j++)
        {
            int value = convert_to_key(&prev_compound[j], &prev_compound[j + 1]);
            char next_item = compound_dict[value];
            int key = next_item - 'A';
            letter_freqs[key] += 1;
            strncpy(&next_compound[index], &prev_compound[j], 1);
            strncpy(&next_compound[index + 1], &next_item, 1);
            index += 2;
        }
        strncpy(&next_compound[index], &prev_compound[prev_len - 1], 1);
        free(prev_compound);
        prev_compound = calloc(2 * prev_len, sizeof(char));
        strncpy(prev_compound, next_compound, 2 * prev_len);
        free(next_compound);
        prev_len = 2 * prev_len - 1;
    }

    //find min and max of letter freqs
    int min_val = INT32_MAX;
    int max_val = -1;
    for(int i = 0; i < 26; i++)
    {
        if(letter_freqs[i] != 0 && letter_freqs[i] < min_val)
        {
            min_val = letter_freqs[i];
        }
        if(letter_freqs[i] > max_val)
        {
            max_val = letter_freqs[i];
        }
    }
    int result = max_val - min_val;

    //free and return
    free_puzzle_input(puzzle_input);
    free(compound_dict);
    free(letter_freqs);
    free(prev_compound);
    return result;
}

/**
 * @brief solves part 2 of day 14 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return uint64_t - answer to part 2
 */
uint64_t
part2(char * filename, int num_steps)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //create hash map and letter frequencies
    int num_compounds = 26 * 26;
    compound_t ** compound_dict = calloc(num_compounds, sizeof(compound_t *));
    uint64_t * letter_freqs = calloc(26, sizeof(uint64_t));

    //do we need to zeroize compound dict?
    for(int i = 0; i < num_compounds; i++)
    {
        compound_dict[i] = calloc(1, sizeof(compound_t));
        compound_dict[i]->curr_freq = 0;
        compound_dict[i]->next_freq = 0;
        compound_dict[i]->element_ids[0] = 0;
        compound_dict[i]->element_ids[1] = 0;
        compound_dict[i]->element_ids[2] = 0;
    }

    //zeroize letter frequencies?
    for(int i = 0; i < 26; i++)
    {
        letter_freqs[i] = 0;
    }

    //initialize compound dict
    for(int i = 1; i < puzzle_input->num_items; i+=2)
    {
        char * compound = puzzle_input->puzzle_items[i]->char_val;
        char * element = puzzle_input->puzzle_items[i + 1]->char_val;
        int element_value = *element - 'A';
    
        int compound_id = convert_to_key(&compound[0], &compound[1]);
        int compound1 = convert_to_key(&compound[0], element);
        int compound2 = convert_to_key(element, &compound[1]);

        if(DEBUG_PRINT)
        {
            char * compound = convert_from_key(compound_id);
            printf("initial compound dict %s\n", compound);
            free(compound);
            compound = NULL;
        }

        compound_dict[compound_id]->element_ids[0] = element_value;
        compound_dict[compound_id]->element_ids[1] = compound1;
        compound_dict[compound_id]->element_ids[2] = compound2;
    }

    //initialize letter frequencies
    int initial_len = (int) strnlen(puzzle_input->puzzle_items[0]->char_val, MAX_STRN_LEN);
    for(int i = 0; i < initial_len; i++)
    {
        int key = puzzle_input->puzzle_items[0]->char_val[i] - 'A';
        letter_freqs[key] += 1;
        if(i != 0)
        {
            int key = convert_to_key(&puzzle_input->puzzle_items[0]->char_val[i - 1], &puzzle_input->puzzle_items[0]->char_val[i]);
            compound_dict[key]->next_freq += 1;
        }
    }

    //perform insertions
    for(int i = 0; i < num_steps; i++)
    {
        if(DEBUG_PRINT)
        {
            printf("step %d\n", i);
        }

        for(int j = 0; j < num_compounds; j++)
        {
            compound_dict[j]->curr_freq = compound_dict[j]->next_freq;
            compound_dict[j]->next_freq = 0;
        }

        for(int j = 0; j < num_compounds; j++)
        {
            letter_freqs[compound_dict[j]->element_ids[0]] += compound_dict[j]->curr_freq;
            compound_dict[compound_dict[j]->element_ids[1]]->next_freq += compound_dict[j]->curr_freq;
            compound_dict[compound_dict[j]->element_ids[2]]->next_freq += compound_dict[j]->curr_freq;
        }
    }

    //find min and max of letter freqs
    uint64_t min_val = UINT64_MAX;
    uint64_t max_val = 0;
    for(int i = 0; i < 26; i++)
    {
        if(letter_freqs[i] != 0 && letter_freqs[i] < min_val)
        {
            min_val = letter_freqs[i];
        }
        if(letter_freqs[i] > max_val)
        {
            max_val = letter_freqs[i];
        }
    }
    uint64_t result = max_val - min_val;

    //free and return
    free_puzzle_input(puzzle_input);
    for(int i = 0; i < num_compounds; i++)
    {
        free(compound_dict[i]);
        compound_dict[i] = NULL;
    }
    free(compound_dict);
    free(letter_freqs);
    return result;
}