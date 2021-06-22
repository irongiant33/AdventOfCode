//includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//global variables
char input_file[] = "input.txt";

//definitions
#define ERROR -1
#define SUCCESS 1
#define BUFF_SIZE 255
#define MAX_INPUT_SIZE 1024

int read_from_file(char * filename, int * mass_values)
{
  FILE * fp = open(filename, "r");
  if(NULL == fp)
  {
    perror("error reading from file");
    return NULL;
  }
  char val = fgetc(fp);
  int mass_index = 0;
  while(EOF != val)
  {
    char buffer[BUFF_SIZE];
    memset(buffer, '\0', BUFF_SIZE);
    uint8_t buff_index = 0;
    while(BUFF_SIZE > buff_index)
    {
      buffer[buff_index] = val;
      val = fgetc(fp);
      buff_index++;
      if(EOF == val || '\n' == val)
      {
        break;
      }
    }
    if(0 < buff_index)
    {
      mass_values[mass_index] = atoi(buffer);
    }
    mass_index++;
  }
  close(fp);
  return mass_index;
}

int sum_values(int * values, int num_values)
{
  int sum = 0;
  for(int i = 0; i < num_values; i++)
  {
    sum += values[i];
  }
  return sum;
}

int main()
{
  int * mass_values = calloc(MAX_INPUT_SIZE, sizeof(int));
  int num_inputs = read_from_file(input_file, mass_values);
  if(NULL == mass_values)
  {
    return ERROR;
  }
  int fuel_requirement = sum_values(mass_values, MAX_INPUT_SIZE);
  printf("The fuel requirement is %d\n", fuel_requirement);
  free(mass_values);
  return SUCCESS;
}
