#include "../include/day12.h"

#define DEBUG_PRINT false
#define MAX_NUM_NODES 100
#define MAX_LABEL_LEN 100
#define MAX_NUM_PATHS 100000

/**
 * @brief retrieve the puzzle input
 * 
 * @param filename - name of the file to retrieve input from
 * @return puzzle_input_t* 
 */
puzzle_input_t *
get_puzzle_input(char * filename)
{
    int num_delimiters = 2;
    char ** delimiters = calloc(num_delimiters, sizeof(char *));
    char delimiter1 = '-';
    char delimiter2 = '\n';
    delimiters[0] = &delimiter1;
    delimiters[1] = &delimiter2;
    puzzle_input_t * puzzle_input = read_file(filename, delimiters, num_delimiters, NULL);

    free(delimiters);
    delimiters = NULL;
    return puzzle_input;
}

/**
 * @brief compare the item to the data to see if there is a match
 * 
 * @param item - item to compare
 * @param data - data to compare
 * @return int - 0 if there is a match, nonzero if no match, -2 if compare error
 */
int
compare(doubly_ll_item_t * item, void * data)
{
    if(NULL == item)
    {
        fprintf(stderr, "cannot compare to NULL item\n");
        return COMPARE_ERROR;
    }
    if(NULL == data)
    {
        fprintf(stderr, "cannot compare NULL data\n");
        return COMPARE_ERROR;
    }

    char * compare_str = (char *) data;
    graph_node_t * graph_node = (graph_node_t *) item->item;  
    cave_t * compare_item = (cave_t *) graph_node->data;  
    if(0 == strncmp(compare_str, compare_item->label, MAX_LABEL_LEN))
    {
        return 0;
    }
    return ERROR;
}

/**
 * @brief code to solve part 1 of Day 11 AoC
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 1
 */
int
part1(char * filename)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }

    //find # of inputs on one line, then get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //initialize graph
    doubly_ll_t * graph = doubly_ll_init(MAX_NUM_NODES);
    doubly_ll_t * path_list = doubly_ll_init(MAX_NUM_PATHS);

    //create a new node for every unique puzzle input.
    char * end_label = "end";
    char * start_label = "start";
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        //check if the cave label already has been created
        doubly_ll_item_t * curr_item = doubly_ll_find(graph, (void *) puzzle_input->puzzle_items[i]->char_val, compare);

        //if a cave item has not been created
        if(NULL == curr_item)
        {
            //create new cave item
            cave_t * cave = calloc(1, sizeof(cave_t));
            cave->label = puzzle_input->puzzle_items[i]->char_val;
            cave->is_big = false;
            cave->is_end = false;

            //check if the cave is the ending cave
            if(0 == strncmp(cave->label, end_label, MAX_LABEL_LEN))
            {
                cave->is_end = true;
            }

            //check if the cave is big (i.e. all caps for label)
            if(0 == is_upper(cave->label))
            {
                cave->is_big = true;
            }

            //create new graph node
            graph_node_t * node = calloc(1, sizeof(graph_node_t));
            node->neighbors = doubly_ll_init(MAX_NUM_NODES);
            node->data = (void *) cave;

            //add node to graph
            doubly_ll_add(graph, (void *) node, NULL);
            curr_item = doubly_ll_fetch(graph, graph->num_items - 1);

            //check if the cave is the starting cave
            if(0 == strncmp(cave->label, start_label, MAX_LABEL_LEN))
            {
                doubly_ll_t * path = doubly_ll_init(puzzle_input->num_items);
                doubly_ll_add(path, (void *) node, NULL);

                doubly_ll_add(path_list, (void *) path, NULL);
            }
        }

        //if we are at an odd index, add to the neighbor lists
        if(1 == i % 2)
        {
            //load the previous and current nodes
            doubly_ll_item_t * prev_item = doubly_ll_find(graph, (void *) puzzle_input->puzzle_items[i - 1]->char_val, compare);
            graph_node_t * prev_node = (graph_node_t *) prev_item->item;
            graph_node_t * curr_node = (graph_node_t *) curr_item->item;

            //add to neighbor list
            doubly_ll_add(curr_node->neighbors, (void *) prev_node, NULL);
            doubly_ll_add(prev_node->neighbors, (void *) curr_node, NULL);
        }
    }

    if(DEBUG_PRINT)
    {
        for(int i = 0; i < graph->num_items; i++)
        {
            doubly_ll_item_t * graph_item = doubly_ll_fetch(graph, i);
            graph_node_t * node = (graph_node_t *) graph_item->item;
            cave_t * cave = (cave_t *) node->data;
            printf("Cave Label: %s, is big = %d, is end = %d\n", cave->label, cave->is_big, cave->is_end);
            for(int j = 0; j < node->neighbors->num_items; j++)
            {
                doubly_ll_item_t * neighbor_item = doubly_ll_fetch(node->neighbors, j);
                graph_node_t * neighbor = (graph_node_t *) neighbor_item->item;
                cave_t * neighbor_cave = (cave_t *) neighbor->data;
                printf("%s, ", neighbor_cave->label);
            }
            printf("\n\n");
        }
    }

    //keep expanding path list until there are no more paths
    bool more_paths = true;
    int step = 0;
    while(more_paths)
    {
        more_paths = false;
        int num_paths = path_list->num_items;
        int path_index = 0;
        if(DEBUG_PRINT)
        {
            printf("***************\nstep %d, num paths: %d\n", step, num_paths);
        }
        while(path_index < num_paths)
        {
            //fetch path
            doubly_ll_item_t * path_item = doubly_ll_fetch(path_list, path_index);
            doubly_ll_t * path = (doubly_ll_t *) path_item->item;
            if(DEBUG_PRINT)
            {
                //print current path
                printf("Path: ");
                for(int i = 0; i < path->num_items; i++)
                {
                    doubly_ll_item_t * item = doubly_ll_fetch(path, i);
                    graph_node_t * node = (graph_node_t *) item->item;
                    cave_t * cave = (cave_t *) node->data;
                    printf("(%s, %d, %d), ", cave->label, cave->is_big, cave->is_end);
                }
                printf("\n\n");
            }

            doubly_ll_item_t * last_item = doubly_ll_fetch(path, path->num_items - 1);
            graph_node_t * last_node = (graph_node_t *) last_item->item;
            cave_t * last_cave = (cave_t *) last_node->data;
            if(!last_cave->is_end)
            {
                //expand the path based on the last node's neighbors
                for(int j = 0; j < last_node->neighbors->num_items; j++)
                {
                    doubly_ll_item_t * neighbor_item = doubly_ll_fetch(last_node->neighbors, j);
                    graph_node_t * neighbor_node = (graph_node_t *) neighbor_item->item;
                    cave_t * neighbor_cave = (cave_t *) neighbor_node->data;
                    doubly_ll_item_t * found_item = doubly_ll_find(path, (void *) neighbor_cave->label, compare);

                    //only expand the path if the neighbor is a big cave or hasn't been explored
                    if(neighbor_cave->is_big || NULL == found_item)
                    {
                        if(DEBUG_PRINT)
                        {
                            printf("adding path for neighbor %s\n", neighbor_cave->label);
                        }
                        more_paths = true;

                        //copy the current path to the new path and add the new node
                        doubly_ll_t * new_path = doubly_ll_init(puzzle_input->num_items);
                        int num_items = path->num_items;
                        for(int k = 0; k < num_items; k++)
                        {
                            doubly_ll_item_t * item = doubly_ll_fetch(path, k);
                            graph_node_t * node = (graph_node_t *) item->item;
                            doubly_ll_add(new_path, (void *) node, NULL);
                        }
                        doubly_ll_add(new_path, (void *) neighbor_node, NULL);
                        if(DEBUG_PRINT)
                        {
                            //print new path
                            for(int i = 0; i < new_path->num_items; i++)
                            {
                                doubly_ll_item_t * item = doubly_ll_fetch(new_path, i);
                                graph_node_t * node = (graph_node_t *) item->item;
                                cave_t * cave = (cave_t *) node->data;
                                printf("%s, ", cave->label);
                            }
                            printf("\n");
                        }
                        
                        //add new path to path list
                        doubly_ll_add(path_list, (void *) new_path, NULL);
                    }
                }
                doubly_ll_t * removed_path = (doubly_ll_t *) doubly_ll_remove(path_list, path_index);
                doubly_ll_destroy(removed_path);
                num_paths--;
            }
            else
            {
                path_index++;
            }
        }
        step++;
    }

    //count number of final paths
    int num_paths = path_list->num_items;

    //free puzzle input and data structs
    for(int i = 0; i < graph->num_items; i++)
    {
        doubly_ll_item_t * graph_item = doubly_ll_fetch(graph, i);
        graph_node_t * graph_node = (graph_node_t *) graph_item->item;
        cave_t * cave = (cave_t *) graph_node->data;

        free(cave);
        cave = NULL;
        doubly_ll_destroy(graph_node->neighbors);
        free(graph_node);
        graph_node = NULL;
    }
    doubly_ll_destroy(graph);
    for(int i = 0; i < path_list->num_items; i++)
    {
        doubly_ll_item_t * path_item = doubly_ll_fetch(path_list, i);
        doubly_ll_t * path = (doubly_ll_t *) path_item->item;
        doubly_ll_destroy(path);
    }
    doubly_ll_destroy(path_list);
    free_puzzle_input(puzzle_input);
    return num_paths;
}

/**
 * @brief solves part 2 of day 11 AOC 2021
 * 
 * @param filename - name of input file to solve
 * @return int - answer to part 2
 */
int
part2(char * filename)
{
    if(NULL == filename)
    {
        fprintf(stderr, "filename cannot be NULL\n");
        return ERROR;
    }

    //find # of inputs on one line, then get puzzle input
    puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //initialize graph
    doubly_ll_t * graph = doubly_ll_init(MAX_NUM_NODES);
    doubly_ll_t * path_list = doubly_ll_init(MAX_NUM_PATHS);
    doubly_ll_t * path_flags = doubly_ll_init(MAX_NUM_PATHS);

    //create a new node for every unique puzzle input.
    char * end_label = "end";
    char * start_label = "start";
    for(int i = 0; i < puzzle_input->num_items; i++)
    {
        //check if the cave label already has been created
        doubly_ll_item_t * curr_item = doubly_ll_find(graph, (void *) puzzle_input->puzzle_items[i]->char_val, compare);

        //if a cave item has not been created
        if(NULL == curr_item)
        {
            //create new cave item
            cave_t * cave = calloc(1, sizeof(cave_t));
            cave->label = puzzle_input->puzzle_items[i]->char_val;
            cave->is_big = false;
            cave->is_end = false;

            //check if the cave is the ending cave
            if(0 == strncmp(cave->label, end_label, MAX_LABEL_LEN))
            {
                cave->is_end = true;
            }

            //check if the cave is big (i.e. all caps for label)
            if(0 == is_upper(cave->label))
            {
                cave->is_big = true;
            }

            //create new graph node
            graph_node_t * node = calloc(1, sizeof(graph_node_t));
            node->neighbors = doubly_ll_init(MAX_NUM_NODES);
            node->data = (void *) cave;

            //add node to graph
            doubly_ll_add(graph, (void *) node, NULL);
            curr_item = doubly_ll_fetch(graph, graph->num_items - 1);

            //check if the cave is the starting cave
            if(0 == strncmp(cave->label, start_label, MAX_LABEL_LEN))
            {
                doubly_ll_t * path = doubly_ll_init(puzzle_input->num_items);
                doubly_ll_add(path, (void *) node, NULL);

                doubly_ll_add(path_list, (void *) path, NULL);
                bool * false_flag = calloc(1, sizeof(bool));
                *false_flag = false;
                doubly_ll_add(path_flags, (void *) false_flag, NULL);
            }
        }

        //if we are at an odd index, add to the neighbor lists
        if(1 == i % 2)
        {
            //load the previous and current nodes
            doubly_ll_item_t * prev_item = doubly_ll_find(graph, (void *) puzzle_input->puzzle_items[i - 1]->char_val, compare);
            graph_node_t * prev_node = (graph_node_t *) prev_item->item;
            graph_node_t * curr_node = (graph_node_t *) curr_item->item;

            //add to neighbor list
            doubly_ll_add(curr_node->neighbors, (void *) prev_node, NULL);
            doubly_ll_add(prev_node->neighbors, (void *) curr_node, NULL);
        }
    }

    if(DEBUG_PRINT)
    {
        for(int i = 0; i < graph->num_items; i++)
        {
            doubly_ll_item_t * graph_item = doubly_ll_fetch(graph, i);
            graph_node_t * node = (graph_node_t *) graph_item->item;
            cave_t * cave = (cave_t *) node->data;
            printf("Cave Label: %s, is big = %d, is end = %d\n", cave->label, cave->is_big, cave->is_end);
            for(int j = 0; j < node->neighbors->num_items; j++)
            {
                doubly_ll_item_t * neighbor_item = doubly_ll_fetch(node->neighbors, j);
                graph_node_t * neighbor = (graph_node_t *) neighbor_item->item;
                cave_t * neighbor_cave = (cave_t *) neighbor->data;
                printf("%s, ", neighbor_cave->label);
            }
            printf("\n\n");
        }
    }

    //keep expanding path list until there are no more paths
    int total_paths = 0;
    bool more_paths = true;
    int step = 0;
    while(more_paths)
    {
        more_paths = false;
        int num_paths = path_list->num_items;
        int path_index = 0;
        printf("***************\nstep %d, num paths: %d\n", step, num_paths);
        while(path_index < num_paths)
        {
            //fetch path
            doubly_ll_item_t * path_item = doubly_ll_fetch(path_list, path_index);
            doubly_ll_item_t * flag_item = doubly_ll_fetch(path_flags, path_index);
            doubly_ll_t * path = (doubly_ll_t *) path_item->item;
            bool * path_flag = (bool *) flag_item->item;
            if(DEBUG_PRINT)
            {
                //print current path
                printf("Path: ");
                for(int i = 0; i < path->num_items; i++)
                {
                    doubly_ll_item_t * item = doubly_ll_fetch(path, i);
                    graph_node_t * node = (graph_node_t *) item->item;
                    cave_t * cave = (cave_t *) node->data;
                    printf("%s, ", cave->label);
                }
                printf("\n");
            }

            doubly_ll_item_t * last_item = doubly_ll_fetch(path, path->num_items - 1);
            graph_node_t * last_node = (graph_node_t *) last_item->item;
            cave_t * last_cave = (cave_t *) last_node->data;
            if(!last_cave->is_end)
            {
                //expand the path based on the last node's neighbors
                for(int j = 0; j < last_node->neighbors->num_items; j++)
                {
                    doubly_ll_item_t * neighbor_item = doubly_ll_fetch(last_node->neighbors, j);
                    graph_node_t * neighbor_node = (graph_node_t *) neighbor_item->item;
                    cave_t * neighbor_cave = (cave_t *) neighbor_node->data;
                    doubly_ll_item_t * found_item = doubly_ll_find(path, (void *) neighbor_cave->label, compare);

                    //only expand the path if the neighbor is a big cave or hasn't been explored
                    if(neighbor_cave->is_big || NULL == found_item || (!*path_flag && 0 != strncmp(start_label, neighbor_cave->label, MAX_STRN_LEN)))
                    {
                        doubly_ll_item_t * flag_item = doubly_ll_fetch(path_flags, path_index);
                        bool current_flag = *(bool *)flag_item->item;
                        if(NULL != found_item && !neighbor_cave->is_big)
                        {
                            current_flag = true;
                        }
                        more_paths = true;

                        //copy the current path to the new path and add the new node
                        doubly_ll_t * new_path = doubly_ll_init(puzzle_input->num_items);
                        int num_items = path->num_items;
                        for(int k = 0; k < num_items; k++)
                        {
                            doubly_ll_item_t * item = doubly_ll_fetch(path, k);
                            graph_node_t * node = (graph_node_t *) item->item;
                            doubly_ll_add(new_path, (void *) node, NULL);
                        }
                        doubly_ll_add(new_path, (void *) neighbor_node, NULL);
                        
                        //add new path to path list
                        doubly_ll_add(path_list, (void *) new_path, NULL);
                        bool * new_flag = calloc(1, sizeof(bool));
                        *new_flag = current_flag;
                        doubly_ll_add(path_flags, (void *) new_flag, NULL);
                    }
                }
            }
            else
            {
                total_paths += 1;
            }
            doubly_ll_t * removed_path = (doubly_ll_t *) doubly_ll_remove(path_list, path_index);
            doubly_ll_destroy(removed_path);
            bool * removed_flag = (bool *) doubly_ll_remove(path_flags, path_index);
            free(removed_flag);
            removed_flag = NULL;
            num_paths--;
        }
        step++;
    }

    //free puzzle input and data structs
    for(int i = 0; i < graph->num_items; i++)
    {
        doubly_ll_item_t * graph_item = doubly_ll_fetch(graph, i);
        graph_node_t * graph_node = (graph_node_t *) graph_item->item;
        cave_t * cave = (cave_t *) graph_node->data;

        free(cave);
        cave = NULL;
        doubly_ll_destroy(graph_node->neighbors);
        free(graph_node);
        graph_node = NULL;
    }
    doubly_ll_destroy(graph);
    for(int i = 0; i < path_list->num_items; i++)
    {
        doubly_ll_item_t * path_item = doubly_ll_fetch(path_list, i);
        doubly_ll_t * path = (doubly_ll_t *) path_item->item;
        doubly_ll_destroy(path);
    }
    doubly_ll_destroy(path_list);
    while(path_flags->num_items > 0)
    {
        bool * removed_flag = (bool *) doubly_ll_remove(path_flags, 0);
        free(removed_flag);
        removed_flag = NULL;
    }
    doubly_ll_destroy(path_flags);
    free_puzzle_input(puzzle_input);
    return total_paths;
}