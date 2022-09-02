#include "../include/day8.h"

#define DEBUG_PRINT false

#define ONE_LEN     2
#define SEVEN_LEN   3
#define FOUR_LEN    4
#define EIGHT_LEN   7

#define DISPLAY_LEN 4
#define INPUTS_PER_LINE 15
#define NUM_SEGMENTS 7
#define NUM_LEARNING_INPUTS 10

/**
 * @brief retrieve the puzzle input
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
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, num_delimiters, NULL);

    puzzle_input_t * new_puzzle_input = filter_by_index(puzzle_input, 10, INPUTS_PER_LINE);

    free(delimiters);
    delimiters = NULL;
    return new_puzzle_input;
}

/**
 * @brief code to solve part 1 of Day 8 AoC
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

    //count to see how many led panels at multiples of indexes 10, 11, 12, 13 are
    //equal to 2, 3, 4, or 7
    int easy_count = 0;
    int base_index = NUM_LEARNING_INPUTS;
    while(base_index < puzzle_input->num_items)
    {
        for(int i = 0; i < DISPLAY_LEN; i++)
        {
            int length = (int) strnlen(puzzle_input->puzzle_items[base_index + i]->char_val, EIGHT_LEN + 1);
            if(length == ONE_LEN || length == FOUR_LEN || length == SEVEN_LEN || length == EIGHT_LEN)
            {
                easy_count++;
            }
        }
        base_index += INPUTS_PER_LINE - 1;
    }

    //free and return running total
    free_puzzle_input(puzzle_input);
    return easy_count;
}

/**
 * @brief convert the active wire string into a uint8_t bitmask
 * This is an example conversion:
 * abe
 * 1100100 = 100
 * 
 * abcdefg
 * 1111111 = 127
 * 
 * @param active_wires - string of wires that are active
 * @param num_active_wires - length of active wires string
 * @return uint8_t - bitmask for the active wires
 */
uint8_t
string_to_mask(char * active_wires, int num_active_wires)
{
    if(NULL == active_wires)
    {
        fprintf(stderr, "cannot convert NULL string to bitmask\n");
        return 0;
    }

    uint8_t mask = 0;
    for(int i = 0; i < num_active_wires; i++)
    {
        switch (active_wires[i])
        {
        case 'a':
            mask += 1 << 6;
            break;
        case 'b':
            mask += 1 << 5;
            break;
        case 'c':
            mask += 1 << 4;
            break;
        case 'd':
            mask += 1 << 3;
            break;
        case 'e':
            mask += 1 << 2;
            break;
        case 'f':
            mask += 1 << 1;
            break;
        case 'g':
            mask += 1 << 0;
            break;
        default:
            break;
        }
    }
    return mask;
}

/**
 * @brief decode the test input
 * 
 * @param active_wires 
 * @param pos 
 * @return int 
 */
int
decode(char * active_wires, uint8_t * pos)
{
    if(NULL == active_wires)
    {
        fprintf(stderr, "cannot decode NULL active wires\n");
        return ERROR;
    }
    //bitmasks of the values 0 through 9 where the MSB corresponds to whether
    //region 0 is turned on/off and the LSB corresponds to whether region 6 is
    //turned on/off
    uint8_t actual[10] = {119, 18, 93, 91, 58, 107, 111, 82, 127, 123};

    int num_active = (int) strnlen(active_wires, NUM_SEGMENTS);

    //calculate the bitmask of the incoming test value to lookup the decoded value
    uint8_t test_val = 0;
    for(int i = 0; i < num_active; i++)
    {
        uint8_t lookup = 0;
        switch (active_wires[i])
        {
        case 'a':
            lookup = 64;
            break;
        case 'b':
            lookup = 32;
            break;
        case 'c':
            lookup = 16;
            break;
        case 'd':
            lookup = 8;
            break;
        case 'e':
            lookup = 4;
            break;
        case 'f':
            lookup = 2;
            break;
        case 'g':
            lookup = 1;
            break;
        default:
            break;
        }
        for(int j = 0; j < NUM_SEGMENTS; j++)
        {
            if(pos[j] == lookup)
            {
                test_val += 1 << (NUM_SEGMENTS - j - 1);
            }
        }
    }

    int decoded = -1;
    int index = 0;
    while(0 > decoded)
    {
        if(actual[index] == test_val)
        {
            decoded = index;
        }
        index++;
    }
    return decoded;
}

/**
 * @brief solves part 2 of day 8 AOC 2021
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

    //create "learning" matrix
    uint8_t ** learning_matrix = calloc(NUM_SEGMENTS + 1, sizeof(uint8_t *));
    for(int i = 0; i < NUM_SEGMENTS + 1; i++)
    {
        //3 is the maximum # of values that can be of any one length
        learning_matrix[i] = calloc(3, sizeof(uint8_t));
        for(int j = 0; j < 3; j++)
        {
            learning_matrix[i][j] = 0;
        }
    }

    //decode the 4 test outputs for every 10 learning inputs
    int sum = 0;
    for(int test_idx = 0; test_idx < puzzle_input->num_items; test_idx += (INPUTS_PER_LINE - 1))
    {
        //assign the 10 learning inputs to the learning matrix
        for(int i = 0; i < NUM_LEARNING_INPUTS; i++)
        {
            char * active_wires = puzzle_input->puzzle_items[i + test_idx]->char_val;
            int num_active_segments = (int) strnlen(active_wires, NUM_SEGMENTS);
            int sub_index = 0;
            while(0 != learning_matrix[num_active_segments][sub_index])
            {
                sub_index++;
            }
            learning_matrix[num_active_segments][sub_index] = string_to_mask(active_wires, num_active_segments);
        }

        //do logic to find wire-segment associations
        uint8_t * pos = calloc(NUM_SEGMENTS, sizeof(uint8_t));
        pos[0] = learning_matrix[2][0] ^ learning_matrix[3][0]; 
        pos[3] = learning_matrix[4][0] & learning_matrix[5][0] & 
                     learning_matrix[5][1] & learning_matrix[5][2];
        pos[1] = (learning_matrix[4][0] ^ pos[3]) ^ learning_matrix[2][0];
        pos[6] = (learning_matrix[5][0] & learning_matrix[5][1] & 
                     learning_matrix[5][2]) ^ pos[0] ^ pos[3];
        pos[4] = (~learning_matrix[4][0] & 127) ^ (pos[0] | pos[6]);
        pos[2] = ((learning_matrix[6][0] ^ learning_matrix[6][1]) | 
                     (learning_matrix[6][0] ^ learning_matrix[6][2]) | 
                     (learning_matrix[6][1] ^ learning_matrix[6][2])) ^ (pos[3] | pos[4]);
        pos[5] = learning_matrix[2][0] ^ pos[2];

        //take test input and decode value
        int value = 0;
        int factors[4] = {1000, 100, 10, 1};
        for(int i = 0; i < DISPLAY_LEN; i++)
        {
            char * active_wires = puzzle_input->puzzle_items[i + NUM_LEARNING_INPUTS + test_idx]->char_val;
            int decoded = decode(active_wires, pos);
            value += decoded * factors[i];
        }

        //add to sum
        sum += value;

        //zeroize learning matrix
        for(int i = 0; i < NUM_SEGMENTS + 1; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                learning_matrix[i][j] = 0;
            }
        }

        //free allocated variables
        free(pos);
        pos = NULL;
    }

    //free and return running total
    free_puzzle_input(puzzle_input);
    for(int i = 0; i < NUM_SEGMENTS + 1; i++)
    {
        free(learning_matrix[i]);
        learning_matrix[i] = NULL;
    }
    free(learning_matrix);
    learning_matrix = NULL;
    return sum;
}