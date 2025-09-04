#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Read input from file
    std::ifstream file("input.txt");
    std::string instructions;
    if (file.is_open()) {
        std::getline(file, instructions);
        file.close();
    } else {
        std::cerr << "Unable to open input file\n";
        return 1;
    }

    // Part 1: Calculate final floor
    int floor = 0;
    for (char c : instructions) {
        if (c == '(') {
            floor++;
        } else if (c == ')') {
            floor--;
        }
    }

    // Part 2: Find position of first basement entry
    int position = 0;
    int current_floor = 0;
    for (size_t i = 0; i < instructions.length(); ++i) {
        if (instructions[i] == '(') {
            current_floor++;
        } else if (instructions[i] == ')') {
            current_floor--;
        }
        if (current_floor == -1) {
            position = i + 1; // 1-based indexing
            break;
        }
    }

    // Output results
    std::cout << "Part 1: Final floor = " << floor << "\n";
    std::cout << "Part 2: First basement position = " << position << "\n";

    return 0;
}
