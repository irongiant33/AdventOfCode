#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

struct Instruction {
    std::string action;
    int x1, y1, x2, y2;
};

std::vector<Instruction> parse_instructions(const std::string& filename) {
    std::vector<Instruction> instructions;
    std::ifstream file(filename);
    std::string line;
    std::regex pattern("(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");
    
    while (std::getline(file, line)) {
        std::smatch matches;
        if (std::regex_match(line, matches, pattern)) {
            Instruction inst;
            inst.action = matches[1].str();
            inst.x1 = std::stoi(matches[2].str());
            inst.y1 = std::stoi(matches[3].str());
            inst.x2 = std::stoi(matches[4].str());
            inst.y2 = std::stoi(matches[5].str());
            instructions.push_back(inst);
        }
    }
    return instructions;
}

long long part1(const std::vector<Instruction>& instructions) {
    std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000, false));
    for (const auto& inst : instructions) {
        for (int i = inst.x1; i <= inst.x2; ++i) {
            for (int j = inst.y1; j <= inst.y2; ++j) {
                if (inst.action == "turn on") {
                    grid[i][j] = true;
                } else if (inst.action == "turn off") {
                    grid[i][j] = false;
                } else { // toggle
                    grid[i][j] = !grid[i][j];
                }
            }
        }
    }
    long long count = 0;
    for (const auto& row : grid) {
        for (bool light : row) {
            if (light) ++count;
        }
    }
    return count;
}

long long part2(const std::vector<Instruction>& instructions) {
    std::vector<std::vector<int>> grid(1000, std::vector<int>(1000, 0));
    for (const auto& inst : instructions) {
        for (int i = inst.x1; i <= inst.x2; ++i) {
            for (int j = inst.y1; j <= inst.y2; ++j) {
                if (inst.action == "turn on") {
                    grid[i][j] += 1;
                } else if (inst.action == "turn off") {
                    grid[i][j] = std::max(0, grid[i][j] - 1);
                } else { // toggle
                    grid[i][j] += 2;
                }
            }
        }
    }
    long long total = 0;
    for (const auto& row : grid) {
        for (int brightness : row) {
            total += brightness;
        }
    }
    return total;
}

int main() {
    auto instructions = parse_instructions("input.txt");
    std::cout << "Part 1: " << part1(instructions) << std::endl; // Expected: 569999
    std::cout << "Part 2: " << part2(instructions) << std::endl; // Expected: 17836115
    return 0;
}