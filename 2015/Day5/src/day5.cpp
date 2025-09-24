#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define DEBUG false
#define NUM_VOWELS 5

using namespace std;

int count(string haystack, char needle)
{
    int num_occurences = 0;
    int index = haystack.find(needle);
    while(index != haystack.npos && index < haystack.size())
    {
        num_occurences++;
        index = haystack.find(needle, index + 1);
    }
    return num_occurences;
}

int part1(vector <string> lines)
{
    int num_nice = 0;
    char vowels[NUM_VOWELS] = {'a', 'e', 'i', 'o', 'u'}; 
    for(string line : lines)
    {
        //condition 1
        int vowel_count = 0;
        for(int i = 0; i < NUM_VOWELS; i++)
        {
            vowel_count += count(line, vowels[i]);
        }
        //condition 2
        bool has_consecutive_chars = false;
        char last_char = '\0';
        for(int i = 0; i < line.size(); i++)
        {
            if(line.at(i) == last_char)
            {
                has_consecutive_chars = true;
                break;
            }
            last_char = line.at(i);
        }
        //condition 3
        bool has_bad_strings = false;
        string bad_strings[4] = {"ab", "cd", "pq", "xy"};
        for(string bad_string : bad_strings)
        {
            if(line.find(bad_string) != line.npos)
            {
                has_bad_strings = true;
                break;
            }
        }
        if(DEBUG)
        {
            cout << line << " : " << has_bad_strings << has_consecutive_chars << vowel_count << endl;
        }
        if(!has_bad_strings && has_consecutive_chars && vowel_count >= 3)
        {
            num_nice++;
        }
    }
    return num_nice;
}

int part2(vector <string> lines)
{
    int num_nice = 0;
    for(string line : lines)
    {
        //condition 1
        bool has_multiple_nonconsecutive = false;
        for(int i = 0; i < line.size() - 3; i++)
        {
            string first_pair = line.substr(i, 2);
            for(int j = i + 2; j < line.size() - 1; j++)
            {
                string second_pair = line.substr(j, 2);
                if(first_pair == second_pair)
                {
                    has_multiple_nonconsecutive = true;
                    break;
                }
            } 
            if(has_multiple_nonconsecutive)
            {
                break;
            }
        }
        //condition 2
        bool has_sandwich_letters = false;
        for(int i = 0; i < line.size() - 2; i++)
        {
            if(line.at(i) == line.at(i + 2))
            {
                has_sandwich_letters = true;
                break;
            }
        }
        if(DEBUG)
        {
            cout << line << " : " << has_sandwich_letters << has_multiple_nonconsecutive << endl;
        }
        if(has_sandwich_letters && has_multiple_nonconsecutive)
        {
            num_nice++;
        }
    }
    return num_nice;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./day5 input.txt\n";
        exit(1);
    }
    ifstream file(argv[1]);
    vector <string> lines;
    string line;
    getline(file, line);
    while(line.size() > 0)
    {
        lines.push_back(line);
        getline(file, line);
    } 
    file.close();

    //part 1
    int ret_val = part1(lines);
    cout << "The answer to part 1 is " << ret_val << endl;

    //part 2
    ret_val = part2(lines);
    cout << "The answer to part 2 is " << ret_val << endl;
}
