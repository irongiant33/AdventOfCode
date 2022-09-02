#include "../include/day4.h"

/**
 * @brief Calculate the hash for a key
 *
 * @param key The key to hash
 */
int
hash_key(int key)
{
    return key % HASH_KEY_SIZE;
}

/**
 * @brief read in the called out numbers. sets the value property by converting
 *        from char to long
 * 
 * @param filename 
 * @return puzzle_input_t* 
 */
puzzle_input_t *
read_called_out(char * filename)
{
    //read in called out numbers
    int num_delimiters = 1;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = ',';
    delimiters[0] = &delimiter1;
    char end_char = '\n';
    puzzle_input_t * called_out = read_file(filename, delimiters, num_delimiters, &end_char);

    //convert input to long
    convert_input_to_long(called_out);

    free(delimiters);
    delimiters = NULL;
    return called_out;
}

/**
 * @brief read in the board inputs and remove the callouts and all values that are empty.
 *        sets the value property of the puzzle items by converting the input to long.
 * 
 * @param filename 
 * @return puzzle_input_t* 
 */
puzzle_input_t *
read_board_inputs(char * filename)
{
    //read in bingo boards
    int num_delimiters = 2;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = ' ';
    char delimiter2 = '\n';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    puzzle_input_t * dirty_boards = read_file(filename, delimiters, num_delimiters, NULL);

    //clean up dirty boards by removing all puzzle items with 0 char_val length
    //exclude 0th index of dirty_boards because these are the callouts
    puzzle_input_t * clean_boards = calloc(dirty_boards->num_items, sizeof(puzzle_input_t));
    clean_boards->num_items = dirty_boards->num_items - 1;
    clean_boards->puzzle_items = calloc(clean_boards->num_items, sizeof(puzzle_item_t *));
    int clean_index = 0;
    for(int i = 1; i < dirty_boards->num_items; i++)
    {
        if(0 != strnlen(dirty_boards->puzzle_items[i]->char_val, MAX_ITEM_LEN))
        {
            //copy item from dirty boards to clean boards and convert to long
            puzzle_item_t * clean_item = calloc(1, sizeof(puzzle_item_t));
            clean_item->char_val = calloc(MAX_ITEM_LEN, sizeof(char));
            strncpy(clean_item->char_val, dirty_boards->puzzle_items[i]->char_val, MAX_ITEM_LEN);

            convert_item_to_long(clean_item);

            //assign to puzzle_items and increment clean index
            clean_boards->puzzle_items[clean_index] = clean_item;
            clean_index++;
        }
        else
        {
            clean_boards->num_items--;
        }
    }

    //free dirty boards, we no longer need it. check clean boards is divisible by puzzle dimension squared.
    free_puzzle_input(dirty_boards);
    if(0 != clean_boards->num_items % (BOARD_DIM * BOARD_DIM))
    {
        fprintf(stderr, "Number of bingo items are not divisible by %d\n", (BOARD_DIM * BOARD_DIM));
        return NULL;
    }
    free(delimiters);
    delimiters = NULL;
    return clean_boards;
}

/**
 * @brief Create a bingo boards object and assign to hash table
 * 
 * @param num_boards - number of bingo boards
 * @param board_inputs - inputs to parse into bingo boards
 * @param hash_table - insert bingo items into this hash table
 * @return bingo_board_t** 
 */
bingo_board_t **
create_bingo_boards(int num_boards, puzzle_input_t * board_inputs, hash_table_t * hash_table)
{
    if(NULL == board_inputs)
    {
        fprintf(stderr, "board inputs cannot be NULL\n");
        return NULL;
    }

    bingo_board_t ** bingo_boards = calloc(num_boards, sizeof(bingo_board_t *));
    int board_input_index = 0;
    for(int i = 0; i < num_boards; i++)
    {
        bingo_boards[i] = calloc(1, sizeof(bingo_board_t));
        bingo_boards[i]->bingo_items = calloc(BOARD_DIM, sizeof(bingo_item_t **));
        bingo_boards[i]->is_winner = false;
        for(int j = 0; j < BOARD_DIM; j++)
        {
            bingo_boards[i]->bingo_items[j] = calloc(BOARD_DIM, sizeof(bingo_item_t *));
            for(int k = 0; k < BOARD_DIM; k++)
            {
                bingo_boards[i]->bingo_items[j][k] = calloc(1, sizeof(bingo_item_t));
                bingo_boards[i]->bingo_items[j][k]->value = (int) board_inputs->puzzle_items[board_input_index]->value;
                bingo_boards[i]->bingo_items[j][k]->is_on = 0;

                insert_hashtable(hash_table, bingo_boards[i]->bingo_items[j][k]->value, (void *) bingo_boards[i]->bingo_items[j][k]);

                board_input_index++;
            }
        }
    }

    return bingo_boards;
}

/**
 * @brief frees all memory allocated to every bingo board
 * 
 * @param bingo_boards - list of bingo boards to free
 * @param num_boards - number of bingo boards in the list
 */
void
free_bingo_boards(bingo_board_t ** bingo_boards, int num_boards)
{
    if(NULL == bingo_boards)
    {
        return;
    }

    for(int i = 0; i < num_boards; i++)
    {
        if(NULL != bingo_boards[i])
        {
            for(int j = 0; j < BOARD_DIM; j++)
            {
                for(int k = 0; k < BOARD_DIM; k++)
                {
                    free(bingo_boards[i]->bingo_items[j][k]);
                    bingo_boards[i]->bingo_items[j][k] = NULL;
                }
                free(bingo_boards[i]->bingo_items[j]);
                bingo_boards[i]->bingo_items[j] = NULL;
            }
            free(bingo_boards[i]->bingo_items);
            bingo_boards[i]->bingo_items = NULL;
            free(bingo_boards[i]);
            bingo_boards[i] = NULL;
        }
    }

    free(bingo_boards);
    bingo_boards = NULL;
}

/**
 * @brief displays the board values in a grid on the left and 
 *        a grid of whether that value has been selected on the right
 * 
 * @param bingo_board 
 */
void
print_board(bingo_board_t * bingo_board)
{
    if(NULL == bingo_board)
    {
        fprintf(stderr, "cannot print NULL board\n");
        return;
    }
    for(int j = 0; j < BOARD_DIM; j++)
    {
        for(int k = 0; k < BOARD_DIM; k++)
        {
            printf("%2d ", bingo_board->bingo_items[j][k]->value);
        }
        printf("   ");
        for(int k = 0; k < BOARD_DIM; k++)
        {
            printf("%d ", bingo_board->bingo_items[j][k]->is_on);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief displays the hash table for debugging
 * 
 * @param hash_table 
 */
void
print_hash_table(hash_table_t * hash_table)
{
    if(NULL == hash_table)
    {
        fprintf(stderr, "cannot print NULL hash table\n");
        return;
    }

    for(int i = 0; i < hash_table->num_buckets; i++)
    {
        printf("Bucket %2d: ", i);
        int bucket_index = 0;
        bool bucket_done = false;
        while(!bucket_done && bucket_index < *hash_table->bucket_sizes)
        {
            bingo_item_t * bingo_item = (bingo_item_t *) hash_table->items[i][bucket_index]->data;
            if(NULL != bingo_item)
            {
                printf("%d ", bingo_item->value);
            }
            else
            {
                bucket_done = true;
            }
            bucket_index++;
        }
        printf("\n");
    }
}

/**
 * @brief return the number of winners
 * 
 * @param winner_indexes - list of board indexes that have won so far
 * @param bingo_boards - list of bingo boards
 * @param num_boards - number of bingo boards
 * @return int - number of winners up to this point in the game
 */
int
find_winners(int * winner_indexes, bingo_board_t ** bingo_boards, int num_boards)
{
    if(NULL == winner_indexes)
    {
        fprintf(stderr, "winner indexes cannot be NULL\n");
        return ERROR;
    }
    if(NULL == bingo_boards)
    {
        fprintf(stderr, "cannot find winners in NULL bingo boards\n");
        return ERROR;
    }

    int num_winners = 0;
    for(int i = 0; i < num_boards; i++)
    {
        if(bingo_boards[i]->is_winner)
        {
            num_winners += 1;
        }
    }
    for(int i = 0; i < num_boards; i++)
    {
        bingo_board_t * board = bingo_boards[i];
        
        //check rows
        int row_idx = 0;
        while(!board->is_winner && row_idx < BOARD_DIM)
        {
            int sum = 0;
            for(int j = 0; j < BOARD_DIM; j++)
            {
                sum += board->bingo_items[row_idx][j]->is_on;
            }
            if(sum == BOARD_DIM)
            {
                winner_indexes[num_winners] = i;
                num_winners++;
                board->is_winner = true;
            }
            else
            {
                row_idx++;
            }
        }

        //check cols
        int col_idx = 0;
        while(!board->is_winner && col_idx < BOARD_DIM)
        {
            int sum = 0;
            for(int j = 0; j < BOARD_DIM; j++)
            {
                sum += board->bingo_items[j][col_idx]->is_on;
            }
            if(sum == BOARD_DIM)
            {
                winner_indexes[num_winners] = i;
                num_winners++;
                board->is_winner = true;
            }
            else
            {
                col_idx++;
            }
        }
    }
    return num_winners;
}

/**
 * @brief calculate the board sum based on the values in the board who's is_on
 *        property is 0
 * 
 * @param board - board to sum
 * @return int - sum of all values with is_on property equal to 0
 */
int
get_board_sum(bingo_board_t * board)
{
    if(NULL == board)
    {
        fprintf(stderr, "cannot sum NULL board\n");
        return ERROR;
    }

    int sum = 0;
    for(int i = 0; i < BOARD_DIM; i++)
    {
        for(int j = 0; j < BOARD_DIM; j++)
        {
            if(0 == board->bingo_items[i][j]->is_on)
            {
                sum += board->bingo_items[i][j]->value;
            }
        }
    }

    return sum;
}

/**
 * @brief code to solve part 1 of Day 4 AoC
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

    //read in called out numbers
    puzzle_input_t * called_out = read_called_out(filename);

    //read in board inputs
    puzzle_input_t * board_inputs = read_board_inputs(filename);
    int num_boards = board_inputs->num_items / (BOARD_DIM * BOARD_DIM);

    //initialize hash table
    hash_table_t * hash_table = create_hashtable(hash_key, HASH_KEY_SIZE);

    //create array of bingo boards
    bingo_board_t ** bingo_boards = create_bingo_boards(num_boards, board_inputs, hash_table);

    if(DEBUG_PRINT)
    {
        printf("num callouts: %d\n", called_out->num_items);
        printf("num board inputs: %d\n", board_inputs->num_items);
        printf("num boards: %d\n", num_boards);
        for(int i = 0; i < num_boards; i++)
        {
            printf("board %d is winner = %d\n", i, bingo_boards[i]->is_winner);
            print_board(bingo_boards[i]);
        }
        print_hash_table(hash_table);
    }

    //call out numbers and check to see if there is a winner
    int num_winners = 0;
    int * winner_indexes = calloc(called_out->num_items, sizeof(int));
    int called_index = 0;
    bool winner_found = false;
    while(called_index < called_out->num_items && !winner_found)
    {
        //set is_on for all called numbers to 1
        int called_num = (int) called_out->puzzle_items[called_index]->value;
        data_item_t ** bucket = hash_table->items[called_num];
        int bucket_index = 0;
        int bucket_done = false;
        while(!bucket_done && bucket_index < *hash_table->bucket_sizes)
        {
            bingo_item_t * called_item = (bingo_item_t *) bucket[bucket_index]->data;
            if(NULL != called_item)
            {
                called_item->is_on = 1;
                bucket_index++;
            }
            else
            {
                bucket_done = true;
            }
        }

        //check if there are any board winners
        if(called_index >= BOARD_DIM)
        {
            num_winners = find_winners(winner_indexes, bingo_boards, num_boards);
        }

        //check number of winners
        if(num_winners == 1)
        {
            winner_found = true;
        }
        else if(num_winners > 1)
        {
            fprintf(stderr, "multiple winners found");
            return ERROR;
        }
        else
        {
            called_index++;
        }
    }

    int last_called_value = (int) called_out->puzzle_items[called_index]->value;

    if(DEBUG_PRINT)
    {
        printf("last called index %d, val = %d\n", called_index, last_called_value);
        printf("winning board: %d\n", winner_indexes[0]);
    }

    //calculate the sum of all off inputs on the winning board
    int board_sum = get_board_sum(bingo_boards[winner_indexes[0]]);

    //free and end
    free_puzzle_input(called_out);
    free_puzzle_input(board_inputs);
    destroy_hashtable(hash_table);
    free_bingo_boards(bingo_boards, num_boards);
    free(winner_indexes);
    winner_indexes = 0;
    return board_sum * last_called_value;
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

    //read in called out numbers
    puzzle_input_t * called_out = read_called_out(filename);

    //read in board inputs
    puzzle_input_t * board_inputs = read_board_inputs(filename);
    int num_boards = board_inputs->num_items / (BOARD_DIM * BOARD_DIM);

    //initialize hash table
    hash_table_t * hash_table = create_hashtable(hash_key, HASH_KEY_SIZE);

    //create array of bingo boards
    bingo_board_t ** bingo_boards = create_bingo_boards(num_boards, board_inputs, hash_table);

    if(DEBUG_PRINT)
    {
        printf("num callouts: %d\n", called_out->num_items);
        printf("num board inputs: %d\n", board_inputs->num_items);
        printf("num boards: %d\n", num_boards);
        for(int i = 0; i < num_boards; i++)
        {
            printf("board %d is winner = %d\n", i, bingo_boards[i]->is_winner);
            print_board(bingo_boards[i]);
        }
        print_hash_table(hash_table);
    }

    //call out numbers and check to see if every board has won
    int num_winners = 0;
    int * winner_indexes = calloc(num_boards, sizeof(int));
    int called_index = 0;
    while(called_index < called_out->num_items && num_winners < num_boards)
    {
        //set is_on for all called numbers to 1
        int called_num = (int) called_out->puzzle_items[called_index]->value;
        data_item_t ** bucket = hash_table->items[called_num];
        int bucket_index = 0;
        int bucket_done = false;
        while(!bucket_done && bucket_index < *hash_table->bucket_sizes)
        {
            bingo_item_t * called_item = (bingo_item_t *) bucket[bucket_index]->data;
            if(NULL != called_item)
            {
                called_item->is_on = 1;
                bucket_index++;
            }
            else
            {
                bucket_done = true;
            }
        }

        //find the number of board winners at this point in the game
        if(called_index >= BOARD_DIM)
        {
            num_winners = find_winners(winner_indexes, bingo_boards, num_boards);
        }

        if(DEBUG_PRINT)
        {
            printf("called index %d\n", called_index);
            for(int k = 0; k < num_boards; k++)
            {
                printf("board %d is winner %d\n", k, bingo_boards[k]->is_winner);
            }
            for(int k = 0; k < num_winners; k++)
            {
                printf("winner #%d = %d\n", k + 1, winner_indexes[k]);
            }
            printf("\n");
        }

        //do not increment called index if the game is over so we know the last called value
        if(num_winners < num_boards)
        {
            called_index++;
        }
    }

    //throw an error if the game completed before everyone won
    if(num_winners != num_boards)
    {
        fprintf(stderr, "number of winners %d is not equal to number of boards %d\n", num_winners, num_boards);
        return ERROR;
    }

    //get the last called value
    int last_called_value = (int) called_out->puzzle_items[called_index]->value;

    if(DEBUG_PRINT)
    {
        for(int i = 0; i < num_boards; i++)
        {
            printf("board %d, is winner %d\n", i, bingo_boards[i]->is_winner);
            print_board(bingo_boards[i]);
        }
        printf("last called index %d, val = %d\n", called_index, last_called_value);
        printf("last winning board: %d\n", winner_indexes[num_boards - 1]);
    }

    //calculate the sum of all off inputs on the last winning board
    int board_sum = get_board_sum(bingo_boards[winner_indexes[num_boards - 1]]);

    //free and end
    free_puzzle_input(called_out);
    free_puzzle_input(board_inputs);
    destroy_hashtable(hash_table);
    free_bingo_boards(bingo_boards, num_boards);
    free(winner_indexes);
    winner_indexes = 0;
    return board_sum * last_called_value;
}