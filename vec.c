#include <stdlib.h>
#include <string.h>

#include "vec.h"

#define INIT_CAP 0
#define REALLOC_SCALE 2

// private function to resize the vec if needed
static int vec_ensure_capacity(vec_t *vec);

vec_t *vec_create(size_t elem_size)
{
    return vec_with_cap(elem_size, INIT_CAP);
}

vec_t *vec_with_cap(size_t elem_size, size_t cap)
{
    vec_t *vec = malloc(sizeof(vec_t));

    if (vec == NULL) return NULL;

    // initialization of basic values
    vec->elem_size = elem_size;
    vec->cap = cap;
    vec->len = 0;
    vec->ptr = calloc(vec->cap, vec->cap * elem_size);

    if (vec->ptr == NULL)
    {
        free(vec);
        return NULL;
    }

    return vec;
}

int vec_push_back(vec_t *vec, const void *item)
{
    return vec_insert(vec, item, vec->len);
}

int vec_push_front(vec_t *vec, const void *item)
{
    return vec_insert(vec, item, 0);
}

int vec_insert(vec_t *vec, const void *item, size_t idx) 
{
    
    // if out of bounds, item is null, or out of memory
    if (idx > vec->len || !item || !vec_ensure_capacity(vec))
        return 0;

    // find the byte offset into the vector
    char * const insert_at = vec->ptr + (idx * vec->elem_size);
    // find where to move the rest of the data to
    char * const move_to = insert_at + vec->elem_size;
    // find how many bytes to move
    size_t move_bytes = vec->len - idx;

    // move the data, then insert the data from the item
    memmove(move_to, move_to, move_bytes);
    memcpy(insert_at, item, vec->elem_size);

    // increment length after moving everything
    vec->len++;

    return 1;
}

void *vec_get(vec_t *vec, size_t idx)
{
    if (vec == NULL) return NULL;
    return vec->ptr + (idx * vec->elem_size);
}

int vec_remove(vec_t *vec, size_t idx)
{
    if (vec == NULL) return 0;

    // finding the element to remove
    char * const dest = vec->ptr + (idx * vec->elem_size);
    char * const src = vec->ptr + (idx + 1) * vec->elem_size;
    // finding no. of elements to move
    size_t move_count = vec->len - (idx + 1);

    memmove(dest, src, move_count * vec->elem_size);

    vec->len--;

    return 1;
}

int vec_shrink(vec_t *vec)
{
    // check for null
    if (vec == NULL) return 0;

    // reallocate the vec pointer
    vec->ptr = realloc(vec->ptr, vec->len * vec->elem_size);
    // null check
    if (vec->ptr == NULL) return 0;
    // setting capacity to match size
    vec->cap = vec->len;

    return 1;
}

void vec_destroy(vec_t *vec)
{
    free(vec->ptr);
    free(vec);
}

static int vec_ensure_capacity(vec_t *vec) 
{
    if (vec == NULL || vec->len > vec->cap) return 0;
    // if vec is at capacity
    if (vec->cap == vec->len)
    {
        // set capacity to 1 if it is 0
        if (vec->cap == 0) { 
            vec->cap = 1; 
        } else {
            vec->cap *= REALLOC_SCALE;
        }
        // reallocate      pointer   no. of elems * size of elems
        vec->ptr = realloc(vec->ptr, vec->cap * vec->elem_size);
    }

    if (vec->ptr == NULL) return 0;

    return 1;
}