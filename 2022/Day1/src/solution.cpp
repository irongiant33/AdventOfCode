#include "solution.hpp"
using namespace std;

#define DEBUG(x);

/*
@brief solve part 1 of advent of code

@param filename: file to read the input from

@return max_calories: maximum number of calories an elf is carrying
*/
int part1(std::string filename)
{
    // open a file in read mode.
    ifstream infile; 
    infile.open(filename); 

    int elf_calories[1000];
    int max_calories = 0;
    int elf_index = 0;
    int calories = 0;
    while(infile)
    {
        std::string str_input;
        std::getline(infile, str_input);

        if("" == str_input)
        {
            if(calories > max_calories)
            {
                max_calories = calories;
            }
            elf_calories[elf_index] = calories;
            DEBUG("Elf #" << std::to_string(elf_index) << ": ");
            DEBUG(std::to_string(calories) << endl);
            elf_index++;
            calories = 0;
        }
        else
        {
            calories += std::stoi(str_input);
        }
    } 

    // close the opened file.
    infile.close();

    cout << "Part 1: The maximum number of calories carried by an elf is ";
    cout << std::to_string(max_calories) << endl;

    return max_calories;
}

/*
@brief solve part 2 of advent of code

@param filename: filename to read input from
@param top_n: number of elves from which to create the sum. Should be less than the total number of elves.

@return top_total: total number of calories for the top_n elves
*/
int part2(std::string filename, int top_n)
{
    // open a file in read mode.
    ifstream infile; 
    infile.open(filename); 

    int num_elves = 1000;
    int elf_calories[num_elves];
    int elf_index = 0;
    int calories = 0;
    while(infile)
    {
        std::string str_input;
        std::getline(infile, str_input);

        if("" == str_input)
        {
            elf_calories[elf_index] = calories;
            DEBUG("Elf #" << std::to_string(elf_index) << ": ");
            DEBUG(std::to_string(calories) << endl);
            elf_index++;
            calories = 0;
        }
        else
        {
            calories += std::stoi(str_input);
        }
    } 

    // close the opened file.
    infile.close();

    std::sort(elf_calories, elf_calories + elf_index);

    int top_total = 0;
    for(int i = (elf_index - 1); i > (elf_index - 1 - top_n); i--)
    {
        top_total += elf_calories[i];
    }

    cout << "Part 2: The total of the top " << std::to_string(top_n) << " elves is ";
    cout << std::to_string(top_total) << endl;

    return top_total;
}

int main ()
{
    std::string filename = "input.txt";
    part1(filename);

    int top_three = 3;
    part2(filename, top_three);
}