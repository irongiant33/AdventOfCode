#include "common.h"

/**
 * @brief Create a new empty hash table
 * @param hash_func The hash function that will be used
 */
hash_table_t *create_hashtable(hash_func hash_f, int num_buckets)
{
    if(hash_f == NULL)
    {
        return NULL;
    }
    hash_table_t * new_hash_table = calloc(1, sizeof(hash_table_t));
    new_hash_table->bucket_sizes = calloc(1, sizeof(int));
    *new_hash_table->bucket_sizes = DEFAULT_HASH_TABLE_BUCKET_SIZE;
    new_hash_table->hash_f = hash_f;
    new_hash_table->num_buckets = num_buckets;
    new_hash_table->items = calloc(new_hash_table->num_buckets, sizeof(data_item_t **));
    for(int i = 0; i < new_hash_table->num_buckets; i++)
    {
        new_hash_table->items[i] = calloc(*new_hash_table->bucket_sizes, sizeof(data_item_t *));
        for(int j = 0; j < *new_hash_table->bucket_sizes; j++)
        {
            data_item_t * new_data_item = calloc(1, sizeof(data_item_t));
            new_data_item->data = NULL;
            new_data_item->key = -1;
            new_hash_table->items[i][j] = new_data_item;
        }  
    }
    return new_hash_table;
}

bool assign_to_bucket(hash_table_t * table, void * data, int key, int hash)
{
    bool collision = true;
    for(int i = 0; i < *table->bucket_sizes; i++)
    {
        if(NULL == table->items[hash][i]->data)
        {
            table->items[hash][i]->data = data;
            table->items[hash][i]->key = key;
            collision = false;
            break;
        }
    }
    return collision;
}

/**
 * @brief Insert a new item into the hash table.
 * 
 * @param table The table to insert into
 * @param key The new key
 * @param data The new data
 * 
 * @return 0 on success
 */
int insert_hashtable(hash_table_t *table, int key, void * data)
{
    if(table == NULL)
    {
        return -1;
    }
    int hash = table->hash_f(key);
    if(hash + 1 > table->num_buckets)
    {
        int old_num_buckets = table->num_buckets;
        table->num_buckets = hash + 1;
        table->items = (data_item_t ***)realloc(table->items, table->num_buckets * sizeof(data_item_t **));
        for(int i = old_num_buckets; i < table->num_buckets; i++)
        {
            table->items[i] = calloc(*table->bucket_sizes, sizeof(data_item_t *));
            for(int j = 0; j < *table->bucket_sizes; j++)
            {
                data_item_t * new_data_item = calloc(1, sizeof(data_item_t));
                new_data_item->data = NULL;
                new_data_item->key = -1;
                table->items[i][j] = new_data_item;
            }  
        }
    }
    bool collision = assign_to_bucket(table, data, key, hash);
    if(collision)
    {
        *table->bucket_sizes = *table->bucket_sizes + DEFAULT_HASH_TABLE_BUCKET_SIZE;
        for(int i = 0; i < table->num_buckets; i++)
        {
            table->items[i] = (data_item_t **)realloc(table->items[i], *table->bucket_sizes * sizeof(data_item_t *));
            data_item_t * new_data_item = calloc(1, sizeof(data_item_t));
            new_data_item->data = NULL;
            new_data_item->key = -1;
            table->items[i][*table->bucket_sizes - 1] = new_data_item;
        }
        assign_to_bucket(table, data, key, hash);
    }
    return 0;
}

/**
 * @brief Get the index within a bucket of a key
 * 
 * @param hash - hash value associated with the key
 * @param table - hash table to look up in
 * @param key - key to find
 * @return int - index of key within the hash bucket
 */
int get_index(int hash, hash_table_t * table, int key)
{
    if(hash + 1 > table->num_buckets)
    {
        return -1;
    }
    int index = -1;
    for(int i = *table->bucket_sizes - 1; i >= 0; i--)
    {
        if(table->items[hash][i] != NULL && table->items[hash][i]->key == key)
        {
            index = i;
            break;
        }
    }
    return index;
}

/**
 * @brief Remove an item from the hash table.
 * 
 * @param table The table to delete from
 * @param key The key to remove
 * 
 * @return <0 on error, 0 on success, >0 if key not in hash table
 */
int delete_from_hashtable(hash_table_t *table, int key)
{
    if(table == NULL)
    {
        return -1;
    }
    int hash = table->hash_f(key);
    int remove_index = get_index(hash, table, key);
    if(remove_index == -1)
    {
        return 1;
    }
    table->items[hash][remove_index]->data = NULL;
    table->items[hash][remove_index]->key = -1;
    return 0;
}

/**
 * @brief Retrieve an item from the hash table.
 * 
 * @param table The table to get the item from
 * @param key The key to retrieve
 * 
 * @return Pointer to the requested item or NULL
 */
data_item_t *get_from_hashtable(hash_table_t *table, int key)
{
    if(table == NULL)
    {
        return NULL;
    }
    int hash = table->hash_f(key);
    int index = get_index(hash, table, key);
    if(index == -1)
    {
        return NULL;
    }
    return table->items[hash][index];
}

/**
 * @brief Remove all items from the hash table.
 * 
 * @param table The table to empty.
 * 
 * @return 0 on success
 */
int empty_hashtable(hash_table_t *table)
{
    if(table == NULL)
    {
        return -1;
    }
    for(int i = 0; i < table->num_buckets; i++)
    {
        for(int j = 0; j < *table->bucket_sizes; j++)
        {
            free(table->items[i][j]);
            table->items[i][j] = NULL;
        }
    }
    return 0;
}

/**
 * @brief Destroy the hash table.
 * 
 * @param table The table to destroy
 * 
 * @return 0 on success
 */
int destroy_hashtable(hash_table_t *table)
{
    if(table == NULL)
    {
        return -1;
    }
    empty_hashtable(table);
    for(int i = 0; i < table->num_buckets; i++)
    {
        free(table->items[i]);
        table->items[i] = NULL;
    }
    free(table->items);
    table->items = NULL;
    free(table->bucket_sizes);
    table->bucket_sizes = NULL;
    free(table);
    table = NULL;
    return 0;
}
