//to compile: gcc -o solution solution.c ../include/util.c
//includes
#include "../include/aoc.h"

//definitions
#define ADD 1
#define MUL 2
#define HALT 99
#define MAX_NUM_INSTRUCTIONS 10000 //the maximum number of instructions per
                                   //program
#define ACCESS_POS 0 //the position of the value to return after the run_intcode
                     //program executes
#define DELIMITER ','
#define NOUN 12 //defined as per the AoC pt.2 instructions
#define NOUN_IDX 1
#define VERB 2 //defined as per the AoC pt.2 instructions
#define VERB_IDX 2
#define DESIRED_RESULT 19690720 //desired output of the intcode program perror
                                //AoC pt.2 instructions
#define FACTOR 100
#define MAX_NOUN_VERB 1000 //maximum value for the noun and verb

//global variables
char input_file[] = "input.txt";


/*
* Grabs a value from the array, increments the instruction pointer, and then
* returns a value.
*/
int take_value(int * program_values)
{
  if(NULL == program_values)
  {
    errno = EINVAL;
    return ERROR;
  }

  static int instruction_ptr = 0;
  int value = program_values[instruction_ptr];
  instruction_ptr++;
  return value;
}

/*
* Runs the intcode program according to specifications in the AoC.
* It resets the values in the array as it runs, so the user should just
* inspect the desired index to retrieve the final program value
*/
int run_intcode(int * program_values, int num_values)
{
  if(NULL == program_values)
  {
    errno = EINVAL;
    return ERROR;
  }

  bool is_running = true;
  while(is_running)
  {
    int code = take_value(program_values);
    switch (code)
    {
      int value1;      //first value in the operation
      int value2;      //second value in the operation
      int index;       //index to find a value
      int store_index; //index to store the result in
      int result;      //variable to hold the result of the operation
      case ADD:;
        index = take_value(program_values);
        value1 = program_values[index];
        index = take_value(program_values);
        value2 = program_values[index];
        store_index = take_value(program_values);

        result = value1 + value2;
        program_values[store_index] = result;
        break;
      case MUL:;
        index = take_value(program_values);
        value1 = program_values[index];
        index = take_value(program_values);
        value2 = program_values[index];
        store_index = take_value(program_values);

        result = value1 * value2;
        program_values[store_index] = result;
        break;
      case HALT:
        is_running = false;
        break;
      default:
        errno = code;
        return ERROR;
        break;
    }
  }
  return SUCCESS;
}

/*
* Finds the NOUN and VERB that create the desired_result. The NOUN is the integer
* at position 1, the VERB is the int at position 2.
*/
int find_result(int desired_result, int * memory, int num_values)
{
  if(NULL == memory)
  {
    errno = EINVAL;
    return ERROR;
  }
  int noun = 0;
  int * program_values = calloc(num_values, sizeof(int));
  memcpy(program_values, memory, num_values);
  bool not_found = true;
  while(not_found && MAX_NOUN_VERB > noun)
  {
    int verb = 0;
    while(noun >= verb)
    {
      program_values[NOUN_IDX] = noun;
      program_values[VERB_IDX] = verb;
      if(ERROR == run_intcode(program_values, num_values))
      {
        perror("error running intcode program");
        printf("error code #%d\n", errno);
        return ERROR;
      }
      if(desired_result == program_values[ACCESS_POS])
      {
        not_found = false;
        break;
      }
      memcpy(program_values, memory, num_values);
      verb++;
    }
    if(not_found)
    {
      noun++;
    }
  }
  free(program_values);
  int output = FACTOR * program_values[NOUN_IDX] + program_values[VERB_IDX];
  return output;
}

int main()
{
  //initialize the intcode program memory
  int * memory = calloc(MAX_NUM_INSTRUCTIONS, sizeof(int));
  if(NULL == memory)
  {
    perror("error allocating memory for memory");
    return ERROR;
  }
  int num_values = read_from_file(input_file, memory, DELIMITER);
  if(ERROR == num_values)
  {
    perror("error converting text file to array");
    return ERROR;
    return ERROR;
  }

  //copy the memory for part 1 and run intcode
  int * program_values = calloc(num_values, sizeof(int));
  memcpy(program_values, memory, num_values);
  program_values[NOUN_IDX] = NOUN;
  program_values[VERB_IDX] = VERB;
  if(ERROR == run_intcode(program_values, num_values))
  {
    perror("error running the intcode program");
    printf("error code #%d\n", errno);
    return ERROR;
  }
  printf("Part 1: The value at position %d is %d\n", ACCESS_POS,
         program_values[ACCESS_POS]);

  //find the desired result
  int output = find_result(DESIRED_RESULT, memory, num_values);
  if(ERROR == output)
  {
    perror("error finding the desired result");
    return ERROR;
  }
  printf("Part 2: The output is %d\n", output);

  //free and return
  free(program_values);
  free(memory);
  return SUCCESS;
}
