#include <stdio.h>
#include <stdlib.h>

#include "vec.h"

static int op = 0;
char *opname;

int main(void)
{
    vec_t *vec = vec_create(sizeof(int));
    if (vec == NULL) {
        fprintf(stderr, "Vec is null\n");
        goto fail;
    }

    // pushing
    printf("[*] Testing pushing:\n");
    int test = 5;
    int test2 = 10;

    op++;
    opname = "pushing";
    if (vec_push_back(vec, &test)) {
        printf("Op %i: Push 1 successful\n", op);
    } else { goto fail; }
    op++;
    if (vec_push_back(vec, &test2)) {
        printf("Op %i: Push 2 successful\n", op);
    } else { goto fail; }

    // getting
    printf("\n[*] Testing getting:\n");
    op++;
    opname = "getting";
    int *get = vec_get(vec, 1);
    if (get == NULL) { goto fail; }
    else {
        if (*get == 10) {
            printf("Op %i: Get successful\n", op);
        } else {
            fprintf(stderr, "Expected 10 for get(1), got %i\n", *get);
            goto fail;
        }
    }
    op++;
    get = vec_get(vec, 0);
    if (get == NULL) { goto fail; }
    else {
        if (*get == 5) {
            printf("Op %i: Get successful\n", op);
        } else {
            fprintf(stderr, "Expected 5 for get(0), got %i\n", *get);
            goto fail;
        }
    }

    printf("\n[*] Testing removal\n");
    op++;
    opname = "removal";
    printf("Pushing 1, 2, 3, 4 to the vec:\n");
    int numbers[] = {1, 2, 3, 4};
    for (int i = 0; i < 4; ++i) {
        if (!vec_push_back(vec, &numbers[i])) {
            fprintf(stderr, "Op %i: Push %i failed\n", op, i);
            goto fail;
        }
    }

    // vec should now be [5, 10, 1, 2, 3, 4]
    // asserting that it is so
    op++;
    get = vec_get(vec, 2);
    if (*get != 1) {
        fprintf(stderr, "Op %i: Expected 1 for get(2), got %i\n", op, *get);
        goto fail;
    }
    get = vec_get(vec, 3);
    if (*get != 2) {
        fprintf(stderr, "Op %i: Expected 2 for get(3), got %i\n", op, *get);
        goto fail;
    }

    op++;
    if (!vec_remove(vec, 3)) {
        goto fail;
    }
    get = vec_get(vec, 3);
    if (*get != 3) {
        fprintf(stderr, "Op %i: Expected 3 for get(3), got %i\n", op, *get);
        goto fail;
    }

    printf("\n[*] Testing shrinking\n");
    op++;
    opname = "shrinking";
    // vec is now [5, 10, 1, 3, 4]
    if (!vec_remove(vec, 1) || !vec_remove(vec, 0)) {
        goto fail;
    }
    // vec should now be [1, 3, 4]; len 3, cap 8
    if (vec->cap != 8 || vec->len != 3) {
        fprintf(stderr, "Expected 6 for cap, 3 for len, got %lu and %lu\n", vec->cap, vec->len);
        goto fail;
    }
    op++;
    get = vec_get(vec, 0);
    if (*get != 1) {
        fprintf(stderr, "Op %i: Expected 1 for get(0), got %i\n", op, *get);
        goto fail;
    }
    op++;
    if (!vec_shrink(vec)) {
        goto fail;
    }
    if (vec->cap != vec->len || vec->len != 3) {
        fprintf(stderr, "Expected cap and len to be equal, got %lu for len", vec->len);
        goto fail;
    }

    printf("All operations successful\n");
    vec_destroy(vec);
    exit(0);
    

fail:
    fprintf(stderr, "Op %i: %s unsuccessful\n", op, opname);
    exit(1);
}