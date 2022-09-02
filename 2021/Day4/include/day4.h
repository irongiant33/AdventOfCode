#include "../../common/common.h"

#define DEBUG_PRINT     false
#define MAX_ITEM_LEN       10
#define BOARD_DIM           5

// The highest bingo number is 99, so choose 100 to give each bingo number its own bucket in the hash table
#define HASH_KEY_SIZE     100

typedef struct bingo_item
{
    int value;
    int is_on;
}bingo_item_t;

typedef struct bingo_board
{
    bingo_item_t *** bingo_items;
    bool is_winner;
}bingo_board_t;

/**
 * @brief Calculate the hash for a key
 *
 * @param key The key to hash
 */
int
hash_key(int key);

/**
 * @brief read in the called out numbers. sets the value property by converting
 *        from char to long
 * 
 * @param filename 
 * @return puzzle_input_t* 
 */
puzzle_input_t *
read_called_out(char * filename);

/**
 * @brief read in the board inputs and remove the callouts and all values that are empty.
 *        sets the value property of the puzzle items by converting the input to long.
 * 
 * @param filename 
 * @return puzzle_input_t* 
 */
puzzle_input_t *
read_board_inputs(char * filename);

/**
 * @brief Create a bingo boards object and assign to hash table
 * 
 * @param num_boards - number of bingo boards
 * @param board_inputs - inputs to parse into bingo boards
 * @param hash_table - insert bingo items into this hash table
 * @return bingo_board_t** 
 */
bingo_board_t **
create_bingo_boards(int num_boards, puzzle_input_t * board_inputs, hash_table_t * hash_table);

/**
 * @brief frees all memory allocated to every bingo board
 * 
 * @param bingo_boards - list of bingo boards to free
 * @param num_boards - number of bingo boards in the list
 */
void
free_bingo_boards(bingo_board_t ** bingo_boards, int num_boards);

/**
 * @brief displays the board values in a grid on the left and 
 *        a grid of whether that value has been selected on the right
 * 
 * @param bingo_board 
 */
void
print_board(bingo_board_t * bingo_board);

/**
 * @brief displays the hash table for debugging
 * 
 * @param hash_table 
 */
void
print_hash_table(hash_table_t * hash_table);

/**
 * @brief return the number of winners
 * 
 * @param winner_indexes - list of board indexes that have won so far
 * @param bingo_boards - list of bingo boards
 * @param num_boards - number of bingo boards
 * @return int - number of winners up to this point in the game
 */
int
find_winners(int * winner_indexes, bingo_board_t ** bingo_boards, int num_boards);

/**
 * @brief calculate the board sum based on the values in the board who's is_on
 *        property is 0
 * 
 * @param board - board to sum
 * @return int - sum of all values with is_on property equal to 0
 */
int
get_board_sum(bingo_board_t * board);

/**
 * @brief code to solve part 1 of Day 4 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename);

/**
 * @brief solves part 2 of day 4 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename);