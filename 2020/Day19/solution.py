#!/usr/bin/python3
"""
This program solves the Day 19 challenge (part 1)
Part 1 Approach:
1. Each rule is an object. The rule will have the following attributes:
- (list) of possible values
- (bool) of whether all the values have been enumerated

2. There is an infinite loop that will loop until the bool of rule 0 is true,
i.e. all of its values have been enumerated

3. Within the infinite loop, there is a loop going through all of the rules
trying to enumerate all of its values. It does so by the following:
- is the number I am trying to replace in the rule dict? if so, then:
	- create N additional values, where N is the number of values in the number
	you are replacing

4. If all of the values have been enumerated, add the rule to the rule dict.

5. Once the while loop has broken, you can just check all of the received
messages to see if they are contained in the possible values of rule 0.

Part 2 Approach:
1. Draw out a couple of possible combinations of what Rule 0 will end up looking
like. Here are some useful cases (I group the rules using parenthesis):

Bare Minimum: 			(42) (42 31)
One Loop for Rule 8: 	(42 (42)) (42 31)
One Loop for Rule 11:   (42) (42 (42 31) 31)
One Loop for each:      (42 (42)) (42 (42 31) 31)
Two Loops for Rule 11:  (42) (42 (42 (42 31) 31) 31)

as you can see there will always be at least 1 more occurrence of 42 than 31.
There will never be an occurence of 42 after 31. There will never be an
occurence of 31 before 42. 31 must occur a minimum of 1 time and 42 must occur
a minimum of 2 times. Only rule 42 and 31 comprise the message.

2. Using the logic above, we can step through every message and determine if the
message substring is in the rule dictionary for 42. If it is, increment a counter.

3. Once a substring is not contained in rule 42, then repeat the step above for
rule 31.

4. Using these counts will help us determine whether the message satisfies the
new rules.
"""

# global imports
from copy import deepcopy
import sys

# global variables
INPUT_FILE_NAME = "input.txt"
RULE_DICT = dict()
ID_SPLITTER = ": "
VALUE_SPLITTER = " | "
DEBUG = False

class Rule():
	"""
	this is the class that contains the attributes and functions for each
	rule
	"""

	def __init__(self, id_num):
		self.id = id_num
		self.values = []
		self.complete = False

	def __repr__(self):
		representation = f"Rule {self.id}: {self.values}"
		return representation


def read_rules(filename):
	"""
	this function reads from input.txt to create all of the empty rules
	@param filename 	  ->  str: name of file to read
	@return rules 		  -> list: list of rule objects
	@return test_messages -> list: list of messages to test whether they fit a
								   rule
	"""
	contents = []
	rules = []
	test_messages = []
	with open(filename) as file_obj:
		contents = file_obj.readlines()
	
	for content in contents:
		stripped_content = content.rstrip()
		if(ID_SPLITTER in stripped_content):
			id_num, values_str = stripped_content.split(ID_SPLITTER)
			values = values_str.split(VALUE_SPLITTER)

			new_rule = Rule(int(id_num))
			if('"' in values[0]):
				new_rule.values.append(values[0][1])
				new_rule.complete = True
				RULE_DICT[new_rule.id] = new_rule.values
			elif('[' in values[0]):
				array_vals = values[0][1:-1]
				str_vals = array_vals.split(", ")
				rule_vals = []
				for val in str_vals:
					new_rule.values.append(val[1:-1])
				RULE_DICT[new_rule.id] = new_rule.values
				new_rule.complete = True
			else:
				for value in values:
					int_values = []
					int_value_strs = value.split()
					for int_value_str in int_value_strs:
						int_values.append(int(int_value_str))
					new_rule.values.append(int_values)
			
			rules.append(new_rule)
		elif(stripped_content):
			test_messages.append(stripped_content)
	
	return (rules, test_messages)


def enumerate_rules(rules):
	"""
	this function contains the while loop to translate all of the rule numbers
	into messages
	@param rules -> list: list of rules to enumerate
	"""
	while(0 not in RULE_DICT):
		rules_not_in_dict = [r for r in rules if r.id not in RULE_DICT]
		for rule in rules_not_in_dict:
			alpha_count = 0
			num_sub_rules = 0
			for value in rule.values:
				for sub_rule_idx in range(len(value)):
					num_sub_rules += 1
					sub_rule = value[sub_rule_idx]
					if(sub_rule in RULE_DICT):
						string_values = RULE_DICT[sub_rule]
						num_string_values = 0
						temp_value = deepcopy(value)
						for string_value in string_values:
							if(0 < num_string_values):
								temp_value[sub_rule_idx] = string_value
								rule.values.append(deepcopy(temp_value))
							else:
								value[sub_rule_idx] = string_value

							num_string_values += 1
					if(str(value[sub_rule_idx]).isalpha()):
						alpha_count += 1
			if(alpha_count == num_sub_rules and rule.id not in RULE_DICT):
				string_values = []
				for value in rule.values:
					string_values.append("".join(value))
				RULE_DICT[rule.id] = string_values

		if(DEBUG):
			print()
			for rule in rules:
				print(rule)
			for key in RULE_DICT:
				print(f"{key}: {RULE_DICT[key]}")
			print()



if __name__ == "__main__":
	rules, messages = read_rules("input.txt")
	
	enumerate_rules(rules)

	#for key in RULE_DICT:
	#	if(key not in [8, 11, 0]):
	#		print(f"{key}: {RULE_DICT[key]}")

	correct_messages = 0
	for message in messages:
		if(message in RULE_DICT[0]):
			correct_messages += 1
	print(f"Part 1: The number of correct messages: {correct_messages}")

	part2_count = 0
	size42 = len(RULE_DICT[42][0])
	size31 = len(RULE_DICT[31][0])
	for message in messages:
		count42 = 0
		count31 = 0
		message_index = 0
		while(message[message_index:(message_index + size42)] in RULE_DICT[42]):
			message_index += size42
			count42 += 1
		while(message[message_index:(message_index + size31)] in RULE_DICT[31]):
			message_index += size31
			count31 += 1
		if(count42 > count31 and message_index == len(message) and count31 > 0):
			part2_count += 1
	
	print(f"Part 2: The number of messages that satisfy the new criteria are: {part2_count}")
