#include <iostream>
#include <algorithm>
#include <compare>
#include <functional>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <set>
#include <map>
#include <utility>

#define DEBUG false

using namespace std;


int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./day9 testinput.txt\n";
    }
    regex pattern("(\\w+) to (\\w+) = (\\d+)");
    smatch matches;
    ifstream file(argv[1]);
    string line;
    set <string> city_names;
    map <string, vector<pair<string, int>>> cities;
    pair<map<string, vector<pair<string, int>>>::iterator, bool> map_state;
    getline(file, line);
    // parse file and build list of cities and their neighbors
    while(line.size() > 0)
    {
        regex_match(line, matches, pattern);
        if(DEBUG)
        {
            cout << matches[0].str() << "//" << matches[1].str() << "//" << matches[2].str() << "//" << matches[3].str() << endl;
        }
        pair<string, int> first_pair  = {matches[2].str(), stoi(matches[3].str())}; //first city's neighbors
        pair<string, int> second_pair = {matches[1].str(), stoi(matches[3].str())}; //second city's neighbors
        city_names.insert(matches[1].str());
        city_names.insert(matches[2].str());
        vector<pair<string, int>> first_neighbors  = {first_pair}; //first cities neighbors
        vector<pair<string, int>> second_neighbors = {second_pair}; //second city's neighbors
        map_state = cities.insert({matches[1].str(), first_neighbors});
        if(!map_state.second)
        {
            map_state.first->second.push_back(first_pair);
        }
        map_state = cities.insert({matches[2].str(), second_neighbors});
        if(!map_state.second)
        {
            map_state.first->second.push_back(second_pair);
        }
        getline(file, line);
    }
    file.close();

    // debug print to verify list of cities and neighbors
    if(DEBUG)
    {
        for(map<string, vector<pair<string, int>>>::iterator it = cities.begin(); it != cities.end(); it++)
        {
            cout << it->first << ": [";
            for(pair<string, int> my_pair : it->second)
            {
                cout << my_pair.first << ":" << my_pair.second << ", ";
            }
            cout << "]\n";
        }
    }

    // find min and max paths
    int max_cost = -1;
    int min_cost = 99999;

    vector<string> city_strings;
    for(map<string, vector<pair<string, int>>>::iterator it = cities.begin(); it != cities.end(); it++)
    {
        city_strings.push_back(it->first);
    }
    do
    {
        int cost = 0;
        if(DEBUG)
        {
            for(string a : city_strings)
            {
                cout << a << ", ";
            }
            cout << endl;
        }
        for(int i = 0; i < city_strings.size() - 1; i++)
        {
            vector<pair<string, int>> neighbors = cities[city_strings[i]];
            for(pair<string, int> neighbor : neighbors)
            {
                if(neighbor.first == city_strings[i + 1])
                {
                    cost += neighbor.second;
                    break;
                }
            }
        }
        if(cost < min_cost)
        {
            min_cost = cost;
        }
        if(cost > max_cost)
        {
            max_cost = cost;
        }
    }
    while(next_permutation(city_strings.begin(), city_strings.end()));

    cout << "The min cost (part 1) is " << min_cost << endl;
    cout << "The max cost (part 2) is " << max_cost << endl;
}
