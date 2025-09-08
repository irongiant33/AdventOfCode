#include <iostream>
#include <fstream>
#include <set>
#include <string>

using namespace std;

// Use pair<int, int> to represent (x, y) coordinates
using Point = pair<int, int>;

void countHouses(const string& directions, int& part1, int& part2) {
    // Part 1: Santa's unique houses
    set<Point> houses1;
    // Part 2: Santa and Robo-Santa's unique houses
    set<Point> houses2;
    
    // Starting position (0,0) for both parts
    Point santa1 = {0, 0};
    houses1.insert(santa1); // Santa delivers to starting house
    
    Point santa2 = {0, 0}, roboSanta = {0, 0};
    houses2.insert(santa2); // Both deliver to starting house
    
    // Process directions
    for (size_t i = 0; i < directions.length(); ++i) {
        // Part 1: Santa moves
        char dir = directions[i];
        if (dir == '^') santa1.second++; // North
        else if (dir == 'v') santa1.second--; // South
        else if (dir == '>') santa1.first++; // East
        else if (dir == '<') santa1.first--; // West
        houses1.insert(santa1);
        
        // Part 2: Santa and Robo-Santa alternate moves
        Point& mover = (i % 2 == 0) ? santa2 : roboSanta;
        if (dir == '^') mover.second++;
        else if (dir == 'v') mover.second--;
        else if (dir == '>') mover.first++;
        else if (dir == '<') mover.first--;
        houses2.insert(mover);
    }
    
    part1 = houses1.size();
    part2 = houses2.size();
}

int main() {
    // Read input from file
    ifstream file("input.txt");
    string directions;
    if (file.is_open()) {
        getline(file, directions);
        file.close();
    } else {
        cerr << "Unable to open input file" << endl;
        return 1;
    }
    
    int part1, part2;
    countHouses(directions, part1, part2);
    
    cout << "Part 1: Houses with at least one present: " << part1 << endl;
    cout << "Part 2: Houses with at least one present: " << part2 << endl;
    
    // Verify against provided answers
    if (part1 != 2565) {
        cerr << "Part 1: Expected 2565, got " << part1 << endl;
    }
    if (part2 != 2639) {
        cerr << "Part 2: Expected 2639, got " << part2 << endl;
    }
    
    return 0;
}