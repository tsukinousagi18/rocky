#ifndef ROCKY_ADT_HASHMAP_H
#define ROCKY_ADT_HASHMAP_H

#include <stddef.h>

typedef struct HashMapNode{
	const char* key;
	void* value;
	struct HashMapNode* next;
} HashMapNode;

typedef struct HashMap {
	int size;
	int capacity;
	HashMapNode** buckets;  // each bucket contains a pointer to a linked list:
} HashMap;

/* Create a hashmap with the given capacity (must be >0). */
HashMap* create_hashmap(int capacity);

/* Free hashmap internals (nodes + bucket array + struct),
   DOES NOT free keys or values stored in the map. */
void free_hashmap(HashMap* map);

/* Return value pointer for key, or NULL if not present.
   Note: stored value may legitimately be NULL; use hashmap_contains
   to check presence when NULL is a valid stored value. */
void* hashmap_get(HashMap* map, const char* key);

/* Return non-zero if the key exists in the map. */
int hashmap_contains(HashMap* map, const char* key);

/* Insert or replace value for key. The map does not copy or free key/value. */
void hashmap_set(HashMap* map, const char* key, void* value);

/* Remove key from map. Returns associated value pointer (caller owns it) or NULL if not found. */
void* hashmap_delete(HashMap* map, const char* key);

#endif 