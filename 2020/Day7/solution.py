INPUT_FILE_NAME = "input.txt"
SEARCH_BAG = "shiny gold"

class Bag():
    def update_lists(self, input_lists, bag_dict):
        if(self.contents_complete):
            return
        bag_name_list = input_lists[0]
        contain_list = input_lists[1]
        amount_list = input_lists[2]

        for i in range(0,len(bag_name_list)):
            bag_name = bag_name_list[i]
            if(bag_name == self.bag_name):
                for j in range(0,len(contain_list[i])):
                    sub_bag_name = contain_list[i][j]
                    sub_bag_amount = amount_list[i][j]
                    if(sub_bag_name != "none"):
                        self.contain_list.append(sub_bag_name)
                        self.amount_list.append(sub_bag_amount)
                        bag_dict[sub_bag_name].update_lists(input_lists,bag_dict)
                        
                        sub_bag_contain_list = bag_dict[sub_bag_name].contain_list
                        sub_bag_amount_list = bag_dict[sub_bag_name].amount_list
                        for k in range(0,len(sub_bag_contain_list)):
                            sub_sub_bag_name = sub_bag_contain_list[k]
                            sub_sub_bag_amount = sub_bag_amount_list[k]
                            if(sub_sub_bag_name != "none"):
                                self.contain_list.append(sub_sub_bag_name)
                                self.amount_list.append(sub_bag_amount * sub_sub_bag_amount)
        self.contents_complete = True
        return

    def __init__(self,name):
        self.contain_list = []
        self.amount_list = []
        self.bag_name = name
        self.contents_complete = False

def get_input_list():
    input_file = open(INPUT_FILE_NAME)
    bag_list = []
    contain_list = []
    amount_list = []
    for line in input_file:
        new_line = line.rstrip()
        new_line = new_line.replace(".","") #get rid of trailing period
        [bag_name, contents] = new_line.split(" bags contain ")
        bag_list.append(bag_name)
        content_list = contents.split(", ")
        if(content_list[0] == 'no other bags'):
            contain_list.append(["none"])
            amount_list.append([0])
        else:
            sub_bag_list = []
            sub_amount_list = []
            for content in content_list:
                params = content.split(" ")
                sub_amount_list.append(int(params.pop(0)))
                params.pop(-1) #get rid of the word "bags"
                sub_bag_list.append(" ".join(params))
            contain_list.append(sub_bag_list)
            amount_list.append(sub_amount_list)

    return [bag_list,contain_list,amount_list]

if __name__ == "__main__":
    input_lists = get_input_list()
    bag_name_list = input_lists[0]
    bag_dict = {}
    num_bags = 0

    #build the bag dictionary
    for bag_name in bag_name_list:
        new_bag = Bag(bag_name)
        bag_dict[bag_name] = new_bag

    #update the contents of the bags in the bag dictionary.
    for bag_name in bag_name_list:
        bag = bag_dict[bag_name]
        bag.update_lists(input_lists, bag_dict)
        if(SEARCH_BAG in bag.contain_list):
            num_bags = num_bags + 1
    
    num_sub_bags = sum(bag_dict[SEARCH_BAG].amount_list)

    print("(part 1) The number of bags is: " + str(num_bags))
    print("(part 2) The number of bags in your " + SEARCH_BAG + " bag is: " + str(num_sub_bags))
