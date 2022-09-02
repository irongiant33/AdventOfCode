#include "../include/day15.h"
#include <limits.h>
#include <math.h>

#define DEBUG_PRINT false

void
print_path(path_t * path)
{
    printf("Expanding path: ");
    for(int i = 0; i < path->list->num_items; i++)
    {
        doubly_ll_item_t * pi = doubly_ll_fetch(path->list, i);
        graph_node_t * gn = (graph_node_t *) pi->item;
        graph_data_t * gd = (graph_data_t *) gn->data;
        printf("%ld ", gd->data->value);
    }
    printf("cost=%ld ", path->cost);
    printf("heuristic=%ld\n", path->heuristic);
}

/**
 * @brief code to solve part 1 of Day 14 AoC
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

    //find the length of each row and filter out the newline characters
    puzzle_input_t * puzzle_input = read_file(filename, NULL, 0, NULL);
    int row_len = 0;
    while(*puzzle_input->puzzle_items[row_len]->char_val != '\n')
    {
        row_len++;
    }
    puzzle_input_t * filtered_input = filter_by_value(puzzle_input, '\n');
    int col_len = filtered_input->num_items / row_len;
    int err_code = convert_input_to_long(filtered_input);
    if(err_code != SUCCESS)
    {
        fprintf(stderr, "error convering input to long");
        return ERROR;
    }
    
    //create a graph from the input
    graph_node_t ** graph = calloc(filtered_input->num_items, sizeof(graph_node_t *));
    for(int i = 0; i < filtered_input->num_items; i++)
    {
        graph_node_t * node = calloc(1, sizeof(graph_node_t));
        graph_data_t * data = calloc(1, sizeof(graph_data_t));
        data->index = i;
        data->data = filtered_input->puzzle_items[i];
        node->data = (void *) data;
        node->neighbors = doubly_ll_init(4);
        graph[i] = node;
    }

    //populate neighbors of the graph
    for(int i = 0; i < filtered_input->num_items; i++)
    {
        //discover neighbors
        int rel_pos = i % row_len;
        if(rel_pos - 1 >= 0) //left
        {
            doubly_ll_add(graph[i]->neighbors, (void *) graph[i - 1], NULL);
        }
        if(rel_pos + 1 < row_len) //right
        {
            doubly_ll_add(graph[i]->neighbors, (void *) graph[i + 1], NULL);
        }
        if(i - row_len >= 0) //top
        {
            doubly_ll_add(graph[i]->neighbors, (void *) graph[i - row_len], NULL);
        }
        if(i + row_len < filtered_input->num_items)
        {
            doubly_ll_add(graph[i]->neighbors, (void *) graph[i + row_len], NULL);
        }
    }

    bool print_graph = false;
    if(DEBUG_PRINT && print_graph)
    {
        for(int i = 0; i < filtered_input->num_items; i++)
        {
            graph_data_t * grd = (graph_data_t *) graph[i]->data;
            printf("Node %2ld: %ld, neighbors=", grd->index, grd->data->value);
            for(int j = 0; j < graph[i]->neighbors->num_items; j++)
            {
                doubly_ll_item_t * dll_i = doubly_ll_fetch(graph[i]->neighbors, j);
                graph_node_t * gr_n = (graph_node_t *) dll_i->item;
                graph_data_t * grd_n = (graph_data_t *) gr_n->data;
                printf("%ld ", grd_n->data->value);
            }
            printf("\n");
        }
    }

    //a*
    int head = 0;
    doubly_ll_t * path_list = doubly_ll_init(filtered_input->num_items * filtered_input->num_items);
    path_t * initial_path = calloc(1, sizeof(path_t));
    doubly_ll_add(path_list, (void *) initial_path, &head);
    int end_node_reached_count = 0;

    initial_path->list = doubly_ll_init(filtered_input->num_items);
    initial_path->visited = calloc(filtered_input->num_items, sizeof(int));
    doubly_ll_add(initial_path->list, (void *) graph[0], &head);
    graph_data_t * graph_d = (graph_data_t *) graph[0]->data;
    initial_path->visited[0] = 1;
    initial_path->cost = graph_d->data->value;
    initial_path->heuristic = (col_len - 1 - (graph_d->index / row_len)) + (row_len - 1 - (graph_d->index % row_len));

    int debug_count = 0;
    int num_complete_paths_to_eval = 3;
    puzzle_item_t * starting_node = (puzzle_item_t *) filtered_input->puzzle_items[0];
    long * lowest_cost = calloc(num_complete_paths_to_eval, sizeof(long));
    long starting_value = -1 * (starting_node->value);
    for(int i = 0; i < num_complete_paths_to_eval; i++)
    {
        lowest_cost[i] = starting_value;
    }
    while(end_node_reached_count < num_complete_paths_to_eval && debug_count < 10000)
    {
        path_t * path = (path_t *) doubly_ll_remove(path_list, 0);
        doubly_ll_item_t * node = doubly_ll_fetch(path->list, 0);
        graph_node_t * graph_node = (graph_node_t *) node->item;

        if(DEBUG_PRINT)
        {
            print_path(path);
        }

        //create path for each neighbor
        int num_of_i = graph_node->neighbors->num_items;
        for(int i = 0; i < num_of_i; i++)
        {
            doubly_ll_item_t * list_item = doubly_ll_fetch(graph_node->neighbors, i);
            graph_node_t * graph_n = (graph_node_t *) list_item->item;
            graph_data_t * g_d = (graph_data_t *) graph_n->data;
            if(path->visited[g_d->index] > 0)
            {
                continue;
            }

            path_t * new_path = calloc(1, sizeof(path_t));
            new_path->list = doubly_ll_init(filtered_input->num_items);
            new_path->visited = calloc(filtered_input->num_items, sizeof(int));
            for(int j = 0; j < path->list->num_items; j++)
            {
                doubly_ll_item_t * n = doubly_ll_fetch(path->list, j);
                doubly_ll_add(new_path->list, n->item, NULL);
            }
            for(int j = 0; j < filtered_input->num_items; j++)
            {
                new_path->visited[j] = path->visited[j];
            }
            doubly_ll_add(new_path->list, (void *) graph_n, &head);
            new_path->visited[g_d->index] = 1;
            new_path->cost = path->cost + g_d->data->value;
            new_path->heuristic = (col_len - 1 - (g_d->index / row_len)) + (row_len - 1 - (g_d->index % row_len));
            if(g_d->index == (filtered_input->num_items - 1))
            {
                for(int k = 0; k < end_node_reached_count; k++)
                {
                    if(lowest_cost[k] == new_path->cost + starting_value)
                    {
                        goto CLEANUP_COMPLETE_PATH;
                    }
                }
                lowest_cost[end_node_reached_count] += new_path->cost;
                end_node_reached_count += 1;
                print_path(new_path);
                printf("path cost: %ld\n", new_path->cost);

CLEANUP_COMPLETE_PATH:
                doubly_ll_destroy(new_path->list);
                free(new_path->visited);
                new_path->visited = NULL;
                free(new_path);
                new_path = NULL;
                continue;
            }

            //priority insertion
            int index = 0;
            bool found_spot = false;
            long new_path_objective = (new_path->cost + 10 * ((long) log(new_path->heuristic + 1)));
            while(index < path_list->num_items && !found_spot)
            {
                doubly_ll_item_t * p_i = doubly_ll_fetch(path_list, index);
                path_t * test_p = (path_t *) p_i->item;
                long test_path_objective = test_p->cost + 10 * ((long) log(test_p->heuristic + 1));
                if(test_path_objective > new_path_objective)
                {
                    found_spot = true;
                }
                else
                {
                    index++;
                }
            }
            doubly_ll_add(path_list, (void *) new_path, &index);
        }
        doubly_ll_destroy(path->list);
        free(path->visited);
        path->visited = NULL;
        free(path);
        path = NULL;

        if(DEBUG_PRINT)
        {
            printf("\t# of paths in path_list: %d\n", path_list->num_items);
        }
        debug_count++;
    }

    //which cost is the lowest?
    long answer = LONG_MAX;
    for(int i = 0; i < num_complete_paths_to_eval; i++)
    {
        if(lowest_cost[i] < answer)
        {
            answer = lowest_cost[i];
        }
    }

    //free and return
    free(lowest_cost);
    lowest_cost = NULL;
    while(path_list->num_items > 0)
    {
        path_t * old_path = (path_t *) doubly_ll_remove(path_list, 0);
        doubly_ll_destroy(old_path->list);
        free(old_path->visited);
        old_path->visited = NULL;
        free(old_path);
        old_path = NULL;
    }
    doubly_ll_destroy(path_list);
    for(int i = 0; i < filtered_input->num_items; i++)
    {
        doubly_ll_destroy(graph[i]->neighbors);
        free(graph[i]->data);
        free(graph[i]);
        graph[i] = NULL;
    }
    free(graph);
    graph = NULL;
    free_puzzle_input(filtered_input);
    if(answer < INT_MAX)
    {
        return (int) answer;
    }
    return -1;
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

    //get the coordinates of the dot inputs
    //puzzle_input_t * puzzle_input = get_puzzle_input(filename);

    //free and return
    //free_puzzle_input(puzzle_input);
    return 0;
}

/*
int
main()
{
    part1("src/test_input.txt");
}
*/