#include <stdlib.h>

#include "bintree.h"
#include "acutest.h"
#include "lib/queue.h"

/* struct Node {
        int Key;
        struct Node *Left;
        struct Node *Right;
}; */

typedef struct Node Tree;

int size;

int is_empty()
{
        return (size <= 0);
}

struct Node* new_node(struct Node* left, int key, struct Node* right)
{
        Tree *p = malloc(sizeof(Tree));

        p->Left = left;
        p->Key = key;
        p->Right = right;

        return p;
}

struct Node* init(int key)
{
        Tree *p = malloc(sizeof(Tree));

        p->Left = 0;
        p->Key = key;
        p->Right = 0;

        return p;
}

void insert(Tree *root, int key)
{
        if (root == NULL) {
                root = new_node(0, key, 0);
                return;
        }

        queue_t queue;
        queue_init(&queue);
        queue_enqueue(&queue, root);

        while (queue_len(&queue) > 0) {
                Tree* temp = queue_dequeue(&queue);
                if (temp->Left != NULL) {
                        queue_enqueue(&queue, temp->Left);
                } else {
                        temp->Left = new_node(0, key, 0);
                        break;
                }

                if (temp->Right != NULL) {
                        queue_enqueue(&queue, temp->Right);
                } else {
                        temp->Right = new_node(0, key, 0);
                        break;
                }
        }
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

void test_insert(void) {
    Tree *root = init(1);
    insert(root, 2);
    insert(root, 3);
    insert(root, 4);
    insert(root, 5);
    insert(root, 6);
    insert(root, 7);

    TEST_ASSERT(1 ==  root->Key);
    TEST_ASSERT(2 ==  root->Left->Key);
    TEST_ASSERT(3 ==  root->Right->Key);
    TEST_ASSERT(4 ==  root->Left->Left->Key);
    TEST_ASSERT(5 ==  root->Left->Right->Key);
    TEST_ASSERT(6 ==  root->Right->Left->Key);
    TEST_ASSERT(7 ==  root->Right->Right->Key);
    TEST_ASSERT(0 ==  root->Right->Right->Left);
    TEST_ASSERT(0 ==  root->Right->Right->Right);
    TEST_ASSERT(0 ==  root->Left->Left->Left);
    TEST_ASSERT(0 ==  root->Left->Left->Right);
}

TEST_LIST = {
    { "test_insert", test_insert },
    { NULL, NULL }
};

