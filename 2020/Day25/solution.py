INPUT_FILE_NAME = "input.txt"

SUBJECT_NUM = 7
DIVISOR = 20201227

def encrypt(loop_size,sn):
	value = 1
	for i in range(0,loop_size):
		value = value * sn
		value = value % DIVISOR
	return value

def reverse_pk(pk,sn):
	value = 1
	loop_size = -1
	for i in range(1,999999999):
		value = value * sn
		value = value % DIVISOR
		if(value == pk):
			loop_size = i
			break
	return loop_size


if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		pk_door = int(input_list[0].rstrip())
		pk_card = int(input_list[1].rstrip())
		ls_door = reverse_pk(pk_door,SUBJECT_NUM)
		ls_card = reverse_pk(pk_card,SUBJECT_NUM)
		print(str(pk_door) + " " + str(ls_door))
		print(str(pk_card) + " " + str(ls_card))
		ec1 = encrypt(ls_card,pk_door)
		ec2 = encrypt(ls_door,pk_card)
		print(str(ec1) + " " + str(ec2))

