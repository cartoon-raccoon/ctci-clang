#include <stdlib.h>

#include "linkedlist.h"

static int node_push(node *node, void *item);

llist_t *llist_create() 
{
    llist_t *list = malloc(sizeof(llist_t));
    if (list == NULL) { return NULL; }

    // setting initial values
    list->head->next = NULL;
    list->head->data = NULL;
    list->len = 0;

    return list;
}

int list_push(llist_t *list, void *item)
{
    return node_push(list->head, item);
}

static int node_push(node *nd, void *item) 
{
    node *new = malloc(sizeof(node));
    if (new == NULL) { return 0; }
    new->data = item;
    new->next = NULL;

    if (nd->next) {
        new->next = nd->next;
    }
    nd = new;

    return 1;
}