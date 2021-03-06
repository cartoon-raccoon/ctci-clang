#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct node {
    struct node *next;
    void *data;
} node;

typedef struct linkedlist {
    size_t len;
    node * head;
} llist_t;

// Creates a new linked list and returns its pointer
llist_t *llist_create();
// Pushes a new item into the front of the list
int list_push(llist_t *list, void *item);
// Appends a new item to the back of the list
int list_append(llist_t *list, void *item);
// Insert an item into the list at a certain index
int list_insert(llist_t *list, size_t idx, void *item);
// Get a pointer to an item in the linked list
void *list_get(llist_t *list, size_t idx);
// Removes an item from index idx in the list
void *list_remove(llist_t *list, size_t idx);
// deallocates the link list and everything in it
void list_destroy(llist_t *list);

#ifdef __cplusplus
}
#endif