#include "common.h"

/**
 * @brief retrieve an item from the doubly linked list
 * 
 * @param list - list to retrieve from
 * @param index - index to retrieve
 * @return doubly_ll_item_t* - retrieved item
 */
doubly_ll_item_t *
doubly_ll_fetch(doubly_ll_t * list, int index)
{
    //check inputs
    if(NULL == list)
    {
        fprintf(stderr, "cannot fetch from NULL list\n");
        return NULL;
    }
    if(index < 0 || index >= list->num_items)
    {
        fprintf(stderr, "index %d is out of fetch range\n", index);
        return NULL;
    }

    //retrieve the item
    doubly_ll_item_t * fetched_item = list->head;
    for(int i = 0; i < index; i++)
    {
        fetched_item = fetched_item->next;
    }
    return fetched_item;
}

/**
 * @brief add item to doubly linked list at the index
 * 
 * @param list - list to add to
 * @param item - item to add
 * @param index - index to add at. If NULL, append the item
 * @return int - -1 if error, 0 if success
 */
int
doubly_ll_add(doubly_ll_t * list, void * item, int * add_at_index)
{
    //check inputs
    if(list == NULL)
    {
        fprintf(stderr, "cannot add item to NULL list\n");
        return ERROR;
    }
    if(item == NULL)
    {
        fprintf(stderr, "cannot add NULL item to list\n");
        return ERROR;
    }
    if(list->num_items == list->max_size)
    {
        fprintf(stderr, "list has reached its maximum size\n");
        return ERROR;
    }
    
    //find index of new item
    int index = list->num_items;
    if(NULL != add_at_index)
    {
        //check input index is in right range
        if(*add_at_index >= 0 && *add_at_index <= list->num_items)
        {
            index = *add_at_index;
        }
        else
        {
            fprintf(stderr, "add index needs to be greater than -1 and less than or equal to %d\n", list->num_items);
            return ERROR;
        }
    }

    doubly_ll_item_t * new_item = calloc(1, sizeof(doubly_ll_item_t));
    new_item->item = item;
    new_item->next = NULL;
    new_item->prev = NULL;

    if(NULL == list->head)
    {
        list->head = new_item;
    }
    else if(index == 0)
    {
        list->head->prev = new_item;
        new_item->next = list->head;
        list->head = new_item;
    }
    else if (index == list->num_items)
    {
        doubly_ll_item_t * last_item = doubly_ll_fetch(list, list->num_items - 1);
        last_item->next = new_item;
        new_item->prev = last_item;
    }
    else
    {
        doubly_ll_item_t * fetched_next_item = doubly_ll_fetch(list, index);
        doubly_ll_item_t * fetched_prev_item = fetched_next_item->prev;
        
        fetched_prev_item->next = new_item;
        fetched_next_item->prev = new_item;

        new_item->next = fetched_next_item;
        new_item->prev = fetched_prev_item;
    }

    //increment number of items in list
    list->num_items += 1;
    return SUCCESS;    
}

/**
 * @brief remove an item from the linked list and return its value
 * 
 * @param list - list to remove from
 * @param index - item index to remove
 * @return void* - value of the removed item
 */
void *
doubly_ll_remove(doubly_ll_t * list, int index)
{
    //check inputs
    if(NULL == list)
    {
        fprintf(stderr, "cannot fetch from NULL list\n");
        return NULL;
    }
    if(index < 0 || index >= list->num_items)
    {
        fprintf(stderr, "index %d is out of fetch range\n", index);
        return NULL;
    }

    //fetch the item to remove
    doubly_ll_item_t * item_to_remove = doubly_ll_fetch(list, index);

    //it is the first item
    if(index == 0)
    {
        list->head = item_to_remove->next;

        if(NULL != item_to_remove->next)
        {
            item_to_remove->next->prev = NULL;
        }
    }
    //it is the last item
    else if (index == (list->num_items - 1))
    {
        item_to_remove->prev->next = NULL;
    }
    //it is in the middle
    else
    {
        item_to_remove->next->prev = item_to_remove->prev;
        item_to_remove->prev->next = item_to_remove->next;
    }

    //decrement the number of items in the list
    list->num_items -= 1;

    //free and return
    void * removed_item = item_to_remove->item;
    free(item_to_remove);
    item_to_remove = NULL;
    return removed_item;
}

/**
 * @brief free and destroy the doubly linked list. does not free the items
 *        stored within the list items themselves
 * 
 * when freeing items within the doubly ll before calling destroy, use a
 * while(list->num_items > 0)
 * {
 *    doubly_ll_item_t * item = doubly_ll_fetch(list, 0);
 *    free(item->item);
 *    item->item = NULL;
 * }
 * 
 * @param list - list to destroy
 * @return int - success code
 */
int
doubly_ll_destroy(doubly_ll_t * list)
{
    if(NULL == list)
    {
        return SUCCESS;
    }

    while(list->num_items > 0)
    {
        doubly_ll_remove(list, 0);
    }

    free(list->list);
    list->list = NULL;
    free(list);
    list = NULL;
    return SUCCESS;
}

/**
 * @brief finds an item in the doubly ll based on the data 
 * 
 * @param list - doubly ll to search
 * @param label - label to find
 * @param compare - pointer to function to compare data with items. Should return 0 if the comparison matches.
 *                  return a value greater than 0 for greater than, less than 0 for less than.
 * @return doubly_ll_item_t * - pointer to the found item
 */
doubly_ll_item_t *
doubly_ll_find(doubly_ll_t * list, void * data, int (*compare)(doubly_ll_item_t * item_a, void * data))
{
    //check inputs
    if(NULL == list)
    {
        fprintf(stderr, "cannot find item in NULL list\n");
        return NULL;
    }
    if(NULL == data)
    {
        fprintf(stderr, "cannot find NULL item in a list\n");
        return NULL;
    }

    //loop through graph and compare each item
    int list_index = 0;
    doubly_ll_item_t * item = list->head;
    bool is_found = false;
    while(!is_found && list_index < list->num_items)
    {
        if(0 == compare(item, data))
        {
            return item;
        }
        item = item->next;
        list_index++;
    }
    return NULL;
}

/**
 * @brief initialize doubly linked list
 * 
 * @param size - maximum number of items in the list
 * @return doubly_ll_t* 
 */
doubly_ll_t *
doubly_ll_init(int max_size)
{
    doubly_ll_t * dll = calloc(1, sizeof(doubly_ll_t));
    dll->num_items = 0;
    dll->max_size = max_size;
    dll->list = calloc(max_size, sizeof(doubly_ll_item_t *));
    dll->head = NULL;
    return dll;
}

/**
 * @brief swap the two indices within the doubly linked list
 * 
 * @param list - list to swap from
 * @param i - index a
 * @param j - index b
 * @return int - success code
 */
int
doubly_ll_swap(doubly_ll_t * list, int i, int j)
{
    if(i >= list->num_items || j > list->num_items)
    {
        fprintf(stderr, "cannot swap items out of list range\n");
        return ERROR;
    }
    if(i < 0 || j < 0)
    {
        fprintf(stderr, "indices must be greater than or equal to 0\n");
        return ERROR;
    }
    if(i == j)
    {
        return SUCCESS;
    }

    doubly_ll_item_t * item_a = doubly_ll_fetch(list, i);
    doubly_ll_item_t * item_b = doubly_ll_fetch(list, j);
    
    doubly_ll_item_t * temp_item = calloc(1, sizeof(doubly_ll_item_t));
    temp_item->item = item_a->item;

    item_a->item = item_b->item;
    item_b->item = temp_item->item;

    free(temp_item);
    temp_item = NULL;
    return SUCCESS;
}

/**
 * @brief helper function to partition the list for quicksort
 * 
 * @param list - list to partition
 * @param compare - comparison function
 * @param low - start index
 * @param high - stop index (includes this number)
 * @return int - index at which the list should be partitioned
 */
int
partition(doubly_ll_t * list, int (*compare)(doubly_ll_item_t * item_a, doubly_ll_item_t * item_b), int low, int high)
{
    doubly_ll_item_t * pivot = doubly_ll_fetch(list, high);

    int index = (low - 1);

    for(int j = low; j <= (high - 1); j++)
    {
        doubly_ll_item_t * swap = doubly_ll_fetch(list, j);
        if(-1 == compare(swap, pivot))
        {
            index++;
            doubly_ll_swap(list, index, j);
        }
    }
    doubly_ll_swap(list, index + 1, high);
    return (index + 1);
}

/**
 * @brief sort a doubly linked list using quicksort
 * 
 * @param list - list to sort
 * @param compare - function to compare items in the list. Should return:
 *                  -1 if item_a < b
 *                   0 if item_a == item_b
 *                   1 if item_a > item_b
 * @param low - start index
 * @param high - stop index (included)
 * @return int success code
 */
int
doubly_ll_sort(doubly_ll_t * list, int (*compare)(doubly_ll_item_t * item_a, doubly_ll_item_t * item_b), int low, int high)
{
    if(NULL == list)
    {
        fprintf(stderr, "cannot sort NULL list\n");
        return ERROR;
    }
    if(NULL == compare)
    {
        fprintf(stderr, "cannot sort list with NULL comparison function\n");
        return ERROR;
    }

    if(low < high)
    {
        int pi = partition(list, compare, low, high);

        doubly_ll_sort(list, compare, low, pi - 1);
        doubly_ll_sort(list, compare, pi + 1, high);
    }
    return SUCCESS;
}

/**
 * @brief counts number of occurences of an item in the doubly ll based on the data 
 * 
 * @param list - doubly ll to search
 * @param label - label to find
 * @param compare - pointer to function to compare data with items. Should return 0 if the comparison matches.
 *                  return a value greater than 0 for greater than, less than 0 for less than.
 * @return int - number of times the data has been found, -1 on error
 */
int
doubly_ll_count(doubly_ll_t * list, void * data, int (*compare)(doubly_ll_item_t * item_a, void * data))
{
    //check inputs
    if(NULL == list)
    {
        fprintf(stderr, "cannot find item in NULL list\n");
        return ERROR;
    }
    if(NULL == data)
    {
        fprintf(stderr, "cannot find NULL item in a list\n");
        return ERROR;
    }

    //loop through graph and compare each item
    int list_index = 0;
    int count = 0;
    while(list_index < list->num_items)
    {
        doubly_ll_item_t * item = doubly_ll_fetch(list, list_index);
        if(0 == compare(item, data))
        {
            count++;
        }
        list_index++;
    }
    return count;
}
