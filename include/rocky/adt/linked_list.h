/**
 * @file linked_list.h
 * @brief Generic singly linked list (void * payloads).
 * @ingroup Core
 *
 * The list owns only its nodes. Callers own the data pointers.
 */

#ifndef ROCKY_ADT_LINKED_LIST_H
#define ROCKY_ADT_LINKED_LIST_H

typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedList LinkedList;

struct LinkedListNode {
    void *data;
    LinkedListNode *next;
};

struct LinkedList {
    int length;
    LinkedListNode *head;
};

LinkedList *create_linked_list(void);
void free_linked_list(LinkedList *ll);
void *linked_list_get(LinkedList *ll, int index);
void linked_list_append(LinkedList *ll, void *data);
void linked_list_insert(LinkedList *ll, void *data, int index);
void *linked_list_pop(LinkedList *ll);
void *linked_list_delete(LinkedList *ll, int index);

#endif /* ROCKY_ADT_LINKED_LIST_H */
