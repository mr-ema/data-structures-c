#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
        struct Node* Prev;
        void* Data;
        struct Node* Next;
} node_t;

typedef struct {
        node_t* Tail;
        int     Size;
} list_t;

node_t* list_new_node(void* data, node_t* next)
{
        node_t* node = malloc(sizeof *node);

        node->Data = data;
        node->Next = next;

        return node;
}

void list_init(list_t* list)
{
        list->Tail = NULL;
        list->Size = 0;
}

int list_len(list_t* list)
{
        return list->Size;
}

int list_is_empty(list_t* list)
{
        return (list->Size <= 0);
}

void list_insert_beg(list_t* list, void* val)
{
        if (list_is_empty(list)) {
                list_init(val);
                return;
        }
        list->Tail->Next = list_new_node(val, list->Tail->Next);
        list->Size++;
}

void list_insert_end(list_t* list, void* val)
{
        if (list_is_empty(list)) {
                return;
        }

        list->Tail->Next = list_new_node(val, list->Tail->Next);
        list->Tail = list->Tail->Next;
        list->Size++;
}

void list_insert_after(list_t* list, int pos, void* val)
{
        if (pos <= 0 || pos >= list->Size) {
                pos <= 0 ? list_insert_beg(list, val) : list_insert_end(list, val);
                return;
        }
        node_t* temp = list->Tail->Next;

        for (int i = 1; i < pos; i++)
                temp = temp->Next;

        temp->Next = list_new_node(val, temp->Next);
        list->Size++;
}

void list_delete_first(list_t* list)
{
        if (list_is_empty(list)) {
                // printf("Underflow Condition\n");
                return;
        }

        node_t* temp = list->Tail->Next;
        list->Tail->Next = temp->Next;

        free(temp);

        list->Size--;
}

void list_delete_last(list_t* list)
{
        if (list_is_empty(list)) {
                // printf("Underflow Condition\n");
                return;
        } 

        node_t* prev = list->Tail;

        for (int i = 1; i < list->Size; i++) {
                prev = prev->Next;
        }

        node_t* temp = list->Tail;

        prev->Next = list->Tail->Next;
        list->Tail = prev;

        free(temp);

        list->Size--;
}

void list_delete_node(list_t* list, int pos)
{
        if (pos <= 1 || pos >= list->Size) {
                pos <= 1 ? list_delete_first(list) : list_delete_last(list);
                return;
        }

        node_t* prev = list->Tail;
        node_t* next = list->Tail->Next;

        for (int i = 1; i < pos; i++) {
                prev = next;
                next = next->Next;
        }

        prev->Next = next->Next;

        free(next);

        list->Size--;
}

#endif /* LIST_H */
