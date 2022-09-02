#include "common.h"

/**
 * @brief determine if the string is all uppercase.
 * 
 * @param string - string to compare
 * @return int - success code. 0 if true, 1 if false, -1 if error
 */
int
is_upper(char * string)
{
    if(NULL == string)
    {
        fprintf(stderr, "cannot determine NULL string to be uppercase\n");
        return ERROR;
    }

    //determine if entire string is uppercase
    size_t string_len = strnlen(string, MAX_STRN_LEN);
    bool is_upper = true;
    size_t index = 0;
    while(is_upper && index < string_len)
    {
        if(string[index] < 'A' || string[index] > 'Z')
        {
            is_upper = false;
        }
        index++;
    }

    //return codes
    if(is_upper)
    {
        return 0;
    }
    return 1;
}