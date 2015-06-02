#ifndef LIST_H
#define LIST_H

#ifdef __cplusplus
#   include <cstdlib>
#   include <cstdio>
#else
#   include <stdlib.h>
#   include <stdio.h>
#endif

typedef struct Link{
    void *data;
    struct Link *next;
}Link;

typedef struct LinkedList{
    Link *head;
    Link *tail;
}LinkedList;

LinkedList *createLinkedList();
void destroyLinkedList(LinkedList *list);
void pushData(LinkedList *list, void *data);
void popData(LinkedList *list, void *data);

#endif /* LIST_H */
