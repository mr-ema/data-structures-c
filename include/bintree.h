#ifndef TREE_H
#define TREE_H

struct Node {
        int Key;
        struct Node *Left;
        struct Node *Right;
};

struct Node* init(int key);

void insert(struct Node **root, int key);
void delete_key(struct Node **root, int key);
void search(int input);

void pre_traversal();
void in_traversal();
void post_traversal();

#endif // TREE_H

