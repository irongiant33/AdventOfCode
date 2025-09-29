from itertools import permutations

def parse_distances(file_path):
    # Initialize distance dictionary
    distances = {}
    cities = set()
    
    # Read from input.txt
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) != 5 or parts[1] != 'to' or parts[3] != '=':
                continue  # Skip malformed lines
            city1, city2, distance = parts[0], parts[2], int(parts[4])
            cities.add(city1)
            cities.add(city2)
            distances[(city1, city2)] = distance
            distances[(city2, city1)] = distance  # Undirected graph
    
    return distances, list(cities)

def tsp_shortest_longest(file_path):
    distances, cities = parse_distances(file_path)
    n = len(cities)
    
    # Get all possible permutations of cities
    min_distance = float('inf')
    max_distance = float('-inf')
    
    for perm in permutations(cities):
        total_distance = 0
        valid = True
        # Calculate total distance for the permutation
        for i in range(n-1):
            if (perm[i], perm[i+1]) not in distances:
                valid = False
                break
            total_distance += distances[(perm[i], perm[i+1])]
        
        if valid:
            min_distance = min(min_distance, total_distance)
            max_distance = max(max_distance, total_distance)
    
    return min_distance, max_distance

# Read from input.txt and compute results
shortest, longest = tsp_shortest_longest('input.txt')
print(f"Part 1 - Shortest route: {shortest}")
print(f"Part 2 - Longest route: {longest}")