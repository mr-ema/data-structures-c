# Tree - NonLinear Data Structure
A **tree** data structure is a non-linear data structure because it
does not store in a sequential manner. It is a hierarchical structure
as elements in a Tree are arranged in multiple levels. In the Tree data
structure, the topmost node is known as a root node. Each node contains
some data, and data can be of any type.

</br>

## Navigation
**Tree**
- [General Tree](https://github.com/mr-ema/data-structures-c/tree/main/Structures/tree#general-tree)
- [Binary Tree](https://github.com/mr-ema/data-structures-c/tree/main/Structures/tree#binary-tree)
- [Balanced Tree](https://github.com/mr-ema/data-structures-c/tree/main/Structures/tree#balanced-tree)
- [Binary Search Tree](https://github.com/mr-ema/data-structures-c/tree/main/Structures/tree#binary-search-tree)
- [Heap](https://github.com/mr-ema/data-structures-c/tree/main/Structures/tree#heap)

</br>
</br>

## Resources
- [_Introduction To Tree_ - Geeks For Geeks](https://www.geeksforgeeks.org/introduction-to-tree-data-structure-and-algorithm-tutorials)

</br>
</br>

## General Tree
A **general tree** data structure has no restriction on the number of nodes. It means that a parent node can have any number of child nodes.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/01-tree.svg"
    alt="General Tree Graphical Representation"
    title="General Tree Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

</br>
</br>

## Binary Tree
A node in a **binary tree** can have a maximum of two child nodes. In the given tree diagram, node B, D, and F are left children, while E, C, and G are the right children.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/02-tree.svg"
    alt="Binary Tree Graphical Representation"
    title="Binary Tree Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

</br>
</br>

## Balanced Tree
If the height of the left sub-tree and the right sub-tree is equal or differs at most by 1, the tree is known as a **balanced tree**.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/03-tree.svg"
    alt="Balanced Binary Tree Graphical Representation"
    title="Balanced Binary Tree Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

## Binary Search Tree
A binary search tree (BST) is a type of binary tree where each node has
at most two children: a left child and a right child. Additionally, the
values in the nodes follow a specific order, where the value of every
node in the left subtree is less than the value of the node itself,
and the value of every node in the right subtree is greater than the
value of the node itself. This ordering property is known as the binary
search tree property.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/04-tree.svg"
    alt="Binary Search Tree Graphical Representation"
    title="Binary Search Tree Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

## Heap
A heap is a specialized tree-based data structure that satisfies the heap
property. The heap property can be defined differently for different
types of heaps, but the most common one is the binary heap, which is
often used to implement priority queues.

In a binary heap, the heap property states that for every node `i` in
the heap, the value stored at `i` is either greater than or equal to (in
a max heap) or less than or equal to (in a min heap) the values of its
children nodes. This means that the root node of a max heap contains the
maximum value in the heap, while the root node of a min heap contains
the minimum value.

Binary heaps are typically implemented as arrays, where the parent-child
relationship is determined by the indices of the array elements. For
a node at index `i`, its left child is located at index `2*i + 1`, and its
right child is located at index `2*i + 2`. Conversely, for a node at index
`j`, its parent is located at index `(j-1)/2`.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/05-tree.svg"
    alt="Heap Graphical Representation"
    title="Heap Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>
