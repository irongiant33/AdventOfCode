#include "../include/day10.h"

#define DEBUG_PRINT false

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
    puzzle_input_t * puzzle_input = read_file(filename, NULL, num_delimiters, NULL);

    return puzzle_input;
}

/**
 * @brief determine if there is a syntax error on the line input. Syntax error
 *        is where an ending character `)`, `}`, `]`, or `>` is not matched to
 *        its respective opening character.
 * 
 * @param line_input 
 * @return int - value corresponding to the magnitude of the error
 * ) = 3
 * ] = 57
 * } = 1197
 * > = 25137
 */
int
parse_line(doubly_ll_t * line_input)
{
    if(NULL == line_input)
    {
        fprintf(stderr, "cannot parse null input line\n");
        return ERROR;
    }

    int line_index = 0;
    int error_val = 0;
    bool is_error = false;
    while(!is_error && line_index < line_input->num_items)
    {
        //fetch the current item
        doubly_ll_item_t * item = doubly_ll_fetch(line_input, line_index);
        char * value = (char *) item->item;

        //check to see if the item is an end character
        char valid_prev_val = 0;
        switch (value[0])
        {
        case ')':
            valid_prev_val = '(';
            break;
        case '}':
            valid_prev_val = '{';
            break;
        case ']':
            valid_prev_val = '[';
            break;
        case '>':
            valid_prev_val = '<';
            break;
        default:
            valid_prev_val = 0;
            break;
        }

        //if the item was an end character, determine if it matches the previous item
        if(0 != valid_prev_val && 0 < line_index)
        {
            line_index--;
            doubly_ll_item_t * prev_item = doubly_ll_fetch(line_input, line_index);
            char * prev_val = (void *) prev_item->item;
            if(0 != strncmp(prev_val, &valid_prev_val, 1))
            {
                is_error = true;
            }
        }
        else if (0 != valid_prev_val && 0 >= line_index)
        {
            is_error = true;
        }

        //if there was an error, assign the error value.
        if(is_error)
        {
            switch (value[0])
            {
            case ')':
                error_val = 3;
                break;
            case ']':
                error_val = 57;
                break;
            case '}':
                error_val = 1197;
                break;
            case '>':
                error_val = 25137;
                break;
            default:
                fprintf(stderr, "unrecognized character\n");
                error_val = ERROR;
                break;
            }
        }
        //if there was not an error, but there was a match, remove the current index as well as the next index
        else if(!is_error && 0 != valid_prev_val)
        {
            doubly_ll_remove(line_input, line_index);
            doubly_ll_remove(line_input, line_index);
        }
        //if there was not an error and no match, increment the line index in all cases
        else
        {
            line_index++;
        }
    }

    return error_val;
}

/**
 * @brief code to solve part 1 of Day 10 AoC
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
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //loop through every puzzle input
    int running_sum = 0;
    int line_count = 0;
    doubly_ll_t * line_input = doubly_ll_init(puzzle_input->num_items);
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        char end_char = '\n';
        int linebreak_cmp = strncmp(puzzle_input->puzzle_items[i]->char_val, &end_char, 1);

        //if newline or the last puzzle input, parse the line
        if(0 == linebreak_cmp || i == puzzle_input->num_items - 1)
        {
            //calculate error value and add to running sum
            line_count++;
            int error_val = parse_line(line_input);
            running_sum += error_val;

            //clear the LL and create a blank one for next line
            doubly_ll_destroy(line_input);
            line_input = doubly_ll_init(puzzle_input->num_items);
        }
        else
        {
            doubly_ll_add(line_input, (void *) puzzle_input->puzzle_items[i]->char_val, NULL);
        }
    }

    doubly_ll_destroy(line_input);
    free_puzzle_input(puzzle_input);
    return running_sum;
}

/**
 * @brief calculate the score of the remaining characters in incomplete lines
 * start with 0 score, then for each character, multiply score by 5 and add value
 * associated with character: ) = 1, ] = 2, } = 3, > = 4.
 * 
 * @param line_input 
 * @return int 
 */
long
calc_line_score(doubly_ll_t * line_input)
{
    if(NULL == line_input)
    {
        fprintf(stderr, "cannot score NULL line\n");
        return ERROR;
    }

    long score = 0;
    for(int i = (line_input->num_items - 1); i >= 0; i--)
    {
        doubly_ll_item_t * item = line_input->head;
        if(i > 0)
        {
            item = doubly_ll_fetch(line_input, i);
        }
        char * value = (char *) item->item;
        long add_amount = 0;
        switch (value[0])
        {
        case '(':
            add_amount = 1;
            break;
        case '[':
            add_amount = 2;
            break;
        case '{':
            add_amount = 3;
            break;
        case '<':
            add_amount = 4;
            break;
        default:
            add_amount = 0;
            break;
        }
        score *= 5;
        score += add_amount;
    }
    return score;
}

/**
 * @brief implement comparison function to allow sorting of line scores
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
        fprintf(stderr, "cannot compare items if one of them is NULL\n");
        return ERROR;
    }

    long * val_a = (long *) item_a->item;
    long * val_b = (long *) item_b->item;
    if(*val_a < *val_b)
    {
        return -1;
    }
    else if (*val_a == *val_b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
 * @brief solves part 2 of day 10 AOC 2021
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

    //find # of inputs on one line, then get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //loop through every puzzle input
    int running_sum = 0;
    int line_count = 0;
    doubly_ll_t * line_input = doubly_ll_init(puzzle_input->num_items);
    doubly_ll_t * line_scores = doubly_ll_init(puzzle_input->num_items);
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        char end_char = '\n';
        int linebreak_cmp = strncmp(puzzle_input->puzzle_items[i]->char_val, &end_char, 1);

        //if newline or the last puzzle input, parse the line
        if(0 == linebreak_cmp || i == puzzle_input->num_items - 1)
        {
            //calculate error value and add to running sum
            line_count++;
            int error_val = parse_line(line_input);
            running_sum += error_val;

            if(0 == error_val)
            {
                long * line_score = calloc(1, sizeof(long));
                *line_score = calc_line_score(line_input);
                doubly_ll_add(line_scores, (void *)line_score, NULL);
            }

            //clear the LL and create a blank one for next line
            doubly_ll_destroy(line_input);
            line_input = doubly_ll_init(puzzle_input->num_items);
        }
        else
        {
            doubly_ll_add(line_input, (void *) puzzle_input->puzzle_items[i]->char_val, NULL);
        }
    }

    //sort line scores and assign middle score
    long middle_score = 0;
    doubly_ll_sort(line_scores, compare, 0, line_scores->num_items - 1);
    doubly_ll_item_t * middle_item = doubly_ll_fetch(line_scores, (line_scores->num_items - 1) / 2);
    middle_score = *(long *) middle_item->item;

    doubly_ll_destroy(line_input);
    while(0 < line_scores->num_items)
    {
        long * item = (long *) doubly_ll_remove(line_scores, 0);
        free(item);
        item = NULL;
    }
    doubly_ll_destroy(line_scores);
    free_puzzle_input(puzzle_input);
    return middle_score;
}