# Linked List - Linear Data Structure
`Linked List` can be defined as collection of `objects` called `nodes` that are randomly stored in `heap memory`.

</br>

> __Note__\
> I'm not explaining operations on a linked list here.\
> However you can look into the code and I will be leaving links to videos that explain it in detail.

</br>

## Navigation
- **List**
  - [Intro](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#intro)
  - [Singly List](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#singly-list)
  - [Doubly List](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#doubly-list)
  - [Circular List](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#circular-list)
  - [Doubly Circular List](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#doubly-circular-list)
  - [Unrolled List](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#unrolled-list)

-  **Operations**
    - [Singly List Insertion - Video](https://www.youtube.com/watch?v=dq3F3e9o2DM&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=11)
    - [Singly List Deletion - Video](https://www.youtube.com/watch?v=ClvYytk5Rlg&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=12)
    - [Doubly List Insertion - Video](https://www.youtube.com/watch?v=v4szCPs9yEY&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=17)
    - [Doubly List Deletion - Video](https://www.youtube.com/watch?v=7yNUXcOcHwE&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=18)
    - [Circular List Insertion - Video](https://www.youtube.com/watch?v=ReGglEXEH08&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=22)
    - [Circular List Deletion - Video](https://www.youtube.com/watch?v=EkE6RHuMx3I&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=23)
    - [Doubly Circular List Insertion - Video](https://www.youtube.com/watch?v=Fa958fGdgx0&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=26)
    - [Doubly Circular List Deletion - Video](https://www.youtube.com/watch?v=ElQxT6hDeNE&list=PLdo5W4Nhv31bbKJzrsKfMpo_grxuLl8LU&index=27)
    - [Unrolled List Insertion & Deletion - Video](https://www.youtube.com/watch?v=PVieySxgEik)
    
- **Security**
  - [Memory Leaks](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#memory-leaks)

</br>

## Resources
- _Computerphile_ - Linked Lists -> [Youtube Video](https://www.youtube.com/watch?v=_jQhALI4ujg)
- _Heap Memory_ -> [OpenDSA](https://opendsa-server.cs.vt.edu/ODSA/Books/CS2/html/HeapMem.html)
- _C - Pointers_ -> [Tutorials Point](https://www.tutorialspoint.com/cprogramming/c_pointers.htm)
- _Pointers and dynamic memory_ - Stack vs Heap -> [Youtube Video](https://www.youtube.com/watch?v=_8-ht2AKyH4)
- _Unrolled Linked List_ -> [Coding Ninjas](https://www.codingninjas.com/codestudio/library/unrolled-linked-list)

</br>
</br>

## Intro
Before continuing, it is important to understand how a link list are allocated in memory, so you don't get too confused. When we using list we also using `Heap Memory`

#### Heap Memory
`Heap` memory, also known as `dynamic` memory, is an alternative to local stack memory. Local memory is quite automatic. Local variables are allocated automatically when a function is called, and they are deallocated automatically when the function exits. Heap memory is different in every way. The programmer explicitly requests that space be allocated. This memory `block` will be of a particular size, ususally determined automatically from the size of the object being created. That memory block (your object) continues to be allocated until something happens that makes it go away. In some languages (noteably, C and C++), an object in heap memory only goes away when the programmer explicitly requests that it be deallocated. So the programmer has much greater control of memory, but with greater responsibility since the memory must now be actively managed. Dropping all references to a memory location without deallocating it is a signficant source of errors in C/C++, and this is so common that it has a name: memory leak. Java removes this source of errors by handling memory deallocation automatically, using garbage collection. The downside is that garbage collection is a slow process that happens at unpredictable times. - [_openDSA_](https://opendsa-server.cs.vt.edu/ODSA/Books/CS2/html/HeapMem.html)

</br>

#### Declaring A Node
```c
// This is a node. A list is composed of many nodes
struct Node {                   // 1
        int Data;               // 2
        struct Node *Next;      // 3 
}*head;                         // 4

// Note: Variables inside struct are call fields.
```
**Let's explain what is happening here**
  1. We declare an `struct`. **A `struct` allow us to group multiple variables into one place**
  2. We declare an integer variable (4 bytes) inside our struct
  3. We declare a pointer (8 bytes) which will point to other struct Node
  4. We use `*head` here to save us of declaring it later. This is the same as do `struct Node *head`
  
> **Note**
> In case you already know what a pointer is. Skip to [Dinamic Memory (Heap)](https://github.com/mr-ema/data-structures-c/tree/main/Structures/list#dinamic-memory-heap).

</br>

**A pointer is a variable that stores the memory address of another variable as its value.**
In `C` we declaring a pointing variable like this `int *pointer`.This can be read as _"a pointer to an integer"_

Finally to access the value of a pointer you have to use the pointer variable preceded by a `*`

#### Pointer In C
```c
// Inizialize an integer variable
int six = 6; // let's assume this get allocated in address 0x45

// Now we inizialize a pointer to `six`
int *pointer = &six; // `&` will give us the address of variable `six`

// Try it your self
printf("six addr: %p\n", &six); 
// If we do `*pointer` we would be accessing the pointer value and not the pointer itself
printf("pointer addr: %p\n", pointer);

// Now we can access `six` value or address as follows
printf("pointer val: %d\n", *pointer); // This print 6

// We can modify `six` through the pointer
*pointer = 69;
printf("pointer new val: %d\n", *pointer); // This print 69
printf("six new val: %d\n", six); // This Also print 69
```

</br>

#### Dinamic Memory (Heap)
```c
struct Node {
        int Data;
        struct Node *Next;
}*head;

/* This will allocates a node into the heap and return a pointer
   to the first field in struct which in this case is 'Data' */
head = malloc(sizeof(struct Node)); // let's assume that this returns 0x1B39
/** We can visualize it like this:
  **************************************************
  * addr  /\_| 0x1B39...0x1B41 | 0x1B41...0x1B49 | *
  * head_/   | Data: nil       | Next: nil       | *
  **************************************************/

// Now we assign values to the fields
head->Data = 69;

// Try it yoursel. Remember include <stdlib.h> and define the struct Node
printf("%p\n", head); // same addr as head->Data
printf("%p\n", &(head->Data)); // address of the first field of Node
printf("%p\n", &(head->Next)); // address will be 8 bytes to the right of head->Data
printf("%d\n", head->Data); // nil or 69
printf("%p\n", head->Next); // nil or a pointer

// This will create another node
head->Next = malloc(sizeof(struct Node)); // let's assume that this return 0x45
/** We can visualize it like this:
  ************************************************************************************
  *       /\_| 0x1B39...0x1B41 | 0x1B41...0x1B49 |  /\_| 0x45...0x4D | 0x4D...0x56 | *
  * head_/   | Data: 69        | Next: 0x45      |_/   | Data: nil   | Next: nil   | *
  ************************************************************************************
  * NOTE: As you can see, in heap memory lotation are not continous.             */

// Now if we do the following.
head->Next = NULL;
/** Altought it seems like you just delete a reference
  * and you don't have nothing to worried about.There is a lot to worried about.
  * In C there is not garbage collector. This means that you have to manually take out the trash.
  * Otherwise the node with address 0x45 will continue in memory causing memory leaks

  * So instead of do head->Next = NULL, what you have to do is free that memory using free().
  
  * Like this:
  *   free(head->Next): this will free that space of memory
  *   head->Next = Null: this will delete the reference

  * NOTE: If you don't delete the reference you will be pointing to an inaccessible memory address causing a crash */
```

</br>

_Graphical Representation_
<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/01-list.svg"
    alt="Heap Memory Graphical Representation"
    title="Heap Memory Graphical Representation"
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
- **Data:** Literally data stored in heap memory
- **Next:** A pointer to the next node also store in heap memory

</br>

#### Singly List In C
```c
struct Node {
        int Data;
        struct Node *next;
} *head;

// Create a list (node)
head = malloc(sizeof(struct Node)); // allocates a node into the heap

/**
  * Let's assume that malloc return a pointer to 0x1B39
  ************************************************
  * head = *0x1B39 -> | Data: (nil) | Next: (nil) | *
  ************************************************/

// Arrow operator -> Allows to access elements in Structures and Unions.
head->Data = 69;

// Let's create another node and let's assume that it returns a pointer to 0x45
head->Next = malloc(sizeof(struct Node));
// So now we can visualize this of the following manner
/******************************************
 | Data: 69 | Next: 0x45 | --> | empty | 
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

#### Doubly List In C
```c
struct Node {
        int Data;
        struct Node *Prev;
        struct Node *Next;
} *head;

// Create a list (node)
head = malloc(sizeof(struct Node)); // allocates a node into the heap

head->Prev = NULL; 
head->Data = 69;

// Now the next field will point to a new node
head->Next = malloc(sizeof(struct Node)); // allocate other node in the heap

// Finally we assign to prev field of the new created node, the previus node which is head
head->Next->Prev = head
```

</br>
</br>

## Circular List
In a circular list **each node links only to the next node exept for the last node which links to the first node**. Here **tail is mandatory** since with tail you can access the first node.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/04-list.svg"
    alt="Circular List Graphical Representation"
    title="Circular List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

#### Circular List In C
```c
struct Node {
        int Data;
        struct Node *Next;
} *tail;

// Create a list (node)
tail = malloc(sizeof(struct Node)); // let's call this node 1

// Inizialize A Node
tail->Data = 69;
tail->Next =  tail;

// Create other node
tail->Next = malloc(sizeof(struct Node)); // let's call this node 2

/** Now the last node (node 2) is not pointing to the first node (node 1) but we know that tail does.
  * So we have to re-assign 'Next' field of node 2 to point to node 1 (first node).
  * We know that tail is pointing to node 1 (first node) so we can assign it tail (tail->Next->Next = tail).
  */
tail->Next->Next = tail; // This may be confusing but with practice and time you will get it

/** In case that you don't get what in the hell tail->Next->Next is doing read this.

  * First tail->Next is accessing node 2
  * And tail->Next->Next is accessing to the Next filed of node 2
  * To a better understanding we could also do
  * node2 = tail->Next;
  * node2->Next = tail; assign last node 'Next' field tail (which point to the first node)
  * Since is a circular list the last node (node 2) has to point to the first node (node 1).
  */


// Finally we have to re-assign tail so it points to the last node which is tail->Next (node 2)
tail = tail->Next; // Now tail is pointing to the last node (node 2).
```

</br>
</br>

## Doubly Circular List
In a doubly circular list **each node links to the next node and the previus node exept for the first node which links to the last node and viceversa**. Here You can use head or tail and you will get o(1) access to the first and last node.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/05-list.svg"
    alt="Doubly Circular List Graphical Representation"
    title="Doubly Circular List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

#### Doubly Circular List In C
```c
struct Node {
        int Data;
        struct Node *Prev;
        struct Node *Next;
} *head;

// Create a list
tail = malloc(sizeof(struct Node)); // allocates a node into the heap

// Inizialize A Node To Better Explaination
tail->Prev = tail;
tail->Data = 69;
tail->Next = tail;

// Now we create another node
tail->Next = malloc(sizeof(struct Node));

// Now we have to re-assign prev so it points to the last node which is tail->Next
tail->Prev = tail->Next;

// Now we have to assign prev field of the new created node to the previus node which is tail
tail->Next->Prev = tail;

// Now we have to assign next field of the new created node to the first node which in this case is also tail
tail->Next->Next = tail;

// Finally we have to re-assign tail so it points to the last node which is tail->Next (see line 132)
tail = tail->Next;
```

</br>
</br>

## Unrolled List
A unrolled list **is a variation on the linked list which stores multiple elements in each node using an array**. This allow us to maximize the use of memory.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/06-list.svg"
    alt="Unrolled List Graphical Representation"
    title="Unrolled List Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

#### Unrolled List In C
```c
struct Node {
        int Len; // track array length
        int Data[3];
        struct Node *Next;
} *head;

// Create a list
head = malloc(sizeof(struct Node)); // allocates a node into the heap

// Since `Data` is an array we have to assign data as follows
head->Data[0] = 3;
head->Len += 1;

head->Data[1] = 6;
head->Len += 1;

head->Data[2] = 9;
head->Len += 1;
```

</br>
</br>

## Memory Leaks
When you're using dynamic memory, you are the responsible for creating and freeing the memory. This means that if you create memory and later on in the program you don't need it anymore, you must free that memory otherwise you will open the way for memory leaks.

</br>

#### Cause Memory Leaks

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
        int Data;
        struct Node *Next;
} *head;

int main() 
{
        head = malloc(sizeof(struct Node));
        
        // Store memory address before delete node to check if continues in memory
        struct Node *temp ;
        
        // --------- This will cause memory leaks ---------
        printf("THIS CAUSE MEMORY LEAKS:\n");
        printf("  NOTE THAT AFTER DELETION YOU STILL GET 1\n\n");
        for (int i = 0; i < 6; i++) {
                head->Next = malloc(sizeof(struct Node));

                head->Next->Data = 1;
                printf("\t\tBefore deletion: %d\n", head->Next->Data);

                // store a reference to node to check if it got deleted
                temp = head->Next;

                head->Next = NULL; // remove reference
                printf("\t\tAfter  deletion: %d\n", temp->Data);
        }
    
        return 0;
}
```

</br>

#### Avoid Memory Leaks

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/08-list.svg"
    alt="Avoid Memory Leaks Graphical Representation"
    title="Avoid Memory Leaks Graphical Representation"
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
        int Data;
        struct Node *Next;
} *head;

int main() 
{
        head = malloc(sizeof(struct Node));
        
        // Store memory address before delete node to check if continues in memory
        struct Node *temp ;
        
        // --------- This will not cause memory leaks ---------
        printf("\n\n\nTHIS DO NOT CAUSE MEMORY LEAKS:\n");
        printf("  NOTE THAT AFTER DELETION 1 GET DELETED AND prinft() OUTPUT THE ADDRESS IN DECIMAL\n");
        printf("  CHECK IT YOURSELF TRANSFORM <ADDR> TO DECIMAL\n\n");
        for (int i = 0; i < 6; i++) {
                head->Next = malloc(sizeof(struct Node));

                head->Next->Data = 1;
                printf("\t\tbefore deletion: %d\n", head->Next->Data);

                // store a reference to node to check if it got deleted
                temp = head->Next;

                free(head->Next); // free node
                head->Next = NULL; // remove reference
                printf("\t\tafter deletion: %d <%p>\n", temp->Data, temp->Data);
        }
    
        return 0;
}
```
