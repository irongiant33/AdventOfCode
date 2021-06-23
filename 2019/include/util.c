//includes
#include "aoc.h"

/*
* This function is helpful to display what the program values look like at
* various points in time
*
*/
int display_values(int * values, int num_values)
{
  if(NULL == values)
  {
    errno = EINVAL;
    return ERROR;
  }

  for(int i = 0; i < num_values; i++)
  {
    printf("%d ", values[i]);
  }
  printf("\n");
  return SUCCESS;
}

/*
* This function reads from a file and stores the integer values in an array.
* It returns the total number of items in the array, splitting items at the
* delimiter
*/
int read_from_file(char * filename, int * values, char delimiter)
{
  if(NULL == filename || NULL == values)
  {
    errno = EINVAL;
    return ERROR;
  }

  FILE * fp = fopen(filename, "r");
  if(NULL == fp)
  {
    perror("error reading from file");
    return ERROR;
  }
  char val = fgetc(fp);
  int index = 0; //tracks the number of mass values provided
  while(EOF != val)
  {
    char buffer[BUFF_SIZE];
    memset(buffer, '\0', BUFF_SIZE);
    uint8_t buff_index = 0;
    //read in the number until a delimiter or the end of the file is reached
    while(BUFF_SIZE > buff_index)
    {
      if(EOF == val || delimiter == val)
      {
        val = fgetc(fp);
        break;
      }
      buffer[buff_index] = val;
      val = fgetc(fp);
      buff_index++;
    }
    //if the number is more than 0 characters long, convert it to an integer
    if(0 < buff_index)
    {
      int value = atoi(buffer);
      values[index] = value;
      index++;
    }
  }
  fclose(fp);
  return index;
}
