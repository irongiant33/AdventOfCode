#include "../../common/common.h"

int
part1(char * filename);

int
part2(char * filename);

/**
 * @brief convert from unsigned binary string to long value
 * 
 * @param bin_str of format XXXXXX where X is 0 or 1.
 * @param num_bits number of bits in the binary string
 * @return long - value of binary string, or -1 if there is an error
 */
long
convert_from_bin_str(char * bin_str, int num_bits);

/**
 * @brief 
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
frequency_selective_filter(puzzle_input_t * puzzle_input, int * bit_frequency, int num_bits, bool most_common);