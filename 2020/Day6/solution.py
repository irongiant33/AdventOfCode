INPUT_FILE_NAME = "input.txt"

def get_input_list():
    input_file = open(INPUT_FILE_NAME)
    input_file_list = []
    group = []
    for line in input_file:
        new_line = line.rstrip()
        if(line == '\n'):
            input_file_list.append(group)
            group = []
        else:
            group.append(new_line)
    input_file_list.append(group)
    return input_file_list

def get_question_sum_pt1(input_list):
    running_sum = 0
    for group in input_list:
        group_string = list("".join(group))
        group_set = set(group_string)
        group_questions = list(group_set)
        running_sum = running_sum + len(group_questions)
    return running_sum

def get_question_sum_pt2(input_list):
    running_sum = 0
    for group in input_list:
        group_string = list("".join(group))
        group_set = set(group_string)
        group_questions = list(group_set)
        num_in_common = len(group_questions)
        for letter in group_questions:
            for member in group:
                if(letter not in list(member)):
                    num_in_common = num_in_common -1
                    break
        running_sum = running_sum + num_in_common
    return running_sum

if __name__ == "__main__":
    input_list = get_input_list()
    question_sum = get_question_sum_pt1(input_list)
    print("(part 1) the sum of all groups questions is: " + str(question_sum))
    question_sum2 = get_question_sum_pt2(input_list)
    print("(part 2) the sum of all groups questions is: " + str(question_sum2))
