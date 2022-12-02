#include <fstream>
#include <iostream>
#include <algorithm>

/*
@brief solve part 1 of advent of code

@param filename: file to read the input from

@return max_calories: maximum number of calories an elf is carrying
*/
int part1(std::string filename);

/*
@brief solve part 2 of advent of code

@param filename: filename to read input from
@param top_n: number of elves from which to create the sum. Should be less than the total number of elves.

@return top_total: total number of calories for the top_n elves
*/
int part2(std::string filename, int top_n);