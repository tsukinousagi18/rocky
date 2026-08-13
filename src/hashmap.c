#include "rocky/adt/hashmap.h"
#include <stdlib.h>
#include <string.h>


/*
 * djb2 string hash function.
 * Converts a string into an unsigned integer hash value.
 */
static unsigned long hashmap_hash(const char* str) {
	unsigned long hash = 5381;
	int c;
	while((c = *str++)) {
		hash = ((hash << 5) + hash) + (unsigned char)c; // hash × 32 + hash + c
	}
	return hash;
}

HashMap* create_hashmap(int capacity) {
	if (capacity <= 0) { // capacity -> no of bucekets the caller wants
		capacity = 16; // default capacity
	}

	HashMap* map = (HashMap*)malloc(sizeof(HashMap));
	if (!map) {
		return NULL;
	}

	map->capacity = capacity;
	map->size = 0;


	// // Allocate memory for the hashmap's bucket array.
	// The array contains 'capacity' HashMapNode pointers, one for each bucket.
	// calloc() initializes all allocated memory to zero, so every bucket starts as NULL.
	// The cast converts the returned pointer to HashMapNode**.
	map->buckets = (HashMapNode**)calloc((size_t)capacity, sizeof(HashMapNode*));

	if (!map->buckets) {
		free(map);
		return NULL;
	}

	return map;
}

/*
 * Frees the hashmap and all bucket nodes.
 * Does NOT free the keys or values stored inside.
 */
void free_hashmap(HashMap* map)
{
	if (!map)
	{
		return;
	}

	for (int i = 0; i < map->capacity; i++)
	{
		HashMapNode* node = map->buckets[i]; // node points to the first node in that bucket.

		while (node)
		{
			HashMapNode* next = node->next;
			free(node);
			node = next;
		}
	}

	free(map->buckets);
	free(map);
}

/*
 * Returns the value associated with a key.
 * Returns NULL if the key is not found.
 */
void* hashmap_get(HashMap* map, const char* key)
{
	if (!map || !key)
	{
		return NULL;
	}

	// determines which bucket the key should be in
	unsigned long h = hashmap_hash(key) % (unsigned long)map->capacity;

	// first node of that bucket's LL
	HashMapNode* node = map->buckets[h];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			return node->value;
		}

		node = node->next;
	}

	return NULL;
}

/*
 * Checks whether a key exists in the hashmap.
 * Returns 1 if found, otherwise 0.
 */
int hashmap_contains(HashMap* map, const char* key)
{
	if (!map || !key)
	{
		return 0;
	}

	unsigned long h = hashmap_hash(key) % (unsigned long)map->capacity;

	HashMapNode* node = map->buckets[h];

	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			return 1;
		}

		node = node->next;
	}

	return 0;
}

/*
 * Inserts a new key-value pair.
 * If the key already exists, its value is updated.
 */
void hashmap_set(HashMap* map, const char* key, void* value)
{
	if (!map || !key)
	{
		return;
	}

	unsigned long h = hashmap_hash(key) % (unsigned long)map->capacity;

	HashMapNode* node = map->buckets[h];

	// Update existing key 
	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			node->value = value;
			return;
		}

		node = node->next;
	}

	// Insert new node 
	HashMapNode* new_node = (HashMapNode*)malloc(sizeof(HashMapNode));

	if (!new_node)
	{
		return;
	}

	new_node->key = key;
	new_node->value = value;

	new_node->next = map->buckets[h];
	map->buckets[h] = new_node;

	map->size++;
}

/*
 * Removes a key from the hashmap.
 * Returns the associated value if found,
 * otherwise returns NULL.
 */
void* hashmap_delete(HashMap* map, const char* key)
{
	if (!map || !key)
	{
		return NULL;
	}

	unsigned long h = hashmap_hash(key) % (unsigned long)map->capacity;

	HashMapNode* node = map->buckets[h];
	HashMapNode* prev = NULL;

	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			if (prev)
			{
				prev->next = node->next;
			}
			else
			{
				map->buckets[h] = node->next;
			}

			void* value = node->value;

			free(node);
			map->size--;

			return value;
		}

		prev = node;
		node = node->next;
	}

	return NULL;
}

