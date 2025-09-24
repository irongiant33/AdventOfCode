#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

bool is_nice_part1(const std::string& s) {
    int vowel_count = 0;
    bool has_double = false;
    std::unordered_set<std::string> forbidden = {"ab", "cd", "pq", "xy"};
    
    // Check for forbidden substrings
    for (size_t i = 0; i < s.length() - 1; ++i) {
        if (forbidden.count(s.substr(i, 2)) > 0) {
            return false;
        }
    }
    
    // Count vowels and check for double letters
    for (size_t i = 0; i < s.length(); ++i) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
            ++vowel_count;
        }
        if (i < s.length() - 1 && s[i] == s[i + 1]) {
            has_double = true;
        }
    }
    
    return vowel_count >= 3 && has_double;
}

bool is_nice_part2(const std::string& s) {
    bool has_pair = false;
    bool has_repeat = false;
    
    // Check for pair of two letters appearing twice without overlapping
    for (size_t i = 0; i < s.length() - 1 && !has_pair; ++i) {
        std::string pair = s.substr(i, 2);
        // Look for this pair in the rest of the string
        for (size_t j = i + 2; j < s.length() - 1; ++j) {
            if (s.substr(j, 2) == pair) {
                has_pair = true;
                break;
            }
        }
    }
    
    // Check for letter repeating with one letter between
    for (size_t i = 0; i < s.length() - 2; ++i) {
        if (s[i] == s[i + 2]) {
            has_repeat = true;
            break;
        }
    }
    
    return has_pair && has_repeat;
}

int main() {
    std::ifstream file("input.txt");
    if (!file) {
        std::cerr << "Cannot open input.txt" << std::endl;
        return 1;
    }
    
    std::vector<std::string> strings;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            strings.push_back(line);
        }
    }
    file.close();
    
    // Part 1
    int nice_count_part1 = 0;
    for (const auto& s : strings) {
        if (is_nice_part1(s)) {
            ++nice_count_part1;
        }
    }
    
    // Part 2
    int nice_count_part2 = 0;
    for (const auto& s : strings) {
        if (is_nice_part2(s)) {
            ++nice_count_part2;
        }
    }
    
    std::cout << "Part 1: " << nice_count_part1 << std::endl; // Expected: 255
    std::cout << "Part 2: " << nice_count_part2 << std::endl; // Expected: 55
    
    return 0;
}