INPUT_FILE_NAME = "input.txt"
VALID_FIELDS = ["byr","iyr","eyr","hgt","hcl","ecl","pid"]
EXCEPTION = "cid"
HAIR_LIST = '0123456789abcdef'
EYE_LIST = ['amb','blu','brn','gry','grn','hzl','oth']
PROBLEM_PART = 2 #change to 1 if you want answer to part 1

import re

def get_input_list():
	input_file = open(INPUT_FILE_NAME,"r")
	input_file_list = []
	passport = {}
	for line in input_file:
		if(line == '\n'):
				input_file_list.append(passport)
				passport = {}
				continue
		
		# remove \n if it exists
		if(line[len(line) - 1] == '\n'):
			line = line[0:(len(line)-1)] 
			
		line_parameters = line.split(" ")
		for parameter in line_parameters:
			[key,value] = parameter.split(":")
			passport[key] = value
	
	input_file_list.append(passport)
		
	input_file.close()
	return input_file_list
	
def check_fields(passport):
	num_check = 0
	
	if(re.match('^((1\d[2-9]\d)|(200[0-2]))$',passport["byr"]) is not None):
		num_check = num_check + 1
	if(re.match('^((201\d)|(2020))$',passport["iyr"]) is not None):
		num_check = num_check + 1
	if(re.match('^((202\d)|(2030))$',passport["eyr"]) is not None):
		num_check = num_check + 1
	if(re.match('^((1[5-8]\dcm)|(19[0-3]cm)|(59in)|(6\din)|(7[0-6]in))$',passport["hgt"]) is not None):
		num_check = num_check + 1
	if(re.match('^#[0-9a-f]{6}$',passport["hcl"]) is not None):
		num_check = num_check + 1
	if(passport["ecl"] in EYE_LIST):
		num_check = num_check + 1
	if(re.match('^\d{9}$',passport["pid"]) is not None):
		num_check = num_check + 1
	
	if(num_check == 7):
		return 1
	else:
		return 0
	

def get_num_valid_passports(passports):
	num_valid = 0
	for passport in passports:
		keys = passport.keys()
		if(len(keys) == 8):
			check_flag = 1
			if(PROBLEM_PART == 2):
				check_flag = check_fields(passport)
			num_valid = num_valid + check_flag
		elif(len(keys) == 7 and (EXCEPTION not in keys)):
			check_flag = 1
			if(PROBLEM_PART == 2):
				check_flag = check_fields(passport)
			num_valid = num_valid + check_flag
	
	return num_valid
			
	
if __name__ == "__main__":
	passports = get_input_list()
	PROBLEM_PART = 1
	num_valid = get_num_valid_passports(passports)
	print('(part 1) there are this many valid passports: ' + str(num_valid))
	PROBLEM_PART = 2
	num_valid = get_num_valid_passports(passports)
	print('(part 2) there are this many valid passports: ' + str(num_valid))
