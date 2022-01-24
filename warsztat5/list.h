#ifndef LIST_H
#define LIST_H

#include <stdio.h>


struct ListRec{

    void * storage;
    struct ListRec * next;

};

typedef struct ListRec * listType;


struct ListInfo{

    struct ListRec * firstRec;
    int (*compare)(void*, void*);
    void (*copy)(void*, void*, size_t);
    size_t elem_size;

};

typedef struct ListInfo * List;


void listInitialize(List * list, int (*compare)(void*, void*), void (*copy)(void*, void*, size_t), size_t elem_size);
int listEmpty(List list);
void listDestroy(List * list);
void * listFind(List * list, void * elem);
void listRemove(List * list, void * elem);
void listInsert(List * list, void * elem);
void listTraverse(List list, void (*visit)(void*));
List copyList(List list);
List listReverse(List list);
List reverseList(List list);
int listCount(List list);
int listCompare(List l1, List l2);
void listClear(List* list);
List* splitListInHalf(List* originalList, List* secondHalf);
void concatenateLists(List* list1, List* list2);
void mergeSortedLists(List* firstList, List* secondList);
void listSort(List* list);
#endif