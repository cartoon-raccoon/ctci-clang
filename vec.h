#include <stddef.h>
#include <stdint.h>

#ifdef _CPLUSPLUS
extern "C" {
#endif

// enum vec_errno {
//     ERROUTOFMEM = 0,
//     ERRNULLVEC = 1,
//     ERRCAPMISMATCH = 2,
// };

typedef struct vec {
    // size of the element to add (allows for generics)
    size_t elem_size;
    // the capacity of the vec
    size_t cap;
    // number of elements in the vec
    size_t len;
    // ptr to the data (byte array)
    char * ptr;
} vec_t;

// creates a new vec and returns a pointer to it
vec_t *vec_create(size_t elem_size);
// creates a new vec with capacity
vec_t *vec_with_cap(size_t elem_size, size_t cap);
// pushes an item to back of the vec 
int vec_push_back(vec_t *vec, const void *item);
// pushes an item to the front of the vec
int vec_push_front(vec_t *vec, const void *item);
// inserts an item at an index
int vec_insert(vec_t *vec, const void *item, size_t idx);
// get a pointer to an element at a certain index
void *vec_get(vec_t *vec, size_t idx);
// remove an item at index idx
// this does not shrink the array down
int vec_remove(vec_t *vec, size_t idx);
// shrink the vec to fit its len
int vec_shrink(vec_t *vec);
// deallocate the vec and all its contents
void vec_destroy(vec_t* vec);

#ifdef _CPLUSPLUS
}
#endif