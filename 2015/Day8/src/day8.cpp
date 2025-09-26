#include <string>
#include <iostream>
#include <fstream>

#define DEBUG false

using namespace std;

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./day8 input.txt\n";
        exit(1);
    }
    ifstream file(argv[1]);
    string line;
    getline(file, line);
    int total_byte_count = 0;
    int in_memory_count = 0;
    int escaped_count = 0;
    while(line.size() > 0)
    {
        if(DEBUG)
        {
            cout << line << " " << line.size() << endl;
        }
        total_byte_count += line.size();
        int i = 1;
        //count in memory
        while(i < line.size() - 1)
        {
            in_memory_count += 1;
            if(line.at(i) == '\\' && i + 1 < line.size() - 1)
            {
                if(line.at(i + 1) == '\"')
                {
                    i += 1;
                }
                else if(line.at(i + 1) == 'x')
                {
                    i += 3;
                }
                else if(line.at(i + 1) == '\\')
                {
                    i += 1;
                }
            }
            i += 1;
        }
        i = 0;
        // count escaped
        escaped_count += 2; // extra two characters for the start and end "
        while(i < line.size())
        {
            escaped_count += 1;
            if(line.at(i) == '\\')
            {
                escaped_count += 1;
            }
            else if(line.at(i) == '\"')
            {
                escaped_count += 1;
            }
            i += 1;
        }
        if(DEBUG)
        {
            cout << in_memory_count << " " << escaped_count << endl;
        }
        getline(file, line);
    }
    file.close();

    cout << "The answer to part 1 is " << total_byte_count - in_memory_count << endl;

    cout << "The answer to part 2 is " << escaped_count - total_byte_count << endl;
}
