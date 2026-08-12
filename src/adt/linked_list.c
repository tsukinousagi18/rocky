/**
 * @file linked_list.c
 * @brief Generic singly linked list implementation.
 * @ingroup Core
 */

#include <rocky/adt/linked_list.h>

#include <stdlib.h>

static LinkedListNode *node_at(LinkedList *ll, int index) {
    if (!ll || index < 0 || index >= ll->length) {
        return NULL;
    }

    LinkedListNode *cur = ll->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur;
}

LinkedList *create_linked_list(void) {
    LinkedList *ll = malloc(sizeof(LinkedList));
    if (!ll) {
        return NULL;
    }
    ll->length = 0;
    ll->head = NULL;
    return ll;
}

void free_linked_list(LinkedList *ll) {
    if (!ll) {
        return;
    }

    LinkedListNode *cur = ll->head;
    while (cur) {
        LinkedListNode *next = cur->next;
        free(cur);
        cur = next;
    }

    free(ll);
}

void *linked_list_get(LinkedList *ll, int index) {
    LinkedListNode *node = node_at(ll, index);
    if (!node) {
        return NULL;
    }
    return node->data;
}

void linked_list_append(LinkedList *ll, void *data) {
    if (!ll) {
        return;
    }

    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    if (!node) {
        return;
    }
    node->data = data;
    node->next = NULL;

    if (!ll->head) {
        ll->head = node;
    } else {
        LinkedListNode *cur = ll->head;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = node;
    }
    ll->length++;
}

void linked_list_insert(LinkedList *ll, void *data, int index) {
    if (!ll || index < 0 || index > ll->length) {
        return;
    }

    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    if (!node) {
        return;
    }
    node->data = data;

    if (index == 0) {
        node->next = ll->head;
        ll->head = node;
    } else {
        LinkedListNode *prev = node_at(ll, index - 1);
        node->next = prev->next;
        prev->next = node;
    }
    ll->length++;
}

void *linked_list_pop(LinkedList *ll) {
    if (!ll || ll->length == 0) {
        return NULL;
    }
    return linked_list_delete(ll, ll->length - 1);
}

void *linked_list_delete(LinkedList *ll, int index) {
    if (!ll || index < 0 || index >= ll->length) {
        return NULL;
    }

    LinkedListNode *old;
    if (index == 0) {
        old = ll->head;
        ll->head = old->next;
    } else {
        LinkedListNode *prev = node_at(ll, index - 1);
        old = prev->next;
        prev->next = old->next;
    }

    void *data = old->data;
    free(old);
    ll->length--;
    return data;
}
