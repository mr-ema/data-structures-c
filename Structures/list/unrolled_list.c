#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
        size_t elem_count;
        struct Node *next;

        int *data;
} Node;

typedef struct {
        size_t len;
        size_t node_capacity;
        size_t threshold;

        struct Node *head;
        struct Node *tail;
} List;


List* list_init(size_t capacity) {
        List *list = malloc(sizeof(List));
        if (!list) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        list->node_capacity = capacity;
        list->threshold = (capacity/2) + 1;

        list->head = NULL;
        list->tail = NULL;
        list->len  = 0;

        return list;
}

void list_clear(List *self) {
        if (self->len <= 0)
                return;

        Node *current = self->head;
        Node *next;

        while (current != NULL) {
                next = current->next;
                free(current->data);
                free(current);
                current = next;
        }

        self->head = NULL;
        self->tail = NULL;
        self->len  = 0;
}

void list_deinit(List **self) {
        list_clear(*self); // Deallocate the list nodes
        free(*self); // Deallocate the list structure

        *self = NULL; // Remove the pointer reference to the list
}

Node* new_node(List *self, int val, Node *next) {
        Node *node = malloc(sizeof(Node));
        if (!node) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        node->data = (int*)malloc(self->node_capacity * sizeof(int));
        if (!(node->data)) {
                fprintf(stderr, "error: memory allocation failed!\n");

                free(node);
                exit(-1);
        }

        node->data[0] = val;
        node->next = next;
        node->elem_count = 0;

        return node;
}

void shift_right(int *arr, size_t size, size_t src, size_t desc) {
        if (src >= desc || desc > size || src < 0) {
                return;
        }

        for (size_t i = desc; i > src; i--)
                arr[i] = arr[i - 1];
}

void shift_left(int *arr, size_t size, size_t src, size_t desc) {
        if (desc <= src  || src > size || src < 0) {
                return;
        }

        for (size_t i = src; i < desc; i++)
                arr[i] = arr[i + 1];
}

int list_is_empty(const List *self) {
        return (self->len <= 0);
}

size_t list_len(const List *self) {
        return self->len;
}

// Adds an element to the head of the list.
void list_add(List *self, int val) {
        if (self->len <= 0) {
                self->head = new_node(self, val, NULL);
                self->tail = self->head;
        } else if (self->head->elem_count < self->node_capacity) {
                shift_right(self->head->data, self->node_capacity, 0, self->head->elem_count);
                self->head->data[0] = val;
        } else {
                Node *fresh_node = new_node(self, val, self->head);

                size_t idx;
                while (fresh_node->elem_count != self->threshold) {
                        idx = (self->head->elem_count - self->threshold) + fresh_node->elem_count;
                        fresh_node->data[++fresh_node->elem_count] = self->head->data[idx];
                }

                self->head->elem_count -= self->threshold;
                self->head = fresh_node;
        }

        self->len++;
        self->head->elem_count++;
}

// Appends an element at the end of the list.
void list_append(List *self, int val) {
        if (self->len <= 0) {
                self->head = new_node(self, val, NULL);
                self->tail = self->head;
        } else if (self->tail->elem_count < self->node_capacity) {
                self->tail->data[self->tail->elem_count] = val;
        } else {
                Node *fresh_node = new_node(self, 0, NULL);
                fresh_node->data[self->threshold] = val;

                size_t idx;
                while (fresh_node->elem_count != self->threshold) {
                        idx = (self->tail->elem_count - self->threshold) + fresh_node->elem_count;
                        fresh_node->data[fresh_node->elem_count++] = self->tail->data[idx];
                }

                self->tail->elem_count -= self->threshold;
                self->tail->next = fresh_node;
                self->tail = fresh_node;
        }

        self->len++;
        self->tail->elem_count++;
}

// Inserts an element at the specified position in the list.
// If the position is greater than the length of the list or less than 0,
// the element is either added to the head (if pos < 0) or appended to the end (if pos > length).
void list_insert(List *self, int val, size_t pos) {
        if (pos > self->len || pos < 0 || self->len <= 0) {
                return (pos < 0 ?  list_add(self, val) : list_append(self, val));
        }

        Node *curr = self->head;
        while (pos > curr->elem_count) {
                pos -= curr->elem_count;
                curr = curr->next;
        }

        if (curr->elem_count < self->node_capacity) {
                shift_right(curr->data, self->node_capacity, pos, curr->elem_count);
                curr->data[pos] = val;
                curr->elem_count++;
        } else {
                int temp_val = curr->data[curr->elem_count - 1];

                Node *fresh_node = new_node(self, 0, curr->next);
                curr->next = fresh_node;

                shift_right(curr->data, self->node_capacity, pos, curr->elem_count);
                curr->data[pos] = val;

                size_t idx;
                while (fresh_node->elem_count != self->threshold) {
                        idx = (curr->elem_count - self->threshold) + fresh_node->elem_count;
                        fresh_node->data[fresh_node->elem_count++] = self->tail->data[idx];
                }

                curr->elem_count -= self->threshold;
                fresh_node->data[fresh_node->elem_count++] = temp_val;

                if (curr == self->tail)
                        self->tail = fresh_node;
        }

        self->len++;
}

// Removes and returns the first element from the list.
int list_chop(List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to chop, list is empty!\n");
                return -1;
        }

        int rem_elem = self->head->data[0];
        self->len--;

        if (self->head->elem_count <= 1) {
                Node *temp = self->head;
                self->head = self->head->next;

                free(temp);
        } else {
                shift_left(self->head->data, self->node_capacity, 0, self->head->elem_count);
                self->head->elem_count--;
        }

        return rem_elem;
}

// Removes the first occurrence of the specified value from the list.
int list_remove(List *self, int val) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to remove, list is empty!\n");
                return -1;
        }

        Node *curr = self->head->next;
        Node *prev = self->head;

        int rem_elem = -1;
        size_t idx = 0;

        while (curr != NULL) {
                for ( ; idx < curr->elem_count; idx++) {
                        if (curr->data[idx] == val) {
                                shift_left(curr->data, self->node_capacity, idx, curr->elem_count);
                                curr->elem_count--;
                                rem_elem = val;
                                break;
                        }
                }

                prev = curr;
                curr = curr->next;
        }

        if (rem_elem <= -1) {
                return -1;
        }

        self->len--;
        if (curr && curr->elem_count <= 0) {
                prev->next = curr->next;
                free(curr);
        }

        return rem_elem;
}

// Removes and returns the last element from the list.
int list_pop(List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to pop, list is empty!\n");
                return -1;
        }

        int rem_elem = self->tail->data[self->tail->elem_count - 1];
        self->len--;

        if (self->tail->elem_count > 1) {
                self->tail->elem_count--;
        } else {
                Node *temp = self->head;
                while (temp->next->next != NULL)
                        temp = temp->next;

                self->tail = temp;
                temp = temp->next;

                self->tail->next = NULL;
                free(temp);
        }

        return rem_elem;
}

void list_display(const List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "list is empty!\n");
                return;
        }

        Node *temp = self->head;
        while (temp != 0) {
                for (int i = 0; i < temp->elem_count; i++)
                        printf("%d->", temp->data[i]);

                temp = temp->next;
        }
        printf("STOP\n");
}

int main() {
        // Initialize a circular list
        List *list = list_init(6);

        // Test adding elements to the head
        list_add(list, 1);
        list_add(list, 2);
        list_add(list, 3);

        // Display the list: Expected output: 3->2->1->
        list_display(list);

        // Test appending elements at the end
        list_append(list, 4);
        list_append(list, 5);
        list_append(list, 6);

        // Display the list: Expected output: 3->2->1->4->5->6->
        list_display(list);

        // Test inserting an element at a specific position
        list_insert(list, 10, 2);
        list_insert(list, 20, 5);

        // Display the list: Expected output: 3->2->10->1->4->20->5->6->
        list_display(list);

        // Test removing an element from the head
        int removed = list_chop(list);
        printf("Removed element: %d\n", removed); // Expected output: 3

        // Display the list: Expected output: 2->10->1->4->20->5->6->
        list_display(list);

        // Test removing the first occurrence of a specific value
        int removed_value = list_remove(list, 4);
        printf("Removed element: %d\n", removed_value); // Expected output: 4

        // Display the list: Expected output: 2->10->1->20->5->6->
        list_display(list);

        // Test removing an element from the end
        int popped = list_pop(list);
        printf("Popped element: %d\n", popped); // Expected output: 6

        // Display the list: Expected output: 2->10->1->20->5->
        list_display(list);

        // Clear the list
        list_clear(list);

        // Display the list after clearing: Expected output: list is empty!
        list_display(list);

        // Test inserting elements after clearing
        list_insert(list, 100, 0);
        list_insert(list, 200, 1);

        // Display the list: Expected output: 200->100->
        list_display(list);

        // Deallocate memory and deinitialize the list
        list_deinit(&list);

        return 0;
}
