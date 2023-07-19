#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
        size_t len;
        size_t capacity;

        int *elems;
} ArrayList;


ArrayList* arraylist_init(size_t initial_capacity) {
        ArrayList *arr = malloc(sizeof(ArrayList));
        if (!arr) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        arr->elems = (int*)malloc(initial_capacity * sizeof(int));
        if (!(arr->elems)) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        arr->capacity = initial_capacity;
        arr->len = 0;

        return arr;
}

void arraylist_deinit(ArrayList **self) {
        free((*self)->elems); // Deallocate array elements
        free(*self); // Deallocate ArrayList struct

        *self = NULL; // Remove the pointer reference to the array list
}

int arraylist_resize(ArrayList *self) {
        self->capacity *= 2;
        self->elems = (int*)realloc(self->elems, sizeof(int) * self->capacity);

        if (!(self->elems)) {
                fprintf(stderr, "error: memory allocation failed!\n");
                return 0;
        }

        return 1;
}

void arraylist_append(ArrayList *self, int val) {
        if (self->len == self->capacity) {
                // don't add the new element if resize fails
                if (!arraylist_resize(self)) return;
        }

        self->elems[self->len++] = val;
}

int arraylist_pop(ArrayList *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to remove, list is empty!\n");
                return -1;
        }

        return self->elems[--self->len];
}

int arraylist_get(ArrayList *self, size_t pos) {
        if (pos >= self->len) {
                fprintf(stderr, "error: index out of bounds!\n");
                return -1;
        }

        return self->elems[pos];
}

void arraylist_insert(ArrayList *self, int val, size_t pos) {
        if (pos > self->len) {
                fprintf(stderr, "error: index out of bounds!\n");
                return;
        } else if (self->len == self->capacity) {
                // don't add the new element if resize fails
                if (!arraylist_resize(self)) return;
        }

        // shift elems
        for (size_t i = self->len; i > pos; i--) {
                self->elems[i] = self->elems[i - 1];
        }

        self->elems[pos] = val;
        self->len++;
}

int main() {
        ArrayList *arrlist = arraylist_init(1);

        {
                int val_to_insert = 20;
                size_t pos_to_insert = 0;
                printf("Inserting value %d at position %zu\n", val_to_insert, pos_to_insert);
                arraylist_insert(arrlist, val_to_insert, pos_to_insert);

                printf("Elements in the array list after insertion: ");
                for (int i = 0; i < arrlist->len; i++)
                        printf("%d ", arraylist_get(arrlist, i));
                printf("\n");
        }

        arraylist_append(arrlist, 1);
        arraylist_append(arrlist, 2);
        arraylist_append(arrlist, 3);

        printf("Elements in the array list: ");
        for (int i = 0; i < arrlist->len; i++)
                printf("%d ", arraylist_get(arrlist, i));
        printf("\n");

        {
                // Test arraylist_insert
                int val_to_insert = 100;
                size_t pos_to_insert = 1;
                printf("Inserting value %d at position %zu\n", val_to_insert, pos_to_insert);
                arraylist_insert(arrlist, val_to_insert, pos_to_insert);

                printf("Elements in the array list after insertion: ");
                for (int i = 0; i < arrlist->len; i++)
                        printf("%d ", arraylist_get(arrlist, i));
                printf("\n");
        }

        // Test arraylist_pop
        int removedElement = arraylist_pop(arrlist);
        printf("Removed element: %d\n", removedElement);

        printf("Elements in the array list after removal: ");
        for (int i = 0; i < arrlist->len; i++)
                printf("%d ", arraylist_get(arrlist, i));
        printf("\n");

        // Test resizing
        arraylist_append(arrlist, 4);
        arraylist_append(arrlist, 5);
        arraylist_append(arrlist, 6);

        printf("Elements in the array list after resizing: ");
        for (int i = 0; i < arrlist->len; i++)
                printf("%d ", arraylist_get(arrlist, i));
        printf("\n");

        arraylist_deinit(&arrlist);

        return 0;
}
