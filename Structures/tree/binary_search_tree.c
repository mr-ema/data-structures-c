#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* BINARY SEARCH TREE (BST) */

typedef struct Node {
        int Key;
        struct Node *Left;
        struct Node *Right;
} Node;

typedef struct Tree {
        Node *Root;
        unsigned int Size;
} Tree;


/**
 * Initializes a brand new binary search tree.
 * If memory allocation fails, it exits the program with a status code of -1.
 *
 * @return A pointer to the initialized tree.
 */
Tree* BST_init()
{
        Tree *ptr = malloc(sizeof(Tree));
        if (!ptr) {
                perror("error: memory allocation failed");
                exit(-1);
        }

        ptr->Root = NULL;
        ptr->Size = 0;

        return ptr;
}

/**
 * Recursively frees the memory allocated for each node in the tree.
 *
 * @param node The root node of the tree to be freed.
 */
void free_tree(Node *node)
{
        if (!node)
                return;

        free_tree(node->Left);
        free_tree(node->Right);
        free(node);
}

/**
 * Removes the entire tree from dynamic memory.
 *
 * @param tree A pointer to the tree to be deinitialized.
 */
void BST_deinit(Tree **tree) {
        free_tree((*tree)->Root);

        free(*tree);
        *tree = NULL;
}

/**
 * Tries to allocate memory for a new node.
 * If memory allocation fails, it exits the program with a status code of -1.
 *
 * @param left A pointer to the left child node.
 * @param key The key value of the new node.
 * @param right A pointer to the right child node.
 * @return A pointer to the newly allocated node.
 */
Node* BST_new_node(Node *left, int key, Node *right)
{
        Node *ptr = malloc(sizeof(Node));
        if (!ptr) {
                perror("error: memory allocation failed");
                exit(-1);
        }

        ptr->Left  = left;
        ptr->Key   = key;
        ptr->Right = right;

        return ptr;
}

/**
 * Recursively inserts a node into the binary search tree.
 *
 * @param node The current node being considered during insertion.
 * @param key The key value of the node to be inserted.
 * @return A pointer to the updated node structure after insertion.
 */
Node* insert_helper(Node *node, int key)
{
        if (!node)
                return BST_new_node(0, key, 0);

        if (key < node->Key)
                node->Left = insert_helper(node->Left, key);
        else
                node->Right = insert_helper(node->Right, key);


        return node;
}

/**
 * Inserts a node into the binary search tree.
 *
 * @param tree A pointer to the tree.
 * @param key The key value of the node to be inserted.
 * @return A pointer to the inserted node.
 */
Node* BST_insert(Tree *tree, int key)
{
        Node* node = insert_helper(tree->Root, key);
        if (!(tree->Root)) {
                tree->Root = node;
        }

        tree->Size++;
        return node;
}

/*
 * Searches for a key in a given binary search tree.
 * returns a null pointer if key is not founded.
 *
 * @param node The root node of the tree to search.
 * @param key The key to search for.
 * @return A pointer to the node with the matching key, or NULL if the key is not found.
 */
Node* BST_search_key(Node *node, int key)
{
        if (!node || node->Key == key)
                return node;

        if (key < node->Key)
                return BST_search_key(node->Left, key);

        return BST_search_key(node->Right, key);
}

/**
 * Finds the minimum value node in a given subtree rooted at 'node'.
 *
 * @param node The root node of the subtree to search.
 * @return A pointer to the node with the minimum key value in the subtree.
 */
Node* min_key_value(Node *node)
{
        Node *temp = node;
        while (temp->Left)
                temp = temp->Left;

        return temp;
}

/**
 * Recursively deletes a node with the given key from the binary search tree.
 *
 * @param node The current node being considered during deletion.
 * @param key The key value of the node to be deleted.
 * @return A pointer to the updated node structure after deletion.
 */
Node* delete_helper(Node *node, int key)
{
        if (!node)
                return node;

        if (key < node->Key) {
                node->Left = delete_helper(node->Left, key);
        } else if (key > node->Key) {
                node->Right = delete_helper(node->Right, key);
        } else {
                Node *temp;

                if (!(node->Left)) {
                        temp = node->Right;
                        free(node);
                        return temp;
                } else if (!(node->Right)) {
                        temp = node->Left;
                        free(node);
                        return temp;
                }

                temp = min_key_value(node->Right);

                node->Key = temp->Key;
                node->Right = delete_helper(node->Right, temp->Key);
        }

        return node;

}

/**
 * Deletes a node with the given key from the binary search tree.
 *
 * @param tree A pointer to the tree.
 * @param key The key value of the node to be deleted.
 */
void BST_delete(Tree *tree, int key)
{
        Node *node = delete_helper(tree->Root, key);
        if (!node) {
                printf("node does't exist\n");
                return;
        }

        tree->Size--;
}

/**********************************************************
 *                         TESTS                          *
 *********************************************************/
int main(void)
{
        // Initialize the BST
        Tree *tree = BST_init();
        assert(tree->Size == 0);

        /*
              30
             /  \
           10    40
          /  \     \
         6   11    null
        */

        // Test Insert
        BST_insert(tree, 30);
        BST_insert(tree, 10);
        BST_insert(tree, 40);
        BST_insert(tree, 6);
        BST_insert(tree, 11);
        assert(tree->Size == 5);

        Node *root = tree->Root;
        assert(root->Key == 30);
        assert(root->Left->Key == 10);
        assert(root->Right->Key == 40);
        assert(root->Left->Left->Key == 6);
        assert(root->Left->Right->Key == 11);

        // Test Search
        Node *left_child = BST_search_key(root, 10);
        Node *fake_key   = BST_search_key(root, 100);
        assert(left_child != NULL);
        assert(fake_key == NULL);

        // Test Deletion
        BST_delete(tree, 10);
        assert(root->Left->Key == 11);
        assert(tree->Size == 4);

        BST_delete(tree, 30);
        assert(root->Key == 40);
        assert(tree->Size == 3);

        // Additional Test Cases
        BST_insert(tree, 55);
        BST_insert(tree, 20);
        BST_insert(tree, 35);
        assert(root->Right->Key == 55);
        assert(root->Left->Right->Key == 20);
        assert(root->Left->Right->Right->Key == 35);

        BST_delete(tree, 20);
        BST_delete(tree, 35);
        BST_delete(tree, 55);
        assert(root->Left->Right == NULL);
        assert(root->Right == NULL);
        assert(tree->Size == 3);

        // Destroy tree
        BST_deinit(&tree);
        assert(tree == NULL);
        return 0;
}
