//includes
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

//definitions
#define ERROR -1
#define SUCCESS 1
#define BUFF_SIZE 255 //the length of the biggest integer to convert. This is
                      //unrealistic because the maximum size of an integer is
                      //(2^32)/2 ~= 2,147,483,647. We could set the value of
                      //BUFF_SIZE to 10, but then we would have to check if
                      //the integer is less than the max value. As it stands,
                      //the integer conversion just rolls over if the value
                      //is greater than max

//structs

//functions
int read_from_file(char * filename, int * values, char delimiter);
int display_values(int * values, int num_values);
