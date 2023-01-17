#include <stdlib.h>

#include "bintree.h"
#include "acutest.h"

/* struct Node {
        int key;
        struct Node *Left;
        struct Node *Right;
}; */

typedef struct Node Tree;

int size;

int is_empty()
{
        return (size <= 0);
}

struct Node* init(int key)
{
        Tree *p = malloc(sizeof(Tree));

        p->Left = 0;
        p->key = key;
        p->Right = 0;

        return p;
}

void insert(Tree *root, int key)
{
        if (root == 0) {
                root->key = key;
                return;
        }
        if (key > root->Left->key) {
                insert(root->Right, key);
        }
                insert(root->Left, key);
}

void in_order_traverse(Tree *root)
{
        if (root == 0) {
                return;
        }

        in_order_traverse(root->Left);
        // output[i] = root.Val;
        in_order_traverse(root->Right);
}

void pre_order_traverse(Tree *root)
{
        if (root == 0) {
                return;
        }

        // output[i] = root.Val;
        pre_order_traverse(root->Left);
        pre_order_traverse(root->Right);
}

void post_order_traverse(Tree *root)
{
        if (root == 0) {
                return;
        }

        post_order_traverse(root->Left);
        post_order_traverse(root->Right);
        // output[i] = root.Val;
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/


TEST_LIST = {
        { NULL, NULL }
};
