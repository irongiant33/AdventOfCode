#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

struct Present {
    int length, width, height;
};

// Calculate wrapping paper needed for one present
int calculateWrappingPaper(const Present& p) {
    int side1 = p.length * p.width;
    int side2 = p.width * p.height;
    int side3 = p.height * p.length;
    int surfaceArea = 2 * side1 + 2 * side2 + 2 * side3;
    int slack = std::min({side1, side2, side3});
    return surfaceArea + slack;
}

// Calculate ribbon needed for one present
int calculateRibbon(const Present& p) {
    // Smallest perimeter of any face
    int perimeter1 = 2 * (p.length + p.width);
    int perimeter2 = 2 * (p.width + p.height);
    int perimeter3 = 2 * (p.height + p.length);
    int wrap = std::min({perimeter1, perimeter2, perimeter3});
    // Bow is the volume of the present
    int bow = p.length * p.width * p.height;
    return wrap + bow;
}

int main() {
    std::ifstream file("input.txt"); // Assume input is in a file named input.txt
    std::string line;
    std::vector<Present> presents;
    
    // Read input
    while (std::getline(file, line)) {
        int l, w, h;
        char x; // To capture 'x' characters
        std::stringstream ss(line);
        ss >> l >> x >> w >> x >> h;
        presents.push_back({l, w, h});
    }
    
    // Part 1: Calculate total wrapping paper
    long long totalPaper = 0;
    for (const auto& p : presents) {
        totalPaper += calculateWrappingPaper(p);
    }
    
    // Part 2: Calculate total ribbon
    long long totalRibbon = 0;
    for (const auto& p : presents) {
        totalRibbon += calculateRibbon(p);
    }
    
    // Output results
    std::cout << "Total wrapping paper needed: " << totalPaper << " square feet\n";
    std::cout << "Total ribbon needed: " << totalRibbon << " feet\n";
    
    return 0;
}
