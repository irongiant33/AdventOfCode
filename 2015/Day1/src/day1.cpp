#include <iostream>
#include <fstream>

using namespace std;
int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "usage: ./day1 input.txt" << endl;
        exit(1);
    }
    
    int floor = 0;
    unsigned int command_counter = 0;
    unsigned int basement_position = 0;
    char command;
    ifstream file(argv[1]);

    // read from the input file character by character to keep
    // track of Santa's floor
    while(file >> command)
    {
        command_counter += 1;
        if(command == '(')
        {
            floor += 1;
        }
        else if(command == ')')
        {
            floor -= 1;
        }
        if(basement_position == 0 && floor < 0) //only set basement_position once
        {
            basement_position = command_counter;
        }
   }
   file.close();

   cout << "Part 1 answer is " << floor << endl;
   cout << "Part 2 answer is " << basement_position << endl; 
}
