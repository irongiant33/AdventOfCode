#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

// Parse input from file into a distance map and list of cities
pair<map<pair<string, string>, int>, vector<string>> parse_distances(const string& file_path) {
    map<pair<string, string>, int> distances;
    set<string> cities;
    ifstream file(file_path);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open input.txt" << endl;
        exit(1);
    }

    while (getline(file, line)) {
        string city1, city2, to;
        int distance;
        stringstream ls(line);
        if (ls >> city1 >> to >> city2 >> to >> distance) {
            cities.insert(city1);
            cities.insert(city2);
            distances[{city1, city2}] = distance;
            distances[{city2, city1}] = distance; // Undirected graph
        }
    }

    file.close();
    vector<string> city_list(cities.begin(), cities.end());
    return {distances, city_list};
}

// Compute shortest and longest TSP routes
pair<int, int> tsp_shortest_longest(const string& file_path) {
    auto [distances, cities] = parse_distances(file_path);
    int n = cities.size();
    vector<int> indices(n);
    for (int i = 0; i < n; ++i) indices[i] = i;

    int min_distance = INT_MAX;
    int max_distance = INT_MIN;

    do {
        int total_distance = 0;
        bool valid = true;
        for (int i = 0; i < n - 1; ++i) {
            string city1 = cities[indices[i]];
            string city2 = cities[indices[i + 1]];
            auto edge = distances.find({city1, city2});
            if (edge == distances.end()) {
                valid = false;
                break;
            }
            total_distance += edge->second;
        }
        if (valid) {
            min_distance = min(min_distance, total_distance);
            max_distance = max(max_distance, total_distance);
        }
    } while (next_permutation(indices.begin(), indices.end()));

    return {min_distance, max_distance};
}

int main() {
    auto [shortest, longest] = tsp_shortest_longest("input.txt");
    cout << "Part 1 - Shortest route: " << shortest << endl;
    cout << "Part 2 - Longest route: " << longest << endl;

    return 0;
}