#include <iostream>
#include <fstream>
#include <string>
#include <deque>

#define SUCCESS 0
#define FAILURE 1
#define DEBUG false

using namespace std;

void string_to_int(string line, int * dimensions)
{
	// convert string to int
	int start_pos = 0;
	int last_pos = 0;
	if(DEBUG)
	{
		cout << "Input: " << line << " ";
	}
	for(int i = 0; i < 2; i++)
	{
		last_pos = line.find("x", start_pos);
		dimensions[i] = stoi(line.substr(start_pos, last_pos - start_pos));
		start_pos = last_pos + 1;
		if(DEBUG)
		{
			cout << dimensions[i] << " ";
		}
	}
	dimensions[2] = stoi(line.substr(start_pos));
	if(DEBUG)
	{
		cout << dimensions[2] << endl;
	}
}

int calculate_ribbon_length(deque <string> * input_lines)
{
	int ribbon_length = 0;
	for(string line : *input_lines)
	{
		// string to int
		int dimensions[3] = {0};
		string_to_int(line, dimensions);

		// find smallest perimeter
		int min_perimeter = 99999; //arbitrarily high value
		int perimeter = 0;
		for(int i = 0; i < 3; i++)
		{
			perimeter = dimensions[i] * 2 + dimensions[(i + 1) % 3] * 2;
			if(perimeter < min_perimeter)
			{
				min_perimeter = perimeter;
			}
			if(DEBUG)
			{
				cout << perimeter << " ";
			}
		}
		if(DEBUG)
		{
			cout << "min perimeter: " << min_perimeter << endl;
		}
		int added_length = min_perimeter + dimensions[0] * dimensions[1] * dimensions[2];
		if(DEBUG)
		{
			cout << "added length: " << added_length << endl;
		}
		ribbon_length += added_length;
	}
	return ribbon_length;
}

/*
 * Calculates square footage the elves require and returns it
 */
int calculate_square_footage(deque <string> * input_lines)
{
	int square_footage_sum = 0;
	for(string line : *input_lines)
	{
		// convert string to int
		int dimensions[3] = {0};
		string_to_int(line, dimensions);

		// calculate square footage
		int surface_areas[3] = {0};
		int sum_surface_areas = 0;
		int min_surface_area = 999999; //arbitrarily high surface area
		for(int i = 0; i < 3; i++)
		{
			surface_areas[i] = dimensions[i] * dimensions[(i + 1) % 3];
			if(surface_areas[i] < min_surface_area)
			{
				min_surface_area = surface_areas[i];
			}
			sum_surface_areas += surface_areas[i] * 2;
			if(DEBUG)
			{
				cout << surface_areas[i] << " ";
			}
		}
		if(DEBUG)
		{
			cout << "min: " << min_surface_area << endl;
		}
		// add smallest area and return
		square_footage_sum += sum_surface_areas + min_surface_area;
	}
	return square_footage_sum;
}

/*
 * Tests program functionality on limited input
 *
 * returns 0 on success and nonzero on failure
 *
 */
int test_square_footage()
{
	// calculate the known input
	deque <string> test_input = {"1x17x21", "21x21x27"};
	int test_answers[2]   = {2*(1*17 + 17*21 + 21*1) + 1*17, 2*(21*21 + 21*27 + 27*21) + 21*21};
	int sum_test_answers = test_answers[0] + test_answers[1];

	// determine your answer
	int my_answer = calculate_square_footage(&test_input);

	// test known input answer against your answer
	if(sum_test_answers == my_answer)
	{
		return SUCCESS;
	}
	else
	{
		cout << "Actual answer does not match expected.\n";
		cout << "Actual: " << my_answer << " Expected: " << sum_test_answers << endl;
		return FAILURE;
	}
}

int test_ribbon_length()
{
	deque <string> test_string = {"2x3x4", "1x1x10"};
	int my_length = calculate_ribbon_length(&test_string);
	int answer = (10 + 24) + (4 + 10);
	if(my_length == answer)
	{
		return SUCCESS;
	}
	else
	{
		cout << "Your answer: " << my_length << " expected: " << answer << endl;
		return FAILURE;
	}
}

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		cout << "Usage: ./day2 input.txt\n";
		return 1;
	}
	int retval = test_square_footage();
	if(DEBUG && retval == FAILURE)
	{
		cout << "test failed!\n";
	}
	else if(DEBUG && retval == SUCCESS)
	{
		cout << "test passed.\n";
	}
	ifstream file(argv[1]);
	deque <string> * input_lines = new deque<string>;
	string line = "";
	getline(file, line, '\n');
	if(DEBUG)
	{
		cout << "First line: " << line << endl;
	}
	while(line.size() > 0)
	{
		input_lines->push_back(line);
		getline(file, line, '\n');
	}
	if(DEBUG)
	{
		cout << "testing square footage\n";
	}
	int square_footage = calculate_square_footage(input_lines);
	cout << "The answer to part 1 is " << square_footage << " sq ft" << endl;
	retval = test_ribbon_length();
	int ribbon_length = calculate_ribbon_length(input_lines);
	cout << "The answer to part 2 is " << ribbon_length << " ft" << endl;
	file.close();
	delete input_lines;
	input_lines = nullptr;
	return 0;
}
