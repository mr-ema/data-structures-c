#include <stdio.h>
#include <stdlib.h>

struct Node {
        int data;
        struct Node* next;
};

struct Node* head = NULL;


void list_insert(int val) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = val;
        newNode->next = head;
        head = newNode;
}

void list_delete() {
        if (head == NULL) {
                printf("List is empty. Nothing to delete.\n");
                return;
        }

        struct Node* temp = head;
        head = head->next;
        free(temp);
}

void list_display() {
        if (head == NULL) {
                printf("List is empty.\n");
                return;
        }

        struct Node* temp = head;
        while (temp != NULL) {
                printf("[%d]->", temp->data);
                temp = temp->next;
        }
        printf("(NULL)\n");
}

int main() {
        // Create an empty list
        list_display(); // Expected output: List is empty.

        // Insert elements
        list_insert(5);
        list_insert(3);
        list_insert(7);

        list_display(); // Expected output: [7]->[3]->[5]->(NULL)

        // Delete elements
        list_delete();
        list_delete();

        list_display(); // Expected output: [5]->(NULL)

        return 0;
}
