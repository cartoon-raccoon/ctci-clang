#include <stddef.h>
#include <stdlib.h>

#include "linkedlist.h"

// private function prototypes for abstraction
static int node_push(node *node, void *item);
static int node_append(node *node, void *item);
static void *node_get(node *node, size_t idx, size_t len);

llist_t *llist_create() 
{
    llist_t *list = malloc(sizeof(llist_t));
    if (list == NULL) return NULL;

    // setting initial values
    list->head->next = NULL;
    list->head->data = NULL;
    list->len = 0;

    return list;
}

int list_push(llist_t *list, void *item)
{
    if (node_push(list->head, item)) {
        list->len++;
        return 1;
    }
    return 0;
}

int list_append(llist_t *list, void *item)
{
    if (node_append(list->head, item)) {
        list->len++;
        return 1;
    }

    return 0;
}


void *list_get(llist_t *list, size_t idx)
{
    return node_get(list->head, idx, list->len);
}

static int node_push(node *nd, void *item) 
{
    // allocating a new node
    node *new = malloc(sizeof(node));
    if (new == NULL) return 0;
    new->data = item;
    new->next = NULL;

    // if there are other elements beyond the current node
    if (nd->next) {
        new->next = nd->next;
    }
    nd = new;

    return 1;
}

static int node_append(node *nd, void *item)
{
    // setting a temp variable as a cursor
    node *cur = nd;
    // traversing the list until the end
    while (cur->next != NULL) {
        cur = cur->next;
    }
    // asserting that cursor->next is null
    if (cur->next != NULL) abort();

    // allocating and initializing a new node
    node *new = malloc(sizeof(node));
    if (new == NULL) return 0;
    new->next = NULL;
    new->data = item;

    cur->next = new;

    return 1;
}

static void *node_get(node *nd, size_t idx, size_t len)
{
    // check for ioob
    if (idx >= len) return NULL;

    node *cur = nd;

    // traversing the list
    for (int i = 0; i <= idx; i++) {
        if (cur == NULL) return NULL;
        cur = cur->next;
    }
    
    // if data is NULL we let the user handle it
    return cur->data;
}