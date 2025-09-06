def calculate_wrapping_and_ribbon(input_file):
    total_paper = 0
    total_ribbon = 0
    
    # Read input file
    with open(input_file, 'r') as file:
        for line in file:
            # Parse dimensions
            l, w, h = map(int, line.strip().split('x'))
            
            # Part 1: Wr colère

            # Surface area = 2*l*w + 2*w*h + 2*h*l
            surface_area = 2 * l * w + 2 * w * h + 2 * h * l
            # Smallest side area for slack
            sides = [l * w, w * h, h * l]
            slack = min(sides)
            # Total paper for this present
            total_paper += surface_area + slack
            
            # Part 2: Ribbon
            # Smallest perimeter of any face
            perimeters = [2 * (l + w), 2 * (w + h), 2 * (h + l)]
            ribbon_wrap = min(perimeters)
            # Volume for bow
            bow = l * w * h
            # Total ribbon for this present
            total_ribbon += ribbon_wrap + bow
    
    return total_paper, total_ribbon

# Assume input is in a file named 'input.txt'
input_file = 'input.txt'
paper, ribbon = calculate_wrapping_and_ribbon(input_file)
print(f"Total wrapping paper needed: {paper} square feet")
print(f"Total ribbon needed: {ribbon} feet")

# Verify against provided answers
assert paper == 1606483, f"Expected 1606483 square feet of paper, got {paper}"
assert ribbon == 3842356, f"Expected 3842356 feet of ribbon, got {ribbon}"