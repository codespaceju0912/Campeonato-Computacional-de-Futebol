#ifndef LINKED_LIST_H
#define LINKED_LIST_H 0

#include "./../../shared/bool.h"
#include "./../../shared/types.h"

typedef struct LinkedList LinkedList;

// newLinkedList is the consctructor for struct LinkedList.
LinkedList* newLinkedList();

/*
    llAdd adds the element (void* element) as the last element of list (LinkedList* list).

    ATTENTION:
        You can add a NULL element on list, so be carefull.
        You could also use sllAdd() to prevets assing a NULL value in list.

    returns:
        if list is NULL or there is not enough memory to adds the element on list, it will returns false;

        if the operation succesfull, it will return true.
*/
bool llAdd(LinkedList* list, void* element);

/*
    llAdd adds the element (void* element) as the last element of list (LinkedList* list).

    returns:
        if list is NULL, element is NULL, or there is not enough memory to adds the element on list, it will returns false;

        if the operation succesfull, it will return true.
*/
bool sllAdd(LinkedList* l, void* element);


/*
    llGet gets the element on list (LinkedList* list) at given index (unsigned int index)
    If list is NULL or the index is invalid, it will return NULL.
    The first element has index 0.

    EXAMPLE:
        1. If list contains no element an you try to get the element index 0, it will return NULL.
        2. If list contains 2 elements:
            - the index 0 will return the first element;
            - the index 1 will return the last element;
            - the index 2 will return NULL.
*/
void* llGet(LinkedList* list, const unsigned int index);


void* llGetLast(LinkedList* list);

bool llIsEmpty(LinkedList* list);


LinkedList* llSearchAll(LinkedList* l, searchFunc func);

void llFullFree(LinkedList* list, freeFunc freeFunction);


void llForeach(LinkedList* l, foreachFunc f);

void* llFindFirst(LinkedList* l, findFirstFunc f);

bool llBoubleSort(LinkedList* l, orderFunc f);

LinkedList* llDeepCopy(LinkedList* l, int start, int end);

int llGetSize(LinkedList* l);
#endif