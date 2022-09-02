# Problem Solving Approach

## Part 1

1. Use space and newline as a delimiter. Assume that the command is the first value on every line and the value is the second and that there are always 2 values.
2. Initialize x position and depth to 0
3. For each command:
    1. If you receive a forward command, add its value to the current x position
    2. If you receive a up command, subtract its value from the depth
    3. If you recieve a down command, add its value to the depth
4. Multiply the depth by the x position

## Part 2

1. Use space and newline as a delimiter. Assume that the command is the first value on every line and the value is the second and that there are always 2 values.
2. Initialize x position, aim, and depth to 0
3. For each command:
    1. If you receive a forward command:
        1. add its value to the current x position
        2. add the aim multiplied by its value to the depth
    2. If you receive a up command, subtract its value from the aim
    3. If you recieve a down command, add its value to the aim
4. Multiply the depth by the x position