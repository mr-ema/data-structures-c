# Linked List - Linear data Structure
A **Linked List** can be defined as collection of objects called **nodes** that are randomly stored in **heap memory**.

</br>

> __Note__\
> \
> I'm not explaining operations on a linked list here.\
> However you can look into the code and I will be leaving links to videos that explain it in detail.

</br>

## Navigation
**List**
- [Intro](#intro)
- [Singly List](#singly-list)
- [Doubly List](#doubly-list)
- [Circular List](#circular-list)
- [Doubly Circular List](#doubly-circular-list)
- [Unrolled List](#unrolled-list)

**Security**
- [Memory Leaks](#memory-leaks)

</br>

## Resources
- [_Computerphile_ - Linked Lists (Video)](https://www.youtube.com/watch?v=_jQhALI4ujg)
- [_Heap Memory_ - OpenDSA](https://opendsa-server.cs.vt.edu/ODSA/Books/CS2/html/HeapMem.html)
- [_C - Pointers_ - Tutorials Point](https://www.tutorialspoint.com/cprogramming/c_pointers.htm)
- [_Pointers and dynamic memory_ - Stack vs Heap (Video)](https://www.youtube.com/watch?v=_8-ht2AKyH4)
- [_Unrolled Linked List_ - Coding Ninjas](https://www.codingninjas.com/codestudio/library/unrolled-linked-list)

**Linked List Operations**
- [_Singly List Insertion_ (Video)](https://www.youtube.com/watch?v=dq3F3e9o2DM&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=11)
- [_Singly List Deletion_ (Video)](https://www.youtube.com/watch?v=ClvYytk5Rlg&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=12)
- [_Doubly List Insertion_ (Video)](https://www.youtube.com/watch?v=v4szCPs9yEY&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=17)
- [_Doubly List Deletion_ (Video)](https://www.youtube.com/watch?v=7yNUXcOcHwE&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=18)
- [_Circular List Insertion_ (Video)](https://www.youtube.com/watch?v=ReGglEXEH08&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=22)
- [_Circular List Deletion_ (Video](https://www.youtube.com/watch?v=EkE6RHuMx3I&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=23)
- [_Doubly Circular List Insertion_ (Video)](https://www.youtube.com/watch?v=Fa958fGdgx0&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=26)
- [_Doubly Circular List Deletion_ (Video)](https://www.youtube.com/watch?v=ElQxT6hDeNE&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=27)
- [_Unrolled List Insertion & Deletion_ (Video)](https://www.youtube.com/watch?v=PVieySxgEik)

</br>
</br>

## Intro
Before continuing, it is important to understand how a linked list is
allocated in memory to avoid confusion. When using a linked list, we
also utilize the **Heap Memory**.

### Heap Memory
**Heap memory**, also known as **dynamic memory**, is an alternative to
local stack memory. Local memory is quite automatic. Local variables
are allocated automatically when a function is called, and they
are deallocated automatically when the function exits. Heap memory
is different in every way. The programmer explicitly requests that
space be allocated. This memory **block** will be of a particular size,
ususally determined automatically from the size of the object being
created. That memory block (your object) continues to be allocated
until something happens that makes it go away. In some languages
(noteably, C and C++), an object in heap memory only goes away when the
programmer explicitly requests that it be deallocated. So the programmer
has much greater control of memory, but with greater responsibility
since the memory must now be actively managed. Dropping all references
to a memory location without deallocating it is a signficant source
of errors in C/C++, and this is so common that it has a name: memory
leak. Java removes this source of errors by handling memory deallocation
automatically, using garbage collection. The downside is that garbage
collection is a slow process that happens at unpredictable times. -
[_openDSA_](https://opendsa-server.cs.vt.edu/ODSA/Books/CS2/html/HeapMem.html)

</br>

**Declaring A Node**
```c
// This is a node. A list is composed of many nodes.
struct Node {
        int data;               // Field: Holds the data value of the node.
        struct Node *next;      // Field: Points to the next node in the list.
}; // struct: A struct allows us to group multiple variables (fields) into one place.

struct Node *head; // Pointer to the head of the list.


/**
  * Explanation of the code:
  *     1. We declare a struct named Node, which represents a node in the linked list.
  *     2. Inside our Node struct, we have an integer variable named data, which holds the data value of the node.
  *     3. We also have a pointer variable named next, which points to the next node in the linked list.
  *     4. The variable head is declared as a pointer to struct Node, and it represents the head (first node) of the list.
  */

// Overall, this code sets up the basic structure for a linked list, where each node contains
// data and a pointer to the next node in the list. The head pointer points to the first node,
// allowing us to access and manipulate the list.
```

</br>

### Pointers
**A pointer is a variable that stores the memory address of another variable as its value.**
In **C** we declare a pointer variable using the syntax `int *p`.This can be read as _"a pointer to an integer"_

To access the value of a pointer, you use the pointer variable preceded
by a `*`. For example, if `p` is a pointer variable pointing to an
integer, you can access the value it points to by dereferencing the
pointer with `*p`.

**Pointers In C**
```c
#include <stdio.h>

int main() {
        // Initialize an integer variable
        int six = 6; // let's assume this is allocated at address 0x45

        // Now we initialize a pointer to `six`
        int *p = &six; // `&` will give us the address of variable `six`

        // Try it yourself
        printf("Address of six: %p\n", &six); 
        // If we use `*p`, we would be accessing the value stored at the pointer's address, not the address itself
        printf("Address stored in pointer: %p\n", p);

        // Now we can access the value of `six` through the pointer
        printf("Value at the address stored in pointer: %d\n", *p); // This prints 6

        // We can modify the value of `six` through the pointer
        *p = 69;
        printf("New value at the address stored in pointer: %d\n", *p); // This prints 69
        printf("New value of six: %d\n", six); // This also prints 69

        return 0;
}
```

</br>

**Linked List And Dinamic Memory (Heap)**
```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
        int data;
        struct Node *next;
} *head;

int main() {
        // This will allocates a node into the heap and return a pointer
        head = malloc(sizeof(struct Node)); // let's assume that this returns 0x1B39
        /** We can visualize it like this:
          **************************************************
          * addr  /\_| 0x1B39...0x1B41 | 0x1B41...0x1B49 | *
          * head_/   | data: nil       | next: nil       | *
          **************************************************/

        // Now we assign values to the fields
        head->data = 69;

        // Try it yourself. Remember include <stdlib.h> and define the struct Node
        printf("head pointer: %p\n", head);                 // same addr as head->data
        printf("head->data address: %p\n", &(head->data));  // address of the first field of Node
        printf("head->next address: %p\n", &(head->next));  // address will be 8 bytes to the right of head->data
        printf("head->data value: %d\n", head->data);       // nil or 69
        printf("head->next pointer: %p\n", head->next);     // nil or a pointer

        // This will create another node
        head->next = malloc(sizeof(struct Node)); // let's assume that this return 0x45
        /** We can visualize it like this:
          ************************************************************************************
          *       /\_| 0x1B39...0x1B41 | 0x1B41...0x1B49 |  /\_| 0x45...0x4D | 0x4D...0x56 | *
          * head_/   | data: 69        | next: 0x45      |_/   | data: nil   | next: nil   | *
          ************************************************************************************
          * NOTE: As you can see, in heap memory lotation are not continous.             */

        // Now if we do the following.
        head->next = NULL;
        /*
         * Set `head->next` to NULL to delete the reference, but it's important to note that this alone is not sufficient.
         * In C, there is no garbage collector, so manual memory management is required to prevent memory leaks.
         * To properly release the memory occupied by the node with address 0x45, you need to use the `free()` function.
         * Here's how you can do it:
         *   free(head->next); // This will free the space of memory
         *   head->next = NULL; // This will delete the reference
         * If you don't delete the reference, you will continue pointing to an inaccessible memory address, potentially causing a crash.
         */
}
```

</br>

_Graphical Representation_
<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/01-list.svg"
    alt="Linked List And Heap Memory Graphical Representation"
    title="Linked List And Heap Memory Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

</br>
</br>

## Singly List
In a singly list **each node links to only the next node**. Also the **head is mandatory** while the **tail is optional**.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/02-list.svg"
    alt="Singly List Graphical Representation"
    title="Singly List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

### Definitions
- **Head:** Is a pointer to the first node in a list
- **Tail:** Same as head you can create a pointer to the last node in a list
- **Node:** A structure containing two fields which are described below
- **data:** Literally data stored in heap memory
- **next:** A pointer to the next node also store in heap memory

</br>

### Singly List In C
```c
struct Node {
        int data;
        struct Node *next;
} *head;

// Create a list (node)
head = malloc(sizeof(struct Node)); // allocates a node into the heap

/**
  * Let's assume that malloc return a pointer to 0x1B39
  ************************************************
  * head = *0x1B39 -> | data: (nil) | next: (nil) | *
  ************************************************/

// Arrow operator -> Allows to access elements in Structures and Unions.
head->data = 69;

// Let's create another node and let's assume that it returns a pointer to 0x45
head->next = malloc(sizeof(struct Node));
// So now we can visualize this of the following manner
/******************************************
 | data: 69 | next: 0x45 | --> | empty | 
```

</br>
</br>

## Doubly List
In a doubly list **each node links to the next node and the previus node**. Also the **head is mandatory** while the **tail is optional**.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/03-list.svg"
    alt="Doubly List Graphical Representation"
    title="Doubly List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

### Doubly List In C
```c
struct Node {
        int data;
        struct Node *Prev;
        struct Node *next;
} *head;

// Create a list (node)
head = malloc(sizeof(struct Node)); // allocates a node into the heap

head->Prev = NULL; 
head->data = 69;

// Now the next field will point to a new node
head->next = malloc(sizeof(struct Node)); // allocate other node in the heap

// Finally we assign to prev field of the new created node, the previus node which is head
head->next->Prev = head
```

</br>
</br>

## Circular List
In a circular list **each node links only to the next node exept for the
last node which links to the first node**. Here **tail is mandatory**
since with tail you can access the first node.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/04-list.svg"
    alt="Circular List Graphical Representation"
    title="Circular List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

### Circular List In C
```c
struct Node {
        int data;
        struct Node *next;
} *tail;

// Create a list (node)
tail = malloc(sizeof(struct Node)); // let's call this node 1

// Initialize a Node
tail->data = 69;
tail->next = tail;

// Create another node
tail->next = malloc(sizeof(struct Node)); // let's call this node 2

/** Now the last node (node 2) is not pointing to the first node (node 1), but we know that `tail` does.
  * So we have to re-assign the 'next' field of node 2 to point to node 1 (the first node).
  * Since `tail` is pointing to node 1, we can assign `tail` to `tail->next->next` (tail->next->next = tail).
  */
tail->next->next = tail; // This may be confusing, but with practice and time, you will get it.

/** In case you don't understand what `tail->next->next` is doing, read this:

  * First, `tail->next` is accessing node 2.
  * And `tail->next->next` is accessing the 'next' field of node 2.
  * For better understanding, we could also do:
  * struct Node *node2 = tail->next;
  * node2->next = tail; // Assign the last node's 'next' field to `tail`, which points to the first node.
  * Since it is a circular list, the last node (node 2) has to point to the first node (node 1).
  */

// Finally, we have to re-assign `tail` so that it points to the last node, which is `tail->next` (node 2).
tail = tail->next; // Now `tail` is pointing to the last node (node 2).
```

</br>
</br>

## Doubly Circular List
In a doubly circular list **each node links to the next node and the
previus node exept for the first node which links to the last node and
viceversa**. Here You can use head or tail and you will get o(1) access
to the first and last node.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/05-list.svg"
    alt="Doubly Circular List Graphical Representation"
    title="Doubly Circular List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

### Doubly Circular List In C
```c
struct Node {
        int data;
        struct Node *Prev;
        struct Node *next;
} *head;

// Create a list
tail = malloc(sizeof(struct Node)); // allocates a node into the heap

// Inizialize A Node To Better Explaination
tail->Prev = tail;
tail->data = 69;
tail->next = tail;

// Now we create another node
tail->next = malloc(sizeof(struct Node));

// Now we have to re-assign prev so it points to the last node which is tail->next
tail->Prev = tail->next;

// Now we have to assign prev field of the new created node to the previus node which is tail
tail->next->Prev = tail;

// Now we have to assign next field of the new created node to the first node which in this case is also tail
tail->next->next = tail;

// Finally we have to re-assign tail so it points to the last node which is tail->next (see line 132)
tail = tail->next;
```

</br>
</br>

## Unrolled List
A unrolled list **is a variation on the linked list which stores multiple
elements in each node using an array**. This allow us to maximize the
use of memory.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/06-list.svg"
    alt="Unrolled List Graphical Representation"
    title="Unrolled List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

### Unrolled List In C
```c
struct Node {
        int Len; // track array length
        int data[3];
        struct Node *next;
} *head;

// Create a list
head = malloc(sizeof(struct Node)); // allocates a node into the heap

// Since `data` is an array we have to assign data as follows
head->data[0] = 3;
head->Len += 1;

head->data[1] = 6;
head->Len += 1;

head->data[2] = 9;
head->Len += 1;
```

</br>
</br>

## Memory Leaks
When you're using dynamic memory, you are the responsible for creating
and freeing the memory. This means that if you create memory and later
on in the program you don't need it anymore, you must free that memory
otherwise you will open the way for memory leaks.

</br>

### Causing Memory Leaks

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/07-list.svg"
    alt="Memory Leaks Graphical Representation"
    title="Memory Leaks Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
        int data;
        struct Node *next;
} *head;

int main()  {
        head = malloc(sizeof(struct Node));

        // Store memory address before delete node to check if continues in memory
        struct Node *temp ;

        // --------- This will cause memory leaks ---------
        printf("THIS CAUSE MEMORY LEAKS:\n");
        printf("  NOTE THAT AFTER DELETION YOU STILL GET 1\n\n");
        for (int i = 0; i < 6; i++) {
                head->next = malloc(sizeof(struct Node));

                head->next->data = 1;
                printf("\t\tBefore deletion: %d\n", head->next->data);

                // store a reference to node to check if it got deleted
                temp = head->next;

                head->next = NULL; // remove reference
                printf("\t\tAfter  deletion: %d\n", temp->data);
        }

        return 0;
}
```

</br>

### Avoiding Memory Leaks

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/08-list.svg"
    alt="Avoiding Memory Leaks Graphical Representation"
    title="Avoiding Memory Leaks Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>


```c
/*********************************************************************************************
  IMPORTANT

    * THIS EXAMPLE USE FREE() TO AVOID MEMORY LEAKS.

    * THIS PROGRAM WILL TRY TO ACCESS ALREADY FREE MEMORY JUST FOR DEMONSTRATION PURPOSES.
    * YOU SHOULD NEVER DO THIS IN REAL PROGRAMS SINCE IT COULD CAUSE UNDEFINED BEHAVIOR.
    * INSTEAD YOU SHOULD USE A DEBUGGER LIKE VALGRIND. 
**********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct Node {
        int data;
        struct Node *next;
} *head;

int main()  {
        head = malloc(sizeof(struct Node));

        // Store memory address before delete node to check if continues in memory
        struct Node *temp ;

        // --------- This will not cause memory leaks ---------
        printf("\n\n\nTHIS DO NOT CAUSE MEMORY LEAKS:\n");
        printf("  NOTE THAT AFTER DELETION 1 GET DELETED AND prinft() OUTPUT THE ADDRESS IN DECIMAL\n");
        printf("  CHECK IT YOURSELF TRANSFORM <ADDR> TO DECIMAL\n\n");
        for (int i = 0; i < 6; i++) {
                head->next = malloc(sizeof(struct Node));

                head->next->data = 1;
                printf("\t\tbefore deletion: %d\n", head->next->data);

                // store a reference to node to check if it got deleted
                temp = head->next;

                free(head->next); // free node
                head->next = NULL; // remove reference
                printf("\t\tafter deletion: %d <%p>\n", temp->data, temp->data);
        }

        return 0;
}
```
