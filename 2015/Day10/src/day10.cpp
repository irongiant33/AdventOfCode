#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

#define DEBUG false

using namespace std;

int solve_puzzle(int num_loops, string input_string)
{
    for(int loop_index = 0; loop_index < num_loops; loop_index++)
    {
        ostringstream output_string;
        int count = 1;
        int i;
        char prev_char = input_string.at(0);
        for(i = 1; i < input_string.size(); i++)
        {
            if(input_string.at(i) != prev_char)
            {
                output_string << count << prev_char;
                prev_char = input_string.at(i);
                count = 1;
            }
            else
            {
                count++;
            }
        }
        output_string << count << input_string.at(i - 1);
        input_string = output_string.str();
        if(DEBUG)
        {
            cout << "Loop " << loop_index << ": Output string " << input_string << endl;
        }
    }
    return input_string.size();
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./day10 input.txt\n";
    }
    ifstream file(argv[1]);
    string line;
    getline(file, line);
    if(DEBUG)
    {
        cout << "The input is " << line << endl;
    }
    file.close();
    if(DEBUG)
    {
        int test_result = solve_puzzle(10, line);
        cout << "The test result is " << test_result << endl;
    }
    int part1_result = solve_puzzle(40, line);
    cout << "The answer to part 1 is " << part1_result << endl;
    int part2_result = solve_puzzle(50, line);
    cout << "The answer to part 2 is " << part2_result << endl;
}
