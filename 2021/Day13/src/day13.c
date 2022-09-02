#include "../include/day13.h"

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
    char delimiter1 = ',';
    char delimiter2 = '\n';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;

    char end_char = 'f';
    puzzle_input_t * dirty_puzzle_input = read_file(filename, delimiters, num_delimiters, &end_char);
    puzzle_input_t * puzzle_input = filter_by_length(dirty_puzzle_input, 0);
    convert_input_to_long(puzzle_input);

    free(delimiters);
    delimiters = NULL;
    return puzzle_input;
}

/**
 * @brief retrieve the puzzle input that is the fold instructions
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_fold_input(char * filename)
{
    int num_delimiters = 3;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = '=';
    char delimiter2 = '\n';
    char delimiter3 = ',';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    delimiters[2] = &delimiter3;

    puzzle_input_t * dirty_puzzle_input = read_file(filename, delimiters, num_delimiters, NULL);
    puzzle_input_t * puzzle_input = filter_by_length(dirty_puzzle_input, 0);

    free(delimiters);
    delimiters = NULL;
    return puzzle_input;
}

/**
 * @brief code to solve part 1 of Day 13 AoC
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

    //get the coordinates of the dot inputs
    puzzle_input_t * dot_inputs = get_puzzle_input(filename);

    //find max X
    int xlim = -1;
    for(int i = 0; i < dot_inputs->num_items; i+=2)
    {
        if((int) dot_inputs->puzzle_items[i]->value > xlim)
        {
            xlim = (int) dot_inputs->puzzle_items[i]->value;
        }
    }
    xlim += 1;

    //find max Y
    int ylim = -1;
    for(int i = 1; i < dot_inputs->num_items; i+=2)
    {
        if((int) dot_inputs->puzzle_items[i]->value > ylim)
        {
            ylim = (int) dot_inputs->puzzle_items[i]->value;
        }
    }
    ylim += 1;

    //create matrix
    int num_rows = ylim;
    int ** dot_matrix = calloc(ylim, sizeof(int *));
    for(int i = 0; i < ylim; i++)
    {
        dot_matrix[i] = calloc(xlim, sizeof(int));
        for(int j = 0; j < xlim; j++)
        {
            dot_matrix[i][j] = 0;
        }
    }

    //add puzzle input to matrix
    for(int i = 0; i < dot_inputs->num_items; i+=2)
    {
        int col = (int) dot_inputs->puzzle_items[i]->value;
        int row = (int) dot_inputs->puzzle_items[i + 1]->value;
        dot_matrix[row][col] += 1;
    }

    //debug print
    if(DEBUG_PRINT)
    {
        for(int i = 0; i < ylim; i++)
        {
            for(int j = 0; j < xlim; j++)
            {
                printf("%d ", dot_matrix[i][j]);
            }
            printf("\n");
        }
        printf("xlim: %d\nylim: %d\n", xlim, ylim);
    }

    //get fold instructions
    puzzle_input_t * fold_instructions = get_fold_input(filename);

    //debug print
    if(DEBUG_PRINT)
    {
        for(int i = dot_inputs->num_items; i < fold_instructions->num_items; i+=2)
        {
            printf("%s = %s\n", fold_instructions->puzzle_items[i]->char_val, fold_instructions->puzzle_items[i + 1]->char_val);
        }
    }

    //conduct the folds
    int num_folds = 1;
    char x_dir[13] = "fold along x";
    for(int i = 0; i < num_folds; i+=2)
    {
        char * instruction = fold_instructions->puzzle_items[dot_inputs->num_items + i]->char_val;
        int xfold = strncmp(instruction, x_dir, 13);
        
        convert_item_to_long(fold_instructions->puzzle_items[dot_inputs->num_items + i + 1]);
        int value = (int) fold_instructions->puzzle_items[dot_inputs->num_items + i + 1]->value;

        //in case of x fold
        if(0 == xfold)
        {
            //determine which fold side has fewer values, the lower or upper side
            int upper = xlim - value;
            int limit = value;
            if(upper < value)
            {
                limit = upper;
            }

            //add the folded values
            for(int k = 0; k < ylim; k++)
            {
                for(int j = 1; j <= limit; j++)
                {
                    dot_matrix[k][value - j] += dot_matrix[k][value + j];
                }
            }
            xlim = value;
        }
        //it is a y fold
        else
        {
            //determine which fold side has fewer values, the lower or upper side
            int upper = ylim - value;
            int limit = value;
            if(upper < value)
            {
                limit = upper;
            }

            //add the folded values
            for(int k = 0; k < xlim; k++)
            {
                for(int j = 1; j <= limit; j++)
                {
                    dot_matrix[value - j][k] += dot_matrix[value + j][k];
                }
            }
            ylim = value;
        }

        //debug print between folds
        if(DEBUG_PRINT)
        {
            for(int j = 0; j < ylim; j++)
            {
                for(int k = 0; k < xlim; k++)
                {
                    printf("%d ", dot_matrix[j][k]);
                }
                printf("\n");
            }
            printf("xlim: %d\nylim: %d\n\n", xlim, ylim);
        }
    }

    //count the folds between the limits
    int num_dots = 0;
    for(int i = 0; i < xlim; i++)
    {
        for(int j = 0; j < ylim; j++)
        {
            if(0 < dot_matrix[j][i])
            {
                num_dots++;
            }
        }
    }

    //free and return
    for(int i = 0; i < num_rows; i++)
    {
        free(dot_matrix[i]);
        dot_matrix[i] = NULL;
    }
    free(dot_matrix);
    free_puzzle_input(dot_inputs);
    free_puzzle_input(fold_instructions);
    return num_dots;
}

/**
 * @brief prints the dot matrix in character form
 * 
 * @param dot_matrix 
 * @param xlim 
 * @param ylim 
 */
void
print_dots(int ** dot_matrix, int xlim, int ylim)
{
    for(int j = 0; j < ylim; j++)
    {
        for(int k = 0; k < xlim; k++)
        {
            char print_char = ' ';
            if(0 < dot_matrix[j][k])
            {
                print_char = '#';
            }
            printf("%c", print_char);
        }
        printf("\n");
    }
    printf("xlim: %d\nylim: %d\n\n", xlim, ylim);
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

    //get the coordinates of the dot inputs
    puzzle_input_t * dot_inputs = get_puzzle_input(filename);

    //find max X
    int xlim = -1;
    for(int i = 0; i < dot_inputs->num_items; i+=2)
    {
        if((int) dot_inputs->puzzle_items[i]->value > xlim)
        {
            xlim = (int) dot_inputs->puzzle_items[i]->value;
        }
    }
    xlim += 1;

    //find max Y
    int ylim = -1;
    for(int i = 1; i < dot_inputs->num_items; i+=2)
    {
        if((int) dot_inputs->puzzle_items[i]->value > ylim)
        {
            ylim = (int) dot_inputs->puzzle_items[i]->value;
        }
    }
    ylim += 1;

    //create matrix
    int num_rows = ylim;
    int ** dot_matrix = calloc(ylim, sizeof(int *));
    for(int i = 0; i < ylim; i++)
    {
        dot_matrix[i] = calloc(xlim, sizeof(int));
        for(int j = 0; j < xlim; j++)
        {
            dot_matrix[i][j] = 0;
        }
    }

    //add puzzle input to matrix
    for(int i = 0; i < dot_inputs->num_items; i+=2)
    {
        int col = (int) dot_inputs->puzzle_items[i]->value;
        int row = (int) dot_inputs->puzzle_items[i + 1]->value;
        dot_matrix[row][col] += 1;
    }

    //debug print
    if(DEBUG_PRINT)
    {
        for(int i = 0; i < ylim; i++)
        {
            for(int j = 0; j < xlim; j++)
            {
                char print_char = '.';
                if(0 < dot_matrix[i][j])
                {
                    print_char = '#';
                }
                printf("%c", print_char);
            }
            printf("\n");
        }
        printf("xlim: %d\nylim: %d\n", xlim, ylim);
    }

    //get fold instructions
    puzzle_input_t * fold_instructions = get_fold_input(filename);

    //debug print
    if(DEBUG_PRINT)
    {
        for(int i = dot_inputs->num_items; i < fold_instructions->num_items; i+=2)
        {
            printf("%s = %s\n", fold_instructions->puzzle_items[i]->char_val, fold_instructions->puzzle_items[i + 1]->char_val);
        }
    }

    //conduct the folds
    int num_folds = fold_instructions->num_items - dot_inputs->num_items;
    char x_dir[13] = "fold along x";
    for(int i = 0; i < num_folds; i+=2)
    {
        char * instruction = fold_instructions->puzzle_items[dot_inputs->num_items + i]->char_val;
        int xfold = strncmp(instruction, x_dir, 13);
        
        convert_item_to_long(fold_instructions->puzzle_items[dot_inputs->num_items + i + 1]);
        int value = (int) fold_instructions->puzzle_items[dot_inputs->num_items + i + 1]->value;

        //in case of x fold
        if(0 == xfold)
        {
            if((xlim - 1)/2 != value)
            {
                printf("xlim %d value %d", xlim, value);
            }
            //determine which fold side has fewer values, the lower or upper side
            int upper = xlim - value;
            int limit = value + 1;
            if(upper < value)
            {
                limit = upper;
            }

            //add the folded values
            for(int k = 0; k < ylim; k++)
            {
                for(int j = 1; j < limit; j++)
                {
                    dot_matrix[k][value - j] += dot_matrix[k][value + j];
                }
            }
            xlim = value;
        }
        //it is a y fold
        else
        {
            if((ylim - 1)/2 != value)
            {
                printf("ylim %d value %d\n", ylim, value);
            }
            //determine which fold side has fewer values, the lower or upper side
            int upper = ylim - value;
            int limit = value + 1;
            if(upper < value)
            {
                limit = upper;
            }

            //add the folded values
            for(int k = 0; k < xlim; k++)
            {
                for(int j = 1; j < limit; j++)
                {
                    dot_matrix[value - j][k] += dot_matrix[value + j][k];
                }
            }
            ylim = value;
        }

        //debug print between folds
        if(DEBUG_PRINT)
        {
            print_dots(dot_matrix, xlim, ylim);
        }
    }

    print_dots(dot_matrix, xlim, ylim);

    //count the folds between the limits
    int num_dots = 0;
    for(int i = 0; i < xlim; i++)
    {
        for(int j = 0; j < ylim; j++)
        {
            if(0 < dot_matrix[j][i])
            {
                num_dots++;
            }
        }
    }

    //free and return
    for(int i = 0; i < num_rows; i++)
    {
        free(dot_matrix[i]);
        dot_matrix[i] = NULL;
    }
    free(dot_matrix);
    free_puzzle_input(dot_inputs);
    free_puzzle_input(fold_instructions);
    return 0;
}