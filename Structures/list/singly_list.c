#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
        int data;
        struct Node *next;
} Node;

typedef struct {
        size_t len;

        struct Node *head;
        struct Node *tail;
} List;


List* list_init() {
        List *list = malloc(sizeof(List));
        if (!list) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

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

        for ( ; self->len > 0; self->len--) {
                next = current->next;
                free(current);
                current = next;
        }

        self->head = NULL;
        self->tail = NULL;
}

void list_deinit(List **self) {
        list_clear(*self); // Deallocate the list nodes
        free(*self); // Deallocate the list structure

        *self = NULL; // Remove the pointer reference to the list
}

Node* new_node(int data, Node *next) {
        Node *node = malloc(sizeof(Node));
        if (!node) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        node->data = data;
        node->next = next;

        return node;
}

size_t list_len(const List *self) {
        return self->len;
}

int list_is_empty(const List *self) {
        return (self->len <= 0);
}

// Adds an element to the head of the list.
void list_add(List *self, int val) {
        if (self->len <= 0) {
                self->head = new_node(val, NULL);
                self->tail = self->head;
        } else {
                self->head = new_node(val, self->head);
        }

        self->len++;
}

// Appends an element at the end of the list.
void list_append(List *self, int val) {
        if (self->len <= 0) {
                self->head = new_node(val, NULL);
                self->tail = self->head;
        } else {
                self->tail->next = new_node(val, NULL);
                self->tail = self->tail->next;
        }

        self->len++;
}

// Inserts an element at the specified position in the list.
// If the position is greater than the length of the list or less than 0,
// the element is either added to the head (if pos < 0) or appended to the end (if pos > length).
void list_insert(List *self, int val, size_t pos) {
        if (pos > self->len || pos < 0 || self->len <= 0) {
                return (pos < 0 ?  list_add(self, val) : list_append(self, val));
        }

        // Use a double pointer to update the node
        Node **temp = &self->head;
        for (size_t i = 0; i < pos; i++)
                temp = &(*temp)->next;

        // update pointer
        *temp = new_node(val, *temp);
        self->len++;
}

// Removes and returns the first element from the list.
int list_chop(List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to chop, list is empty!\n");
                return -1;
        }

        int rem_elem = self->head->data;

        Node *head = self->head;
        self->head = head->next; // new head

        free(head);
        self->len--;

        return rem_elem;
}

// Removes the first occurrence of the specified value from the list.
int list_remove(List *self, int val) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to remove, list is empty!\n");
                return -1;
        }

        Node *temp = self->head;
        Node *prev;
        while (temp->data != val && temp != self->tail) {
                prev = temp;
                temp = temp->next;
        }

        if (temp->data == val) {
                prev->next = temp->next;

                self->len--;
                free(temp);

                return val;
        }

        return -1;
}

// Removes and returns the last element from the list.
int list_pop(List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to pop, list is empty!\n");
                return -1;
        }

        Node *prev = self->head;
        for (int i = 1; i < self->len; i++) {
                prev = prev->next;
        }

        int rem_elem = self->tail->data;

        Node *tail = self->tail;
        self->tail = prev;

        free(tail);
        self->len--;

        return rem_elem;
}

void list_display(const List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "list is empty!\n");
                return;
        }

        Node *temp = self->head;
        for (size_t i = 0; i < self->len; i++) {
                printf("%d->", temp->data);
                temp = temp->next;
        }
        printf("STOP\n");
}

int main() {
        // Initialize a circular list
        List *list = list_init();

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

