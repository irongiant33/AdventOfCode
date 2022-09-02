#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define ERROR                              -1
#define SUCCESS                            0
#define NUM_CHARS_TO_READ                  1
#define NO_EOF                             0
#define DEFAULT_NUM_PUZZLE_ITEMS      100000
#define DEBUG                          false
#define DEFAULT_HASH_TABLE_BUCKET_SIZE   100
#define BASE                              10
#define MAX_STRN_LEN                     500
#define COMPARE_ERROR                     -2

////////////////////////////////////////////////////////////////////////////////
// doubly_ll

typedef struct doubly_ll_item doubly_ll_item_t;

typedef struct doubly_ll_item
{
    void * item;
    doubly_ll_item_t * prev;
    doubly_ll_item_t * next;
}doubly_ll_item_t;

typedef struct doubly_ll
{
    doubly_ll_item_t ** list;
    doubly_ll_item_t * head;
    int num_items;
    int max_size;
}doubly_ll_t;

/**
 * @brief add item to doubly linked list at the index
 * 
 * @param list - list to add to
 * @param item - item to add
 * @param index - index to add at. If NULL, append the item
 * @return int - -1 if error, 0 if success
 */
int
doubly_ll_add(doubly_ll_t * list, void * item, int * add_at_index);

/**
 * @brief remove an item from the linked list and return its value
 * 
 * @param list - list to remove from
 * @param index - item index to remove
 * @return void* - value of the removed item
 */
void *
doubly_ll_remove(doubly_ll_t * list, int index);

/**
 * @brief free and destroy the doubly linked list. does not free the items
 *        stored within the list items themselves
 * 
 * @param list - list to destroy
 * @return int - success code
 */
int
doubly_ll_destroy(doubly_ll_t * list);

/**
 * @brief retrieve an item from the doubly linked list
 * 
 * @param list - list to retrieve from
 * @param index - index to retrieve
 * @return doubly_ll_item_t* - retrieved item
 */
doubly_ll_item_t *
doubly_ll_fetch(doubly_ll_t * list, int index);

/**
 * @brief initialize doubly linked list
 * 
 * @param size - maximum number of items in the list
 * @return doubly_ll_t* 
 */
doubly_ll_t *
doubly_ll_init(int max_size);

/**
 * @brief swap the two indices within the doubly linked list
 * 
 * @param list - list to swap from
 * @param i - index a
 * @param j - index b
 * @return int - success code
 */
int
doubly_ll_swap(doubly_ll_t * list, int i, int j);

/**
 * @brief helper function to partition the list for quicksort
 * 
 * @param list - list to partition
 * @param compare - comparison function
 * @param low - start index
 * @param high - stop index (does not include this number)
 * @return int - index at which the list should be partitioned
 */
int
partition(doubly_ll_t * list, int (*compare)(doubly_ll_item_t * item_a, doubly_ll_item_t * item_b), int low, int high);

/**
 * @brief sort a doubly linked list using quicksort
 * 
 * @param list - list to sort
 * @param compare - function to compare items in the list. Should return:
 *                  -1 if item_a < b
 *                   0 if item_a == item_b
 *                   1 if item_a > item_b
 * @param low - start index
 * @param high - stop index (not included)
 * @return int success code
 */
int
doubly_ll_sort(doubly_ll_t * list, int (*compare)(doubly_ll_item_t * item_a, doubly_ll_item_t * item_b), int low, int high);

/**
 * @brief finds an item in the doubly ll based on the data 
 * 
 * @param list - doubly ll to search
 * @param label - label to find
 * @param compare - pointer to function to compare data with items
 * @return doubly_ll_item_t * - pointer to the found item
 */
doubly_ll_item_t *
doubly_ll_find(doubly_ll_t * list, void * data, int (*compare)(doubly_ll_item_t * item_a, void * data));

/**
 * @brief counts number of occurences of an item in the doubly ll based on the data 
 * 
 * @param list - doubly ll to search
 * @param label - label to find
 * @param compare - pointer to function to compare data with items. Should return 0 if the comparison matches.
 *                  return a value greater than 0 for greater than, less than 0 for less than.
 * @return int - number of times the data has been found
 */
int
doubly_ll_count(doubly_ll_t * list, void * data, int (*compare)(doubly_ll_item_t * item_a, void * data));

////////////////////////////////////////////////////////////////////////////////
// fileio

typedef struct puzzle_item
{
    char * char_val;
    long value;
}puzzle_item_t;

typedef struct puzzle_input
{
    puzzle_item_t ** puzzle_items;
    int num_items;
}puzzle_input_t;

/**
 * @brief Reads a file and stores the contents in contents
 * 
 * @param filename - filename to read
 * @param contents - contents to store (preallocated)
 * @param num_lines - number of lines to read
 * @param num_chars_per_line - number of characters per line
 * @return int 
 */
puzzle_input_t * read_file(char * filename, char ** delimiters, int num_delimiters, char * end_char);

/**
 * @brief frees memory allocated to puzzle_input struct
 * 
 * @param puzzle_input 
 */
void free_puzzle_input(puzzle_input_t * puzzle_input);

/**
 * @brief converts the entirety of the puzzle input to long
 * 
 * @param puzzle_input - puzzle input to convert
 * @return int - success code
 */
int
convert_input_to_long(puzzle_input_t * puzzle_input);

/**
 * @brief converts a puzzle item's char_val to long
 * 
 * @param puzzle_item - puzzle item to convert
 * @return int - success code
 */
int
convert_item_to_long(puzzle_item_t * puzzle_item);

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
filter_by_index(puzzle_input_t * puzzle_input, int start_index, int increment);

/**
 * @brief filter the puzzle input by removing every instance of the specified value
 * 
 * @param puzzle_input 
 * @param value 
 * @return puzzle_input_t* 
 */
puzzle_input_t *
filter_by_value(puzzle_input_t * puzzle_input, char value);

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
filter_by_length(puzzle_input_t * puzzle_input, int length);

////////////////////////////////////////////////////////////////////////////////
// hash_table

/**
 * @brief The basic node that will be stored in the hash table.
 *
 * We're going to be sticking with integers just because it's easy to write
 * a hash function. Given that 3.1.13 already covered writing a hash function
 * it seems to make sense on the actual data structure here.
 */
typedef struct _data_item_t {
    void * data; ///< The data stored 
    int key; ///< the key
} data_item_t;

/**
 * @brief a function pointer to a custom-defined hash function.
 * takes an integer key and returns an integer hash
 */
typedef int (*hash_func)(int key);

/**
 * @brief The actual hash table itself.
 * 
 * The new value replaces the old value if inserting the same key multiple times
 *
 * Your design must include some way of mitigating hash collisions. The fields 
 * defined in hash_table_t should provide a hint on how to do so.
 */
typedef struct _hash_table_t {
    data_item_t ***items; ///< Buckets and their corresponding items
    int *bucket_sizes;  ///< Size of each of the buckets
    hash_func hash_f; ///< Hash function 
    int num_buckets; ///< Might be useful to keep track of how many buckets you
                     ///< have
} hash_table_t;

/**
 * @brief Create a new empty hash table
 * 
 * @param hash_func The hash function that will be used
 * @param num_buckets the initial number of buckets to create
 */
hash_table_t *create_hashtable(hash_func hash_f, int num_buckets);

/**
 * @brief Insert a new item into the hash table.
 * 
 * @param table The table to insert into
 * @param key The new key
 * @param data The new data
 * 
 * @return 0 on success
 */
int insert_hashtable(hash_table_t *table, int key, void * data);

/**
 * @brief Remove an item from the hash table.
 * 
 * @param table The table to delete from
 * @param key The key to remove
 * 
 * @return <0 on error, 0 on success, >0 if key not in hash table
 */
int delete_from_hashtable(hash_table_t *table, int key);

/**
 * @brief Retrieve an item from the hash table.
 * 
 * @param table The table to get the item from
 * @param key The key to retrieve
 * 
 * @return Pointer to the requested item or NULL
 */
data_item_t *get_from_hashtable(hash_table_t *table, int key);

/**
 * @brief Remove all items from the hash table.
 * 
 * @param table The table to empty.
 * 
 * @return 0 on success
 */
int empty_hashtable(hash_table_t *table);

/**
 * @brief Destroy the hash table.
 * 
 * @param table The table to destroy
 * 
 * @return 0 on success
 */
int destroy_hashtable(hash_table_t *table);

////////////////////////////////////////////////////////////////////////////////
// graph

typedef struct graph_node graph_node_t;

typedef struct graph_node
{
    void * data;
    doubly_ll_t * neighbors;
}graph_node_t;

////////////////////////////////////////////////////////////////////////////////
// string_ops

/**
 * @brief determine if the string is all uppercase.
 * 
 * @param string - string to compare
 * @return int - success code. 0 if true, 1 if false, -1 if error
 */
int
is_upper(char * string);