#ifndef LIST_H
#define LIST_H

/* Linked List Operations */
void insert_beg(int val);
void insert_after(int pos, int val);
void insert_end(int val);
void delete_first();
void delete_node(int pos);
void delete_last();

/* Helper Funtions */
void init(int val);
int is_empty();
int len();

#endif // LIST_H
