INPUT_FILE_NAME = "input.txt"

class Item():
	def __init__(self,ingredients_str,allergens_str):
		self.ingredients = ingredients_str.split(" ")
		self.allergens = allergens_str.split(", ")

	def intersect(self, item_b, set_intersection):
		intersection = []
		for ingredient in self.ingredients:
			if(ingredient in item_b.ingredients and ingredient in set_intersection):
				intersection.append(ingredient)
		return intersection

	def __repr__(self):
		print_str = "Ingredients: "
		for ingredient in self.ingredients:
			print_str = print_str + ingredient + " "
		print_str = print_str + "\nAllergens: "
		for allergen in self.allergens:
			print_str = print_str + allergen + " "
		print_str = print_str + "\n"
		return print_str

	def __ne__(self, item_b):
		if(self.ingredients == item_b.ingredients and self.allergens == item_b.allergens):
			return False
		return True

def remove_allergen(items,allergen,ingredient):
	for item in items:
		if(allergen in item.allergens):
			item.allergens.remove(allergen)
		if(ingredient in item.ingredients):
			item.ingredients.remove(ingredient)
	return items

if __name__ == "__main__":
	with open(INPUT_FILE_NAME) as input_file:
		input_list = input_file.readlines()
		items = []
		allergens = []
		allergen_dict = [[],[]]

		# process input
		for row in input_list:
			row = row.rstrip() # remove whitespace
			row = row[0:len(row)-1] # remove trailing )
			[ingredients_str, allergens_str] = row.split(" (contains ")
			new_item = Item(ingredients_str,allergens_str)
			items.append(new_item)
			for allergen in new_item.allergens:
				if(allergen not in allergens):
					allergens.append(allergen)
		
		last_len = [0,0,0]
		num_added = 0
		while(len(allergens) > 0):
			allergen = allergens.pop(0)
			removed = False
			for item_a in items:
				if(allergen in item_a.allergens):
					found = False
					set_intersection = item_a.ingredients
					# check if there is one allergen and one ingredient
					if(len(item_a.ingredients) == 1 and len(item_a.allergens) == 1):
						found = True
						removed = True
						items = remove_allergen(items,allergen,item_a.ingredients[0])
					# check if any other items also contain that allergen
					for item_b in items:
						if(item_a != item_b and allergen in item_b.allergens):
							found = True
							set_intersection = item_a.intersect(item_b,set_intersection)
							if(len(set_intersection) == 1):
								allergen_dict[0].append(allergen)
								allergen_dict[1].append(set_intersection[0])
								items = remove_allergen(items,allergen,set_intersection[0])
								removed = True
					# if no other items contained that allergen
					if(not found):
						removed = True
						for ingredient in item_a.ingredients:
							items = remove_allergen(items,allergen,ingredient)
					else:
						break
			if(not removed):
				allergens.append(allergen)
		
		num_items = 0
		for item in items:
			num_items = num_items + len(item.ingredients)
		print("(part 1) the number of times non-allergenic items appear is: " + str(num_items))
		
		sorted_string = ""
		num_loops = len(allergen_dict[0])
		for i in range(0,num_loops):
			min_val = "zzzzzzz"
			min_str = ""
			for i in range(0,len(allergen_dict[0])):
				if(allergen_dict[0][i] < min_val):
					min_val = allergen_dict[0][i]
					min_str = allergen_dict[1][i]
			sorted_string = sorted_string + min_str + ","
			allergen_dict[0].remove(min_val)
			allergen_dict[1].remove(min_str)
		print("(part 2) the sorted ingredient list based on allergens is: " + sorted_string)