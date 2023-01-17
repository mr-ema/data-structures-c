#ifndef ARRAY_H
#define ARRAY_H

// Helpers
int max_size();
int is_full();
int is_empty();
int len();

// Operations
void traverse();
void insert_beg(int val);
void insert_at_pos(int pos, int val);
void insert_end(int val);
void delete_beg();
void delete_at_pos(int pos);
void delete_end();

#endif // ARRAY_H
