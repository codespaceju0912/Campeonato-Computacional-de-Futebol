#ifndef LINKED_LIST_C
#define LINKED_LIST_C 0

#include <stdlib.h>
#include "./../../shared/types.h"

typedef struct Node
{
    void* data;
    struct Node* next;
} Node;


/*
    @struct LinkedList essa struct encapusla o conceito de LinkedList.
    Como nenhum comportamento foi especificado, ela irá operar como uma
    fila, pois facilita a ordenação pelo ID dos times.
*/
typedef struct LinkedList
{
    Node* first;
    Node* last;
    unsigned int size;
} LinkedList;


LinkedList* newLinkedList() {
    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    
    if(l == NULL)
        return NULL;

    l->first = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}

static void llAddN(LinkedList* l, Node* n) {
    if(l->first == NULL) {
        l->first = n;
        l->last = n;
    } else {
        l->last->next = n;
        l->last = n;
    }

    l->size++;
}

bool llAdd(LinkedList* l, void* elmt) {
    Node* n;

    if(l == NULL || elmt == NULL)
        return false;

    n = (Node*)malloc(sizeof(Node));
    if(n == NULL)
        return false;

    n->data = elmt;
    n->next = NULL;

    llAddN(l, n);

    return true;
}

bool sllAdd(LinkedList* l, void* elmt) {
    if(elmt == NULL)
        return false;
    
    return llAdd(l, elmt);
}

/*
    getAt try get the node in LinkedList (l) at passed index (idx).

    ATTENTION:
        This function is not safe; if l or l->first are NULL it will cause a Segmentation Fault.

        Additionaly, if the idx is greater than l->size it will cause a Segmentation Fault.

        Only use this function if you know what are you doing.
*/
static Node* getAt(LinkedList* l, const unsigned int idx) {
    register unsigned int i;
    register unsigned int stop = idx;

    Node* n = l->first;

    for(i = 0; i < stop; i++)
        n = n->next;

    return n;
}

void* llGet(LinkedList* l, const unsigned int index) {
    Node* n;

    if(l == NULL)
        return NULL;

    if(index >= l->size)
        return NULL;

    n = getAt(l, index);

    if(n == NULL)
        return NULL;

    return n->data;
}

void* llGetLast(LinkedList* l) {
    if(l == NULL || l->last == NULL)
        return NULL;

    return l->last->data;
}

bool llIsEmpty(LinkedList* l) {
    if(l == NULL)
        return false;

    return l->first == NULL;
}

static void llFree(LinkedList* l) {
    Node* last; 
    Node* current;


    for(current = l->first; current != NULL;) {
        last = current;
        current = current->next;
        free(last);
    }
}

static void llFreeData(LinkedList* l, freeFunc f) {
    Node* last; 
    Node* current;


    for(current = l->first; current != NULL;) {
        f(current->data);
        last = current;
        current = current->next;
        free(last);
    }
}

void llFullFree(LinkedList* l, freeFunc f) {
    if(l == NULL)
        return;

    if(f == NULL)
        llFree(l);
    else
        llFreeData(l, f);

    free(f);
}

LinkedList* llSearchAll(LinkedList* l, searchFunc func) {
    LinkedList* nl = newLinkedList();
    Node* n;
    bool ok;
    if(l == NULL || func == NULL || nl == NULL)
        return NULL;

    for(n = l->first; n != NULL; n = n->next)
        if(func(n->data)) {
            ok = llAdd(nl, n->data);
            if(!ok) {
                llFullFree(nl, NULL);
                return NULL;
            }
        }

    return nl;
}

void llForeach(LinkedList* l, foreachFunc f) {
    Node* n;
    if(l == NULL || f == NULL)
        return;

    for(n = l->first; n != NULL; n = n->next)
        f(n->data);
}

void* llFindFirst(LinkedList* l, findFirstFunc f) {
    Node* n;
    if(l == NULL || f == NULL)
        return NULL;
    
    for(n = l->first; n != NULL; n = n->next)
        if(f(n->data))
            return n->data;
    
    return NULL;
}

bool llRemoveFirstFound(LinkedList* l, removeFunc f) {
    Node* n;
    Node* b = NULL;
    if(l == NULL || f == NULL)
        return false;

    for(n = l->first; n != NULL; n = n->next) {
        if(f(n->data)) {
            if(b == NULL) {
                l->first = n->next;
                if(l->first == NULL)
                    l->last == NULL;
                free(n);
            } else {
                b->next = n->next;
                if(b->next == NULL)
                    l->last = b;
                free(n);
            }

            l->size--;
            return true;
        }

        b = n;
    }

    return false;
}

bool llBoubleSort(LinkedList* l, orderFunc f) {
    Node* a;
    Node* b;
    void* swapAux;
    
    if(l == NULL || f == NULL)
        return false;

    for(a=l->first; a != NULL; a = a->next)
        for(b=l->first; b != NULL; b = b->next)
            if(f(a->data, b->data) == greater_than) {
                swapAux = b->data;
                b->data = a->data;
                a->data = swapAux;
            }

    return true;
}

static Node* nodeCopy(Node* n) {
    Node* cp;

    if(n == NULL)
        return NULL;

    cp = (Node*)malloc(sizeof(Node));
    if(cp == NULL)
        return NULL;

    cp->data = n->data;
    cp->next = NULL;
    return cp;
}

LinkedList* llDeepCopy(LinkedList* l, int start, int end) {
    LinkedList* lCopy;
    Node* n;
    Node* copy;
    Node* lastCopy;
    int i;

    if(l == NULL || l->first == NULL || start < 0 || end < start || end > l->size)
        return NULL;

    lCopy = newLinkedList();
    if(lCopy == NULL)
        return NULL;

    n = l->first;
    for(i=0; i < start; i++)
        n = n->next;

    copy = nodeCopy(n);
    if(copy == NULL) {
        free(copy);
        return NULL;
    }

    lCopy->first = copy;
    lastCopy = copy;
    for(i; i < end; i++) {
        n = n->next;
        if(n == NULL)
            break; // early stop
        copy = nodeCopy(n);
        if(copy == NULL) {
            llFullFree(lCopy, NULL);
            return NULL;
        }
        lastCopy->next = copy;
        lastCopy = copy;
    }

    lCopy->last = copy;
    lCopy->size = end-start;

    return lCopy;
}

int llGetSize(LinkedList* l) {
    if(l == NULL)
        return -1;

    return l->size;
}

#endif