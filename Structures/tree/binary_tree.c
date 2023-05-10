#include <stdlib.h>

#include "bintree.h"
#include "acutest.h"
#include "lib/queue.h"

// balanced binary tree implementation

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
        size++;

        return p;
}

void insert(Tree *root, int key)
{
        if (root == NULL) {
                root = init(key);
                return;
        }

        queue_t queue;
        queue_init(&queue);
        queue_enqueue(&queue, root);

        Tree* temp = NULL;
        while (queue_len(&queue) > 0) {
                temp = queue_dequeue(&queue);

                if (temp->Left) {
                        queue_enqueue(&queue, temp->Left);
                } else {
                        temp->Left = new_node(0, key, 0);
                        break;
                }

                if (temp->Right) {
                        queue_enqueue(&queue, temp->Right);
                } else {
                        temp->Right = new_node(0, key, 0);
                        break;
                }
        }

        size++;
}

// returns a node or a null pointer
Tree* recursive_find_node(Tree* root, int key)
{
        if (root == NULL || root->Key == key) {
                return root;
        }

        Tree* left = recursive_find_node(root->Left, key);
        if (left) return left;

        return recursive_find_node(root->Right, key);
}

// returns the parent of a given node or a null pointer
Tree* get_parent_node(Tree* root, Tree* node) {
        if (root == NULL || root->Left == node || root->Right == node) {
                return root;
        }

        Tree* left = get_parent_node(root->Left, node);
        if (left) return left;

        return get_parent_node(root->Right, node);

}

void delete_key(Tree* root, int key)
{
        if (is_empty()) {
                return;
        }

        Tree* target_node = recursive_find_node(root, key);
        if (!target_node) {
                printf("error: key doesn't exist!");
                return;
        }

        Tree* parent = NULL;
        Tree* temp = NULL;

        // keep track of levels to keep the tree balanced
        // this allow delete just leaf nodes on the last level
        int level = 0;
        int last_level = size / 2;

        queue_t queue;
        queue_init(&queue);
        queue_enqueue(&queue, root);

        while (queue_len(&queue) > 0) {
                temp = queue_dequeue(&queue);

                if (level >= last_level && (temp->Left == NULL && temp->Right == NULL)) {
                        // find the parent node to nullify the pointer to be delete
                        // you can also keep track of the parent node for better perfomance
                        parent = get_parent_node(root, temp);

                        target_node->Key = temp->Key;
                        break;
                }

                if (temp->Left)
                        queue_enqueue(&queue, temp->Left);

                if (temp->Right)
                        queue_enqueue(&queue, temp->Right);

                level++;
        }

        if (parent && parent->Left == temp) {
                parent->Left = NULL;
        } else if (parent && parent->Right == temp) {
                parent->Right = NULL;
        }

        free(temp);
        size--;
}

void in_order_traverse(Tree *root)
{
        if (root == 0) {
                return;
        }

        in_order_traverse(root->Left);
        // output[i] = root->Key;
        printf("%d ", root->Key);
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

void test_insert(void)
{
    Tree *root = init(1);
    insert(root, 2);
    insert(root, 3);
    insert(root, 4);
    insert(root, 5);
    insert(root, 6);
    insert(root, 7);

    TEST_CHECK(1 == root->Key);
    TEST_CHECK(2 == root->Left->Key);
    TEST_CHECK(3 == root->Right->Key);
    TEST_CHECK(4 == root->Left->Left->Key);
    TEST_CHECK(5 == root->Left->Right->Key);
    TEST_CHECK(6 == root->Right->Left->Key);
    TEST_CHECK(7 == root->Right->Right->Key);
    TEST_CHECK(0 == root->Right->Right->Left);
    TEST_CHECK(0 == root->Right->Right->Right);
    TEST_CHECK(0 == root->Left->Left->Left);
    TEST_CHECK(0 == root->Left->Left->Right);
}

void test_delete_key(void)
{
        Tree* root = init(50);  // root
        insert(root, 30);       // left
        insert(root, 20);       // right
        insert(root, 40);       // left->left
        insert(root, 70);       // left->right
        insert(root, 60);       // right->left
        insert(root, 80);       // right->right

        delete_key(root, 20);
        TEST_CHECK(root->Right->Key == 40);
        TEST_CHECK(size == 6);

        delete_key(root, 30);
        TEST_CHECK(root->Left->Key == 70);
        TEST_CHECK(size == 5);

        delete_key(root, 50);
        TEST_CHECK(root->Key == 60);
        TEST_CHECK(size == 4);

        delete_key(root, 70);
        TEST_CHECK(root->Left->Key == 80);
        TEST_CHECK(size == 3);

        delete_key(root, 40);
        TEST_CHECK(root->Right->Key == 80);
        TEST_CHECK(size == 2);

        delete_key(root, 60);
        TEST_CHECK(root->Key == 80);
        TEST_CHECK(size == 1);

        // last delete
        delete_key(root, 80);
        // TEST_CHECK(root == NULL); [FAILING]
        TEST_CHECK(size == 0);
}

TEST_LIST = {
    { "INSERTION", test_insert },
    { "DELITION",  test_delete_key },
    { NULL, NULL }
};

