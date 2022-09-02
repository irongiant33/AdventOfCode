import copy

INPUT_FILE_NAME = "input.txt"

class Round():
	def __init__(self,player1,player2):
		self.player1 = player1
		self.player2 = player2

	def __eq__(self,other):
		if(self.player1 == other.player1 and self.player2 == other.player2):
			return True
		return False

	def __repr__(self):
		print_str = "Player 1: "
		for card in self.player1:
			print_str = print_str + str(card) + " "
		print_str = print_str + "\nPlayer 2: "
		for card in self.player2:
			print_str = print_str + str(card) + " "
		return print_str

def check_round(rnd,rounds):
	for i in range(0,len(rounds)-1):
		r = rounds[i]
		if(rnd == r):
			return True
	return False

def play_combat(player1, player2, is_recursive,loop_num=0):
	rounds = []
	round_num = 0
	while(len(player1) > 0 and len(player2) > 0):
		rnd = Round(copy.deepcopy(player1),copy.deepcopy(player2))
		rounds.append(rnd)
		round_num = round_num + 1
		player1_card = player1.pop(0)
		player2_card = player2.pop(0)
		if(check_round(rnd,rounds)):
			# game instantly ends in win for player 1
			player1.insert(0,player1_card)
			return [player1,[]]
		elif(is_recursive and len(player1) >= player1_card and len(player2) >= player2_card):
			[sub_player1, sub_player2] = play_combat(copy.deepcopy(player1),copy.deepcopy(player2),True,loop_num+1)
			if(len(sub_player1) == 0):
				player2.append(player2_card)
				player2.append(player1_card)
			else:
				player1.append(player1_card)
				player1.append(player2_card)
		else:
			if(player1_card > player2_card):
				player1.append(player1_card)
				player1.append(player2_card)
			else:
				player2.append(player2_card)
				player2.append(player1_card)
	return [player1, player2]

def calculate_score(player):
	multiplier = len(player)
	score = 0
	for card in player:
		score = score + multiplier * card
		multiplier = multiplier - 1
	return score

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()

		players = [[],[]]
		index = 0
		for line in input_list:
			if(line.rstrip().isnumeric()):
				players[index].append(int(line.rstrip()))
			elif(line.rstrip()==""):
				index = 1
		
		player1 = players[0]
		player2 = players[1]
		[player1, player2] = play_combat(copy.deepcopy(player1),copy.deepcopy(player2),False)
		
		score = 0
		if(len(player1) == 0):
			score = calculate_score(player2)
		else:
			score = calculate_score(player1)

		print("(part 1): the score of Combat is: " + str(score))


		player1 = players[0]
		player2 = players[1]
		[player1, player2] = play_combat(copy.deepcopy(player1),copy.deepcopy(player2),True)

		score = 0
		if(len(player1) == 0):
			score = calculate_score(player2)
		else:
			score = calculate_score(player1)
		
		print("(part 2): the score of Recursive Combat is: " + str(score))