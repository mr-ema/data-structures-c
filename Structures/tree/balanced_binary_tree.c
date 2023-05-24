#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "lib/queue.h"

DECLARE_QUEUE(Queue, struct Node*);
typedef struct Node {
        int key;
        struct Node *left;
        struct Node *right;
} Node;

typedef struct Tree {
        struct Node *root;
        size_t len;
} Tree;


Tree* bt_init() {
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

void bt_deinit(Tree **self) {
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

void bt_insert(Tree *self, int key) {
        if (!(self->root)) {
                self->root = new_node(0, key, 0);
                return;
        }

        Queue *queue = queue_init(self->len + 1);
        queue_enqueue(queue, self->root);

        Node *temp = NULL;
        while (queue_len(queue) > 0) {
                temp = queue_dequeue(queue);

                if (temp->left) {
                        queue_enqueue(queue, temp->left);
                } else {
                        temp->left = new_node(0, key, 0);
                        break;
                }

                if (temp->right) {
                        queue_enqueue(queue, temp->right);
                } else {
                        temp->right = new_node(0, key, 0);
                        break;
                }
        }

        self->len++;
        queue_deinit(&queue);
}

Node* recursive_find_node(Node *root, int key) {
        if (!root || root->key == key) {
                return root;
        }

        Node* left = recursive_find_node(root->left, key);
        if (left) return left;

        return recursive_find_node(root->right, key);
}

Node* get_parent_node(Node *root, Node *node) {
        if (!root || root->left == node || root->right == node) {
                return root;
        }

        Node* left = get_parent_node(root->left, node);
        if (left) return left;

        return get_parent_node(root->right, node);
}

void bt_delete(Tree **self, int key) {
        if ((*self)->len <= 0) {
                fprintf(stderr, "error: fail to delete, the tree is empty!\n");
                return;
        }

        Node* target_node = recursive_find_node((*self)->root, key);
        if (!target_node) {
                fprintf(stderr, "error: key doesn't exist!\n");
                return;
        }

        Node *parent = NULL;
        Node *temp = NULL;

        // keep track of levels to keep the tree balanced
        // this allow delete just leaf nodes on the last level
        int level = 0;
        int last_level = (*self)->len / 2;

        Queue *queue = queue_init((*self)->len + 1);
        queue_enqueue(queue, (*self)->root);

        while (queue_len(queue) > 0) {
                temp = queue_dequeue(queue);

                if (level >= last_level && (temp->left == NULL && temp->right == NULL)) {
                        // find the parent node to nullify the pointer to be delete
                        // you can also keep track of the parent node for better perfomance
                        parent = get_parent_node((*self)->root, temp);

                        target_node->key = temp->key;
                        break;
                }

                if (temp->left)
                        queue_enqueue(queue, temp->left);

                if (temp->right)
                        queue_enqueue(queue, temp->right);

                level++;
        }

        if (parent && parent->left == temp) {
                parent->left = NULL;
        } else if (parent && parent->right == temp) {
                parent->right = NULL;
        } else {
                // if not parent make the root node 'NULL'
                *self = NULL;
        }

        free(temp);
        (*self)->len--;
        queue_deinit(&queue);
}

void bt_inorder(Node *root) {
        if (root == 0)
                return;

        bt_inorder(root->left);
        printf("%d ", root->key);
        bt_inorder(root->right);
}

void bt_preorder(Node *root) {
        if (root == 0)
                return;

        printf("%d ", root->key);
        bt_preorder(root->left);
        bt_preorder(root->right);
}

void bt_postorder(Node *root) {
        if (root == 0)
                return;

        bt_postorder(root->left);
        bt_postorder(root->right);
        printf("%d ", root->key);
}

int main() {
        Tree* bt = bt_init();

        // Test bt_insert()
        bt_insert(bt, 50);
        bt_insert(bt, 30);
        bt_insert(bt, 70);
        bt_insert(bt, 20);
        bt_insert(bt, 40);
        bt_insert(bt, 60);
        bt_insert(bt, 80);

        printf("In-order traversal: ");
        bt_inorder(bt->root);
        printf("\n");

        printf("Pre-order traversal: ");
        bt_preorder(bt->root);
        printf("\n");

        printf("Post-order traversal: ");
        bt_postorder(bt->root);
        printf("\n");

        // Test bt_delete()
        bt_delete(&bt, 20);
        bt_delete(&bt, 70);

        printf("In-order traversal after deletion: ");
        bt_inorder(bt->root);
        printf("\n");

        // Test bt_delete() on an empty tree
        bt_delete(&bt, 30);

        // Test recursive_find_node() and get_parent_node()
        Node* node30 = recursive_find_node(bt->root, 30);
        Node* parent30 = get_parent_node(bt->root, node30);
        printf("Parent of node 30: %p\n", parent30);

        Node* node40 = recursive_find_node(bt->root, 40);
        Node* parent40 = get_parent_node(bt->root, node40);
        printf("Parent of node 40: %p\n", parent40);

        Node* node80 = recursive_find_node(bt->root, 80);
        Node* parent80 = get_parent_node(bt->root, node80);
        printf("Parent of node 80: %p\n", parent80);

        // Test bt_delete() on the root node
        bt_delete(&bt, 50);

        printf("In-order traversal after deleting the root node: ");
        bt_inorder(bt->root);
        printf("\n");

        bt_deinit(&bt);
}
