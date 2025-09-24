#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

#define DEBUG false
#define NUM_KEYWORDS 3
#define GRID_SIZE 1000

using namespace std;

int count_lights(vector <int> commands, vector < pair <int, int> > coords, int (*funcs[NUM_KEYWORDS])(int val))
{
    //check to make sure sizes are appropriate
    if(commands.size()*2 != coords.size())
    {
       cout << "Mismatch in sizes of commands vector and coords vector\n";
       cout << "commands: " << commands.size() << " coords: " << coords.size() << endl;
       return -1;
    }
    
    // solve
    int grid[GRID_SIZE][GRID_SIZE] = {0};
    if(DEBUG)
    {
        for(int i = 0; i < GRID_SIZE; i++)
        {
            for(int j = 0; j < GRID_SIZE; j++)
            {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Should see 0 1 0 follow this\n";
        cout << funcs[0](1) << " " << funcs[1](0) << " " << funcs[2](1) << endl;
    }
    int coords_index = 0;
    for(vector<int>::iterator it = commands.begin(); it != commands.end(); it++)
    {
        pair <int, int> start_coord = coords[coords_index];
        pair <int, int> end_coord = coords[coords_index + 1];
        coords_index += 2;
        if(DEBUG)
        {
            cout << *it << " from " << start_coord.first << " to " << end_coord.first << endl;
            cout << "and from " << start_coord.second << " to " << end_coord.second << endl;
        }
        for(int i = start_coord.first; i <= end_coord.first; i++)
        {
            for(int j = start_coord.second; j <= end_coord.second; j++)
            {
                int result = funcs[*it](grid[i][j]);
                if(DEBUG)
                {
                    cout << grid[i][j] << " on " << *it << " is: " << result << endl;
                }
                grid[i][j] = result;
            }
        }
        if(DEBUG)
        {
            for(int i = 0; i < GRID_SIZE; i++)
            {
                for(int j = 0; j < GRID_SIZE; j++)
                {
                    cout << grid[i][j] << " ";
                }
                cout << endl;
            }
        }
    }
    int num_lights = 0;
    for(int i = 0; i < GRID_SIZE; i++)
    {
        for(int j = 0; j < GRID_SIZE; j++)
        {
            num_lights += grid[i][j];
        }
    }
    return num_lights;
}

int toggle_part1(int val)
{
    return val ^ 1;
}

int on_part1(int val)
{
    return val | 1;
}

int off_part1(int val)
{
    return val & 0;
}

int toggle_part2(int val)
{
    return val + 2;
}

int on_part2(int val)
{
    return val + 1;
}

int off_part2(int val)
{
    int result = val - 1;
    if(result < 0)
    {
        return 0;
    }
    return result;
}

int main(int argc, char * argv[])
{
    // parse file contents into vector
    if(argc != 2)
    {
        cout << "Usage: ./day6 input.txt\n";
        exit(1);
    }
    ifstream file(argv[1]);
    regex pattern("\\d+,\\d+");
    string keywords[NUM_KEYWORDS] = {"toggle", "on", "off"};
    vector < int > commands;
    vector < pair<int, int> > coords; //even indexes is start, odd indexes are end coord
    string line = "default";
    while(line.size() > 0)
    {
        getline(file, line);
        for(int i = 0; i < NUM_KEYWORDS; i++)
        {
            if(line.find(keywords[i]) != line.npos)
            {
                commands.push_back(i);
                break;
            }
        }
        for(sregex_iterator it(line.begin(), line.end(), pattern); it != sregex_iterator(); it++)
        {
            smatch match = *it;
            string coord_string(match.str());
            int delimiter_index = coord_string.find(",");
            pair<int, int> coord = {stoi(coord_string.substr(0, delimiter_index)), stoi(coord_string.substr(delimiter_index + 1, coord_string.size() - delimiter_index))};
            coords.push_back(coord);
        }
        if(DEBUG)
        {
            for(int m : commands)
            {
                cout << m << endl;
            }
            for(pair<int, int> m : coords)
            {
                cout << m.first << "," << m.second << endl;
            }
        }
    }
    file.close();

    //handle part 1
    int (*funcs[NUM_KEYWORDS])(int val) = {&toggle_part1, &on_part1, &off_part1};
    int ret_val = count_lights(commands, coords, funcs);
    cout << "The answer to part 1 is " << ret_val << endl;

    //handle part 2
    int (*part2_funcs[NUM_KEYWORDS])(int val) = {&toggle_part2, &on_part2, &off_part2};
    ret_val = count_lights(commands, coords, part2_funcs);
    cout << "The answer to part 2 is " << ret_val << endl;
}
