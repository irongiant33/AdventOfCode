//to compile: gcc -o solution solution.c ../include/util.c
//includes
#include "../include/aoc.h"

//global variables
char input_file[] = "input.txt"; //name of the file in which to find the masses
extern int errno;

//definitions
#define MAX_INPUT_SIZE 1024 //maximum number of inputs to accept. This has been
                            //arbitrarily set, if you want to calculate fuel
                            //for more inputs, increase this number
#define SUBTRACT_FUEL 2
#define DIVIDE_MASS 3
#define DELIMITER '\n'

/*
* This function sums the fuel values according to the problem requirements.
* It takes the input masses, divides by 3, rounds down, and then subtracts
* by 2. To find the total fuel requirement, it sums all of the fuel values.
*/
int sum_values(int * values, int num_values)
{
  if(NULL == values)
  {
    errno = EINVAL; //set invalid argument error
    return ERROR;
  }

  int sum = 0;
  for(int i = 0; i < num_values; i++)
  {
    int temp_value = values[i];
    temp_value = ((int) temp_value / DIVIDE_MASS);
    //make sure that the fuel value cannot be negative. At the least, it is 0
    if(SUBTRACT_FUEL < temp_value)
    {
      temp_value -= SUBTRACT_FUEL;
    }
    else
    {
      temp_value = 0;
    }
    sum += temp_value;
  }
  return sum;
}

/*
* This function sums the fuel recursively until there is no more mass to be
* added.
*/
int sum_recursive(int * values, int num_values)
{
  if(NULL == values)
  {
    errno = EINVAL; //set invalid argument ERROR
    return ERROR;
  }
  int sum = 0;
  int min_mass = SUBTRACT_FUEL * DIVIDE_MASS; //the minimum amount of mass
                                              //that needs more fuel
  for(int i = 0; i < num_values; i++)
  {
    int temp_value = values[i];
    int temp_sum = 0;
    while(min_mass < temp_value)
    {
      temp_value = sum_values(&temp_value, 1);
      sum += temp_value;
    }
  }
  return sum;
}

int main()
{
  //allocate memory
  int * mass_values = calloc(MAX_INPUT_SIZE, sizeof(int));
  if(NULL == mass_values)
  {
    perror("error allocating memory for mass_values");
    return ERROR;
  }

  //read from file, conduct operations on input, and return
  int num_inputs = read_from_file(input_file, mass_values, DELIMITER);
  if(ERROR == num_inputs)
  {
    perror("error reading from file");
    printf("Filename: %s\n", input_file);
    return ERROR;
  }
  int fuel_requirement = sum_values(mass_values, num_inputs);
  if(ERROR == fuel_requirement)
  {
    perror("Error calculating fuel requirement");
    return ERROR;
  }
  printf("Part 1: The fuel requirement is %d\n", fuel_requirement);
  int recursive_fuel = sum_recursive(mass_values, num_inputs);
  if(ERROR == recursive_fuel)
  {
    perror("Error calculating recursive fuel requirement");
    return ERROR;
  }
  printf("Part 2: The fuel requirement is %d\n", recursive_fuel);

  //free and return
  free(mass_values);
  return SUCCESS;
}
