INPUT_FILE_NAME = "input.txt"

def iterate(players):
	player1_card = players[0].pop(0)
	player2_card = players[1].pop(0)
	if(player1_card > player2_card):
		players[0].append(player1_card)
		players[0].append(player2_card)
	else:
		players[1].append(player2_card)
		players[1].append(player1_card)
	return players

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
		
		player1_len = len(players[0])
		player2_len = len(players[1])
		while(player1_len != 0 and player2_len != 0):
			players = iterate(players)
			player1_len = len(players[0])
			player2_len = len(players[1])
		
		score = 0
		if(player1_len == 0):
			score = calculate_score(players[1])
		else:
			score = calculate_score(players[0])

		print("(part 1): the score is: " + str(score))