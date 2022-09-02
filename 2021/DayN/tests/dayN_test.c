#include "CUnit/Basic.h"

#include "../include/dayN.h"

void
test_fileio_no_delimiter_no_end(void)
{
    puzzle_input_t * puzzle_input = read_file("../src/example_input1.txt", NULL, 0, NULL);
    CU_ASSERT_EQUAL(89, puzzle_input->num_items);
}

void
test_fileio_no_delimiter_end(void)
{
    char end_char = '\n';
    puzzle_input_t * puzzle_input = read_file("../src/example_input.txt", NULL, 0, &end_char);
    CU_ASSERT_EQUAL(6, puzzle_input->num_items);
}

void
test_fileio_one_delimiter_no_end(void)
{
    char ** delimiters = calloc(1, sizeof(char *));
    char delimiter = '\n';
    delimiters[0] = &delimiter;
    puzzle_input_t * puzzle_input = read_file("../src/example_input.txt", delimiters, 1, NULL);
    CU_ASSERT_EQUAL(5, puzzle_input->num_items);
    free(delimiters);
    delimiters = NULL;
}

void
test_fileio_one_delimiter_end(void)
{
    char ** delimiters = calloc(1, sizeof(char *));
    char delimiter = ',';
    delimiters[0] = &delimiter;
    char end_char = '8';
    puzzle_input_t * puzzle_input = read_file("../src/example_input2.txt", delimiters, 1, &end_char);
    CU_ASSERT_EQUAL(3, puzzle_input->num_items);
    free(delimiters);
    delimiters = NULL;
}

void
test_fileio_two_delimiters_no_end(void)
{
    char ** delimiters = calloc(2, sizeof(char *));
    char delimiter1 = '\n';
    char delimiter2 = ',';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    puzzle_input_t * puzzle_input = read_file("../src/example_input3.txt", delimiters, 2, NULL);
    CU_ASSERT_EQUAL(10, puzzle_input->num_items);
    free(delimiters);
    delimiters = NULL;
}

void
test_fileio_two_delimiters_end(void)
{
    char ** delimiters = calloc(2, sizeof(char *));
    char delimiter1 = '\n';
    char delimiter2 = ',';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    char end_char = '9';
    puzzle_input_t * puzzle_input = read_file("../src/example_input3.txt", delimiters, 2, &end_char);
    CU_ASSERT_EQUAL(9, puzzle_input->num_items);
    free(delimiters);
    delimiters = NULL;
}

/**
 * @brief test whether the fileio will successfully realloc if there are more
 *        test items than default
 * 
 */
void
test_fileio_realloc(void)
{
    CU_ASSERT_EQUAL(0, 1);
}