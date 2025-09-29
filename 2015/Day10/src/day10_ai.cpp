#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

std::string look_and_say_regex(const std::string& sequence) {
    // Use regex to split into groups of consecutive identical digits
    std::regex pattern("((.)\\2*)");
    std::vector<std::string> groups;
    std::sregex_iterator it(sequence.begin(), sequence.end(), pattern);
    std::sregex_iterator end;
    
    while (it != end) {
        groups.push_back(it->str(1)); // Capture group 1 (full run of digits)
        ++it;
    }
    
    // Generate the next sequence
    std::string result;
    for (const auto& group : groups) {
        result += std::to_string(group.length()) + group[0];
    }
    return result;
}

std::string look_and_say_manual(const std::string& sequence) {
    // Manual counting of consecutive digits
    std::string result;
    size_t count = 1;
    char current_digit = sequence[0];
    
    for (size_t i = 1; i < sequence.length(); ++i) {
        if (sequence[i] == current_digit) {
            ++count;
        } else {
            result += std::to_string(count) + current_digit;
            current_digit = sequence[i];
            count = 1;
        }
    }
    result += std::to_string(count) + current_digit;
    
    return result;
}

int look_and_say_n_times(const std::string& file_path, int iterations, bool use_regex = true) {
    // Read the initial sequence from input.txt
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << file_path << std::endl;
        return 0;
    }
    
    std::string sequence;
    std::getline(file, sequence);
    file.close();
    
    if (sequence.empty()) {
        std::cerr << "Error: Empty input string" << std::endl;
        return 0;
    }
    
    // Apply look-and-say process for the specified number of iterations
    for (int i = 0; i < iterations; ++i) {
        sequence = use_regex ? look_and_say_regex(sequence) : look_and_say_manual(sequence);
    }
    
    return sequence.length();
}

int main() {
    std::string file_path = "input.txt";
    
    // Part 1: 40 iterations
    int part1_length = look_and_say_n_times(file_path, 40, true); // Use regex by default
    std::cout << "Part 1 - Length after 40 iterations: " << part1_length << std::endl;
    
    // Part 2: 50 iterations
    int part2_length = look_and_say_n_times(file_path, 50, true);
    std::cout << "Part 2 - Length after 50 iterations: " << part2_length << std::endl;
    
    return 0;
}