#include <iostream>
#include <set>
#include <fstream>
#include <utility> 


using namespace std;

int day3_solver(ifstream * file, bool is_robot)
{
    char command;
    pair <int, int> santa_pos = make_pair(0, 0);
    pair <int, int> robot_pos = make_pair(0, 0);
    set < pair<int, int> > visited = {santa_pos};
    int counter = 0;
    while(*file >> command)
    {
        pair<int, int> pos = make_pair(get<0>(santa_pos), get<1>(santa_pos));
        if(is_robot && counter % 2 != 0)
        {
            pos = make_pair(get<0>(robot_pos), robot_pos.second);
        }
        switch(command)
        {
            case 'v':
                pos = make_pair(get<0>(pos), get<1>(pos) + 1); 
                break;
            case '<':
                pos = make_pair(get<0>(pos) - 1, get<1>(pos));
                break;
            case '^':
                pos = make_pair(get<0>(pos), get<1>(pos) - 1);
                break;
            case '>':
                pos = make_pair(get<0>(pos) + 1, get<1>(pos));
                break;
            default:
                cout << "unknown command: " << command << endl;
                break;
        }
        visited.insert(pos);
        if(is_robot && counter % 2 != 0)
        {
            robot_pos = make_pair(get<0>(pos), get<1>(pos));
        }
        else
        {
            santa_pos = make_pair(get<0>(pos), get<1>(pos));
        }
        counter++;
   }
   return visited.size(); 
}


int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Usage: ./day3 input.txt\n";
        exit(1);
    }
    ifstream file(argv[1]);
    int part1_ans = day3_solver(&file, false);
    cout << "The answer to part 1 is " << part1_ans << endl;
    file.close();
    file.open(argv[1]);
    int part2_ans = day3_solver(&file, true);
    cout << "The answer to part 2 is " << part2_ans << endl;
    file.close();
    return 0;
}
