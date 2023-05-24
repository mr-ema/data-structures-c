#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node {
        int key;
        struct Node *left;
        struct Node *right;
} Node;

typedef struct Tree {
        Node *root;
        size_t len;
} Tree;


Tree* bst_init() {
        Tree *tree = malloc(sizeof(Tree));
        if (!tree) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        tree->root = NULL;
        tree->len  = 0;

        return tree;
}

void free_tree_recursive(Node *root) {
        if (!root)
                return;

        free_tree_recursive(root->left);
        free_tree_recursive(root->right);

        free(root);
}

void bst_deinit(Tree **self) {
        free_tree_recursive((*self)->root); // Deallocate all nodes within the tree
        free(*self); // Deallocate Tree

        *self = NULL; // Remove the pointer reference to the tree
}

Node* new_node(Node *left, int key, Node *right) {
        Node *node = malloc(sizeof(Node));
        if (!node) {
                fprintf(stderr, "error: memory allocation failed!\n");
                exit(-1);
        }

        node->left  = left;
        node->key   = key;
        node->right = right;

        return node;
}

Node* insert_helper(Node *node, int key) {
        if (!node)
                return new_node(0, key, 0);

        if (key < node->key)
                node->left = insert_helper(node->left, key);
        else
                node->right = insert_helper(node->right, key);

        return node;
}

Node* bst_insert(Tree *self, int key) {
        Node* node = insert_helper(self->root, key);
        if (!(self->root)) {
                self->root = node;
        }

        self->len++;
        return node;
}

Node* bst_search_key(Node *node, int key) {
        if (!node || node->key == key)
                return node;

        if (key < node->key)
                return bst_search_key(node->left, key);

        return bst_search_key(node->right, key);
}

Node* min_key_value(Node *node) {
        Node *temp = node;
        while (temp->left)
                temp = temp->left;

        return temp;
}

Node* delete_helper(Node *node, int key) {
        if (!node)
                return node;

        if (key < node->key) {
                node->left = delete_helper(node->left, key);
        } else if (key > node->key) {
                node->right = delete_helper(node->right, key);
        } else {
                Node *temp;

                if (!(node->left)) {
                        temp = node->right;
                        free(node);
                        return temp;
                } else if (!(node->right)) {
                        temp = node->left;
                        free(node);
                        return temp;
                }

                temp = min_key_value(node->right);

                node->key = temp->key;
                node->right = delete_helper(node->right, temp->key);
        }

        return node;
}

void bst_delete(Tree *self, int key) {
        if (self->len <= 0) {
                fprintf(stderr, "error: fail to delete, the tree is empty!\n");
                return;
        }

        Node *node = delete_helper(self->root, key);
        if (!node) {
                fprintf(stderr, "key: %d does not exist!\n", key);
                return;
        }

        self->len--;
}

int main() {
        Tree* bst = bst_init();

        // Test bst_insert() and bst_search_key()
        bst_insert(bst, 50);
        bst_insert(bst, 30);
        bst_insert(bst, 70);
        bst_insert(bst, 20);
        bst_insert(bst, 40);
        bst_insert(bst, 60);
        bst_insert(bst, 80);

        printf("Searching for keys:\n");
        printf("Key 50: %s\n", bst_search_key(bst->root, 50) ? "Found" : "Not found");
        printf("Key 30: %s\n", bst_search_key(bst->root, 30) ? "Found" : "Not found");
        printf("Key 70: %s\n", bst_search_key(bst->root, 70) ? "Found" : "Not found");
        printf("Key 20: %s\n", bst_search_key(bst->root, 20) ? "Found" : "Not found");
        printf("Key 40: %s\n", bst_search_key(bst->root, 40) ? "Found" : "Not found");
        printf("Key 60: %s\n", bst_search_key(bst->root, 60) ? "Found" : "Not found");
        printf("Key 80: %s\n", bst_search_key(bst->root, 80) ? "Found" : "Not found");
        printf("Key 90: %s\n", bst_search_key(bst->root, 90) ? "Found" : "Not found");

        // Test bst_delete()
        printf("\nDeleting keys:\n");
        bst_delete(bst, 20);
        bst_delete(bst, 70);
        bst_delete(bst, 90);

        printf("Key 20 deleted\n");
        printf("Key 70 deleted\n");
        printf("Key 90 deleted\n");

        printf("\nSearching for keys after deletion:\n");
        printf("Key 20: %s\n", bst_search_key(bst->root, 20) ? "Found" : "Not found");
        printf("Key 70: %s\n", bst_search_key(bst->root, 70) ? "Found" : "Not found");
        printf("Key 90: %s\n", bst_search_key(bst->root, 90) ? "Found" : "Not found");

        bst_deinit(&bst);
}
