#include "common.h"

/**
 * @brief find the index of the next delimiter in the file
 * 
 * @param fp - file to find delimiter
 * @param delimiters - list of delimiter characters (NULL if no delimiters)
 * @param num_delimiters - number of delimiters
 * @param end_char - end character (NULL if EOF)
 * @return int 
 */
int find_next_delimiter(FILE * fp, char ** delimiters, int num_delimiters, char * end_char)
{
    //input checking
    if(NULL == fp)
    {
        fprintf(stderr, "file pointer cannot be null\n");
        return ERROR;
    }
    if(NULL == delimiters && 0 < num_delimiters)
    {
        fprintf(stderr, "delimiters cannot be null\n");
        return ERROR;
    }
    for(int i = 0; i < num_delimiters; i++)
    {
        if(NULL == delimiters[i])
        {
            fprintf(stderr, "index %d of delimiters is NULL\n", i);
            return ERROR;
        }
    }

    //find next delimiter
    int offset = 0;
    bool delimiter_found = false;
    int is_end_of_file = 0;
    int extra_offset = 0;
    while(!delimiter_found)
    {
        char char_in = fgetc(fp);
        is_end_of_file = feof(fp);
        if(NO_EOF < is_end_of_file)
        {
            delimiter_found = true;
        }
        else if(0 == num_delimiters)
        {
            offset += 1;
            delimiter_found = true;
        }
        else
        {
            //matches delimiter?
            for(int i = 0; i < num_delimiters; i++)
            {
                if(0 == strncmp(&char_in, delimiters[i], 1))
                {
                    delimiter_found = true;
                    extra_offset = 1;
                }
            }

            //matches end?
            if(NULL != end_char && 0 == strncmp(&char_in, end_char, 1))
            {
                delimiter_found = true;
                extra_offset = 1;
            }
        }

        //increment offset
        if(!delimiter_found)
        {
            offset += 1;
        }
    }

    //free and reset file pointer
    fseek(fp, -(offset + extra_offset), SEEK_CUR);
    return offset;
}

/**
 * @brief read puzzle input file
 * 
 * @param filename - name of file to read
 * @param delimiters - list of delimiter characters (NULL if no delimiters)
 * @param num_delimiters - number of delimiters
 * @param end_char - character to stop reading (NULL if EOF)
 * @return puzzle_input_t* - list of puzzle items that have been split according
 *                           to the delimiters
 */
puzzle_input_t * read_file(char * filename, char ** delimiters, int num_delimiters, char * end_char)
{
    //input checking
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be null\n");
        return NULL;
    }
    if(NULL == delimiters && 0 < num_delimiters)
    {
        fprintf(stderr, "delimiters cannot be null\n");
        return NULL;
    }
    for(int i = 0; i < num_delimiters; i++)
    {
        if(NULL == delimiters[i])
        {
            fprintf(stderr, "index %d of delimiters is NULL\n", i);
            return NULL;
        }
    }

    //open the file to read
    FILE * fp;
    fp = fopen(filename, "r");
    if(NULL == fp)
    {
        fprintf(stderr, "Cannot open file %s\n", filename);
        return NULL;
    }

    //read the file
    bool stop_reading = false;
    puzzle_input_t * puzzle_input = calloc(1, sizeof(puzzle_input_t));
    puzzle_input->puzzle_items = calloc(DEFAULT_NUM_PUZZLE_ITEMS, sizeof(puzzle_item_t *));
    int puzzle_item_index = 0;
    int num_puzzle_items = DEFAULT_NUM_PUZZLE_ITEMS;
    while(!stop_reading)
    {
        //find index of next delimiter
        int delimiter_offset = find_next_delimiter(fp, delimiters, num_delimiters, end_char);
        if(ERROR == delimiter_offset)
        {
            fprintf(stderr, "error finding next delimiter\n");
            return NULL;
        }

        //store contents between stop point and delimiter in puzzle item
        puzzle_item_t * puzzle_item = calloc(1, sizeof(puzzle_item_t));
        puzzle_item->char_val = calloc(delimiter_offset + 1, sizeof(char)); //extra 1 for null byte
        for(int i = 0; i < delimiter_offset; i++)
        {
            *(puzzle_item->char_val + i) = fgetc(fp);
        }

        //add puzzle item to puzzle input. Realloc if necessary.
        if(num_puzzle_items == puzzle_item_index)
        {
            num_puzzle_items = puzzle_item_index + DEFAULT_NUM_PUZZLE_ITEMS;
            puzzle_input->puzzle_items = realloc(puzzle_input->puzzle_items, num_puzzle_items);
        }
        puzzle_input->puzzle_items[puzzle_item_index] = puzzle_item;
        puzzle_item_index += 1;

        //read in the delimiter to check if its the end
        char delimiter = fgetc(fp);
        int is_end_of_file = feof(fp);
        bool is_match_end_char = (NULL != end_char && 0 == strncmp(end_char, &delimiter, 1));
        if(NO_EOF < is_end_of_file || is_match_end_char)
        {
            stop_reading = true;
        }
        else if(0 == num_delimiters)
        {
            fseek(fp, -1, SEEK_CUR);
        }
    }
    puzzle_input->num_items = puzzle_item_index;

    //close the file and return
    fclose(fp);
    return puzzle_input;
}

/**
 * @brief frees memory allocated to puzzle_input struct
 * 
 * @param puzzle_input 
 */
void
free_puzzle_input(puzzle_input_t * puzzle_input)
{
    if(NULL == puzzle_input)
    {
        return;
    }
    if(NULL == puzzle_input->puzzle_items)
    {
        goto FREE_AND_DESTROY;
    }

    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        if(NULL != puzzle_input->puzzle_items[i])
        {
            if(NULL != puzzle_input->puzzle_items[i]->char_val)
            {
                free(puzzle_input->puzzle_items[i]->char_val);
                puzzle_input->puzzle_items[i]->char_val = NULL;
            }

            free(puzzle_input->puzzle_items[i]);
            puzzle_input->puzzle_items[i] = NULL;
        }
    }
    free(puzzle_input->puzzle_items);
    puzzle_input->puzzle_items = NULL;

    FREE_AND_DESTROY:
    free(puzzle_input);
    puzzle_input = NULL;
    return;
}

/**
 * @brief converts a puzzle item's char_val to long
 * 
 * @param puzzle_item - puzzle item to convert
 * @return int - success code
 */
int
convert_item_to_long(puzzle_item_t * puzzle_item)
{
    if(NULL == puzzle_item->char_val)
    {
        fprintf(stderr, "cannot convert puzzle item with NULL char val\n");
        return ERROR;
    }

    char * end_ptr;
    puzzle_item->value = strtol(puzzle_item->char_val, &end_ptr, BASE);
    if (errno != 0) {
        perror("strtol");
        return ERROR;
    }

    if (end_ptr == puzzle_item->char_val) {
        fprintf(stderr, "No digits were found\n");
        return ERROR;
    }

    return SUCCESS;
}

/**
 * @brief converts the entirety of the puzzle input to long
 * 
 * @param puzzle_input - puzzle input to convert
 * @return int - success code
 */
int
convert_input_to_long(puzzle_input_t * puzzle_input)
{
    if(NULL == puzzle_input)
    {
        fprintf(stderr, "cannot convert NULL input to long\n");
        return ERROR;
    }

    //convert input to long
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        int ret_val = convert_item_to_long(puzzle_input->puzzle_items[i]);
        if(ERROR == ret_val)
        {
            fprintf(stderr, "error converting item %d into long\n", i);
            return ERROR;
        }
    }
    return SUCCESS;
}

/**
 * @brief filters the puzzle input by removing certain indices. Frees the puzzle
 *        input that you give it in lieu of the input it returns
 * 
 * @param puzzle_input - puzzle input to filter
 * @param start_index - starting index of filter
 * @param increment - value to increment to get to the next bad value
 * @return puzzle_input_t * - pointer to new puzzle input
 */
puzzle_input_t *
filter_by_index(puzzle_input_t * puzzle_input, int start_index, int increment)
{
    if(NULL == puzzle_input)
    {
        fprintf(stderr, "cannot filter NULL puzzle input\n");
        return NULL;
    }
    if(start_index > puzzle_input->num_items)
    {
        fprintf(stderr, "start index is out of filter range\n");
        return NULL;
    }

    puzzle_input_t * new_puzzle_input = calloc(1, sizeof(puzzle_input_t));
    new_puzzle_input->num_items = puzzle_input->num_items;
    new_puzzle_input->puzzle_items = calloc(new_puzzle_input->num_items, sizeof(puzzle_item_t *));

    int new_puzzle_index = 0;
    int bad_index = start_index;
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        //add to new puzzle if you're at a good index
        if(i != bad_index)
        {
            puzzle_item_t * puzzle_item = calloc(1, sizeof(puzzle_item_t));

            size_t new_length = strnlen(puzzle_input->puzzle_items[i]->char_val, MAX_STRN_LEN);
            puzzle_item->char_val = calloc(new_length + 1, sizeof(char));
            strncpy(puzzle_item->char_val, puzzle_input->puzzle_items[i]->char_val, new_length);
            puzzle_item->value = puzzle_input->puzzle_items[i]->value;
    
            new_puzzle_input->puzzle_items[new_puzzle_index] = puzzle_item;
            new_puzzle_index++;
        }
        else
        {
            new_puzzle_input->num_items--;
            bad_index += increment;
        }
    }

    //free and return
    free_puzzle_input(puzzle_input);
    return new_puzzle_input;
}

/**
 * @brief filter the puzzle input by removing every instance of the specified value
 * 
 * @param puzzle_input 
 * @param value 
 * @return puzzle_input_t* 
 */
puzzle_input_t *
filter_by_value(puzzle_input_t * puzzle_input, char value)
{
    if(NULL == puzzle_input)
    {
        fprintf(stderr, "cannot filter NULL puzzle input\n");
        return NULL;
    }

    puzzle_input_t * new_puzzle_input = calloc(1, sizeof(puzzle_input_t));
    new_puzzle_input->num_items = puzzle_input->num_items;
    new_puzzle_input->puzzle_items = calloc(new_puzzle_input->num_items, sizeof(puzzle_item_t *));

    int new_puzzle_index = 0;
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        //add to new puzzle if you're at a good index
        if(*puzzle_input->puzzle_items[i]->char_val != value)
        {
            puzzle_item_t * puzzle_item = calloc(1, sizeof(puzzle_item_t));

            size_t new_length = strnlen(puzzle_input->puzzle_items[i]->char_val, MAX_STRN_LEN);
            puzzle_item->char_val = calloc(new_length + 1, sizeof(char));
            strncpy(puzzle_item->char_val, puzzle_input->puzzle_items[i]->char_val, new_length);
            puzzle_item->value = puzzle_input->puzzle_items[i]->value;
    
            new_puzzle_input->puzzle_items[new_puzzle_index] = puzzle_item;
            new_puzzle_index++;
        }
        else
        {
            new_puzzle_input->num_items--;
        }
    }

    //free and return
    free_puzzle_input(puzzle_input);
    return new_puzzle_input;
}

/**
 * @brief filters the puzzle input by checking the length of each puzzle item's
 *        char_val. Frees the puzzle input that you give it in lieu of the input
 *        it returns
 * 
 * @param puzzle_input - puzzle input to filter
 * @param length - length to remove
 * @return puzzle_input_t * - pointer to new puzzle input
 */
puzzle_input_t *
filter_by_length(puzzle_input_t * puzzle_input, int length)
{
    if(NULL == puzzle_input)
    {
        fprintf(stderr, "cannot filter NULL puzzle input\n");
        return NULL;
    }
    if(0 > length)
    {
        fprintf(stderr, "length cannot be negative\n");
        return NULL;
    }

    size_t bad_len = (size_t) length;
    puzzle_input_t * new_puzzle_input = calloc(1, sizeof(puzzle_input_t));
    new_puzzle_input->num_items = puzzle_input->num_items;
    new_puzzle_input->puzzle_items = calloc(new_puzzle_input->num_items, sizeof(puzzle_item_t *));

    int new_puzzle_index = 0;
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        size_t item_len = strnlen(puzzle_input->puzzle_items[i]->char_val, MAX_STRN_LEN);

        //add to new puzzle if the length is not equal to bad length
        if(item_len != bad_len)
        {
            puzzle_item_t * puzzle_item = calloc(1, sizeof(puzzle_item_t));
            
            puzzle_item->char_val = calloc(item_len + 1, sizeof(char));
            strncpy(puzzle_item->char_val, puzzle_input->puzzle_items[i]->char_val, item_len);
            puzzle_item->value = puzzle_input->puzzle_items[i]->value;
    
            new_puzzle_input->puzzle_items[new_puzzle_index] = puzzle_item;
            new_puzzle_index++;
        }
        else
        {
            new_puzzle_input->num_items--;
        }
    }

    //free and return
    free_puzzle_input(puzzle_input);
    return new_puzzle_input;
}