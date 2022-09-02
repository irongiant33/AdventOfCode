INPUT_FILE_NAME = "input.txt"

import copy

def to_binary(value,binary=""):
	val = value//2
	binary = str(value % 2) + binary
	if(val > 1):
		binary = to_binary(val,binary)
	else:
		return str(val) + binary
	return binary

def to_decimal(str_value):
	decimal = 0
	num_bits = len(str_value)
	for i in range(0,num_bits):
		decimal = decimal + int(str_value[i])*(2**(num_bits-1-i))
	return decimal

def apply_mask(decimal_value,mask):
	binary_str = to_binary(decimal_value)
	num_zero_fill = len(mask) - len(binary_str)
	binary_str = "0"*num_zero_fill + binary_str
	mask_list = list(mask)
	binary_str_list = list(binary_str)
	for i in range(0,len(mask_list)):
		if(mask_list[i] != 'X' and mask_list[i] != binary_str_list[i]):
			binary_str_list[i] = mask_list[i]
	decimal_val = to_decimal("".join(binary_str_list))
	return decimal_val

def expand(addresses):
	new_addresses = []
	for address in addresses:
		for i in range(0,2):
			temp_address = address + str(i)
			new_addresses.append(temp_address)
	return new_addresses

def apply_mask_pt2(memory_address,mask):
	binary_str = to_binary(memory_address)
	num_zero_fill = len(mask) - len(binary_str)
	binary_mem_addr = "0"*num_zero_fill + binary_str
	mask_list = list(mask)
	binary_mem_addr_list = list(binary_mem_addr)
	addresses = [""]
	for i in range(0,len(mask_list)):
		if(mask_list[i] == 'X'):
			addresses = expand(addresses)
		else:
			add_to = binary_mem_addr_list[i]
			if(mask_list[i] == '1'):
				add_to = '1'
			for j in range(0,len(addresses)):
				addresses[j] = addresses[j] + add_to
	address_nums = []
	for address in addresses:
		address_nums.append(to_decimal(address))
	return address_nums

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		memory = [[],[]]
		mask = ""
		for instruction in input_list:
			instruction = (instruction.rstrip()).split(" = ")
			command_params = instruction[0].split('[')
			if(instruction[0] == "mask"):
				mask = instruction[1]
			if(command_params[0] == "mem"):
				memory_address = int(command_params[1][0:len(command_params[1])-1])
				value = apply_mask(int(instruction[1]),mask)
				if(memory_address in memory[0]):
					memory[1][memory[0].index(memory_address)] = value
				else:
					memory[0].append(memory_address)
					memory[1].append(value)
		
		print("(part 1) the sum of values in memory is: "+str(sum(memory[1])))

		memory = [[],[]]
		mask = ""
		for instruction in input_list:
			instruction = (instruction.rstrip()).split(" = ")
			command_params = instruction[0].split('[')
			if(instruction[0] == "mask"):
				mask = instruction[1]
			if(command_params[0] == "mem"):
				memory_address = int(command_params[1][0:len(command_params[1])-1])
				addresses = apply_mask_pt2(memory_address,mask)
				for address in addresses:
					if(address in memory[0]):
						memory[1][memory[0].index(address)] = int(instruction[1])
					else:
						memory[0].append(address)
						memory[1].append(int(instruction[1]))
		print("(part 2) the sum of values in memory is: " + str(sum(memory[1])))