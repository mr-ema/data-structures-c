# Queue - Linear Data Structure
Unlike stacks, a `queue` is open at both its ends. One end is always used to insert data `enqueue` and the other is used to remove data `dequeue`.
Queue follows **FIFO** (First-In-First-Out) methodology.

</br>

## Navigation
- **Queue**
  - [Simple Queue](https://github.com/mr-ema/data-structures-c/tree/main/Structures/queue#simple-queue)
  - [Circular Queue](https://github.com/mr-ema/data-structures-c/tree/main/Structures/queue#circular-queue)
  - [Priority Queue](https://github.com/mr-ema/data-structures-c/tree/main/Structures/queue#priority-queue)
  - [Double Ended Queue](https://github.com/mr-ema/data-structures-c/tree/main/Structures/queue#double-ended-queue)

- **Operations**
  - [Enqueue](https://github.com/mr-ema/data-structures-c/tree/main/Structures/queue#enqueue)
  - [Dequeue](https://github.com/mr-ema/data-structures-c/tree/main/Structures/queue#dequeue)

</br>

## Recurses
- _Queue Short Animation_ -> [Youtube Video](https://www.youtube.com/watch?v=ojGf3SH7n48)
- _Queue Applications_ -> [Article](https://www.geeksforgeeks.org/applications-of-queue-data-structure/)
- _Device Queue_ -> [Article](https://www.krivalar.com/OS-device-queue)
- _OS Process Scheduling_ -> [Article](https://www.tutorialspoint.com/operating_system/os_process_scheduling.htm)


</br>
</br>

## Simple Queue
A `simple queue` is the most basic queue. In this `queue`, the `enqueue` operation takes place at the `rear`, while the `dequeue` operation takes place at the `front`. **This kind of queue has the limitation that when `rear` reaches the end of the queue you cannot `enqueue` more elements**

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/01-queue.svg"
    alt="Simple Queue Graphical Representation"
    title="Simple Queue Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
/* Using Array */

#define N 7

int queue[N];
int rear = -1;
int front = -1;

// Simulate Image
enqueue(1); // front = 0 / rear = 0
enqueue(2); // front = 0 / rear = 1
enqueue(3); // front = 0 / rear = 2
enqueue(4); // front = 0 / rear = 3
enqueue(5); // front = 0 / rear = 4
enqueue(6); // front = 0 / rear = 5

dequeue(1);  // front = 1 / rear = 5
enqueue(7); // front = 1 / rear = 6

/* Notes:
      * In this kind of `queue` once `rear` reach the end of an array you can't `enqueue` more elements
      * When `rear` and `front` are equal you have to reset the `queue` (front = -1; rear = -1;)
      * Once it restarts you can re-insert elements until `rear` reaches the end again  */
```

</br>
</br>

## Circular Queue
A `circular queue` is the extended version of a regular `queue` where the last element is connected to the first element.
Thus forming a circle-like structure. **Another thing to point out is that a `circular queue` overcomes `simple queue` limitation**

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/02-queue.svg"
    alt="Circular Queue Graphical Representation"
    title="Circular Queue Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
/* Using Array */

#define N 8

int queue[N];
int rear = -1;
int front = -1;

// Simulate Image
enqueue(10); // front = 0 / rear = 0
enqueue(20); // front = 0 / rear = 1
enqueue(30); // front = 0 / rear = 2
enqueue(40); // front = 0 / rear = 3
enqueue(50); // front = 0 / rear = 4

/* Notes:
      * In this kind of `queue` once `rear` reach the end you have to reset rear to 0
      * And when front reach 0 you have to set front to (N - 1)  */
```

</br>
</br>

## Priority Queue
A `priority queue` is a type of `queue` that arranges elements based on their priority values. Elements with higher priority values are typically retrieved before elements with lower priority values.

Types of `Priority Queue`:
- **Ascending Order Priority Queue:** As the name suggests, in ascending order priority queue, the element with a lower priority value is given a higher priority in the priority list.
- **Descending order Priority Queue:** In descending order priority queue, the element with a higher priority value is given a higher priority in the priority list.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/03-queue.svg"
    alt="Priority Queue Graphical Representation"
    title="Priority Queue Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
/* Unordered ascending priority queue (array)*/

#define MAX 4

struct Item {
        int Value;
        int Priority;
};

struct Item queue[MAX];

// Pointer to last inserted item
int ptr  = -1;

// Simulate Image
enqueue(10, 3); // ptr = 0
enqueue(20, 8); // ptr = 1
enqueue(30, 1); // ptr = 2
enqueue(40, 5); // ptr = 3

/* Notes:
      * In this kind of `queue` `rear` and `front` are optional
      * You can have `front` and `rear` in an ordered queue (front = highest priority, rear = lowest priority)
      * You could also use 2 arrays to implement this kind of queue (one for values and another for the priority */
```

</br>
</br>

## Double Ended Queue
`Double ended queues`, called `deques` for short, are a generalized form of the `queue`. It is exactly like a `queue` except that elements can be added to or removed from the `head` or the `tail`.

Types of `deque`:
- **Input Restricted Deque:** In this deque, input is restricted at a single end but allows deletion at both the ends.
- **Output Restricted Deque:** In this deque, output is restricted at a single end but allows insertion at both the ends.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/04-queue.svg"
    alt="Double Ended Queue Graphical Representation"
    title="Double Ended Queue Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
/* Using Array */

#define N 6

int deque[N];
int rear = -1;
int front = -1;

// Simulate Image
enqueue_rear(1); // front = 0 / rear = 0
enqueue_rear(2); // front = 0 / rear = 1
enqueue_rear(3); // front = 0 / rear = 2
enqueue_rear(4); // front = 0 / rear = 3
enqueue_rear(5); // front = 0 / rear = 4
enqueue_rear(6); // front = 0 / rear = 5
enqueue_rear(7); // front = 0 / rear = 5

enqueue_rear(n); // front = 0 / rear = 6
dequeue_rear(7); // front = 0 / rear = 5

dequeue_front(1);  // front = 1 / rear = 5
enqueue_front(n); // front = 0 / rear = 5

/* Notes:
      * In this kind of `queue` you can insert of both ends (front and rear)
      * Operations in a `deque` are quite similar to the ones in a `circle queue` */
```

</br>
</br>

## Enqueue
`Enqueue` operation consist in add an element to the `rear` of a `queue`.

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/05-queue.svg"
    alt="Enqueue Operation Graphical Representation"
    title="Enqueue Operation Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
/* Simple Enqueue */

void enqueue(int value)
{
        if (is_full()) {
                printf("Queue Is Full\n");
                return;
        } else if (is_empty()) {
                // Increment both pointer in first insert
                front++;
        }

        queue[++rear] = value; // add element to rear
}
```

</br>
</br>

## Dequeue
`Dequeue` operation consist in remove an element from `front`. So the next element in line can be attended. 

</br>

<p  align="center">
  <img
    src="https://github.com/mr-ema/data-structures-c/blob/main/art/06-queue.svg"
    alt="Dequeue Operation Graphical Representation"
    title="Dequeue Operation Graphical Representation"
    style="display: inline-block; margin: 0 auto; height: auto; width: 80%;">
</p>

```c
/* Simple Dequeue */

void dequeue()
{
        if (is_empty()) {
                printf("Queue Is Empty\n");
                return;
        } else if (front == rear) {
                // Reset queue
                rear = -1;
                front = -1;
                return;
        }

        front++; // In an array queue we just increment front pointer
}
```
