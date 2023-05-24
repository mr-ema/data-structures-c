#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct Node {
        int data;

        struct Node *prev;
        struct Node *next;
} Node;

typedef struct {
        size_t len;
        struct Node *tail;
} List;


List* list_init() {
        List *list = malloc(sizeof(List));
        if (!list) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        list->tail = NULL;
        list->len  = 0;

        return list;
}

void list_clear(List *self) {
        if (self->len <= 0)
                return;

        Node *current = self->tail->next; // Head
        Node *next;

        for ( ; self->len > 0; self->len--) {
                next = current->next;
                free(current);
                current = next;
        }

        self->tail->next = self->tail;
        self->tail->prev = self->tail;
}

void list_deinit(List **self) {
        list_clear(*self);      // Deallocate the list nodes
        free(*self);            // Deallocate the list structure

        *self = NULL;   // Remove the pointer reference to the list
}

Node* new_node(Node *prev, int data, Node *next) {
        Node *node = malloc(sizeof(Node));
        if (!node) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        node->prev = prev;
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
                self->tail = new_node(NULL, val, NULL);
                self->tail->next = self->tail;
                self->tail->prev = self->tail;
        } else {
                Node *fresh_node = new_node(self->tail, val, self->tail->next);
                self->tail->next->prev = fresh_node;  // Update head->prev
                self->tail->next = fresh_node;        // Update head
        }

        self->len++;
}

// Appends an element at the end of the list.
void list_append(List *self, int val) {
        if (self->len <= 0) {
                self->tail = new_node(NULL, val, NULL);
                self->tail->next = self->tail;
                self->tail->prev = self->tail;
        } else {
                self->tail = new_node(self->tail, val, self->tail->next);
                self->tail->prev->next = self->tail; // Update old tail
                self->tail->next->prev = self->tail; // Update head->prev
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
        Node **temp = &self->tail->next;
        for (size_t i = 0; i < pos; i++)
                temp = &(*temp)->next;

        // Create a new node to be inserted, updating the necessary pointers
        Node *fresh_node = new_node((*temp)->prev, val, *temp);

        (*temp)->prev = fresh_node;   // Update the previous pointer of the node to be replaced
        *temp = fresh_node;           // Replace the node at the desired position with the new node
        self->len++;
}

// Removes and returns the first element from the list.
int list_chop(List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to chop, list is empty!\n");
                return -1;
        }

        int rem_elem = self->tail->next->data;
        Node *head = self->tail->next;

        // Set new head
        self->tail->next = head->next; 
        self->tail->next->prev = head->prev;

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

        Node *temp = self->tail->next;
        Node *prev = self->tail;
        while (temp->data != val && temp != self->tail) {
                temp = temp->next;
                prev = prev->next;
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

        int rem_elem = self->tail->data;
        Node *tail = self->tail;

        // Set new tail
        self->tail->next->prev = tail->next; // Update head->prev
        self->tail->prev->next = tail->next; // Update [x->tail->head] to [x->head]
        self->tail = self->tail->prev;

        free(tail);
        self->len--;

        return rem_elem;
}

void list_display(const List *self) {
        if (self->len <= 0) {
                fprintf(stderr, "list is empty!\n");
                return;
        }

        Node *temp = self->tail->next; // Head
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
