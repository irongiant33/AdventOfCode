#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

#define DEBUG(x);

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

    return 0;
}

int part2(std::string filename, int top_n)
{
    // open a file in read mode.
    ifstream infile; 
    infile.open("input.txt"); 

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

    cout << "Part 2: The total of the top 3 elves is ";
    cout << std::to_string(top_total) << endl;

    return 0;
}

int main ()
{
    std::string filename = "input.txt";
    part1(filename);

    int top_three = 3;
    part2(filename, top_three);
}