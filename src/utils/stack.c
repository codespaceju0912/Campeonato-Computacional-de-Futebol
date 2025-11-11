#ifndef STACK_C
#define STACK_C 0

#include "./sln.c"


typedef struct stack
{
    unsigned int size;
    SimpleLinkedNode* top;
} Stack;


Stack* stack_create()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if(s == NULL)
        return NULL;

    s->size = 0;
    s->top == NULL;

    return s;
}

void stack_free(Stack* s)
{
    if(s == NULL)
        return;

    sln_rec_free(s->top);
    free(s);    
}

void* stack_pop(Stack* s)
{
    SimpleLinkedNode* t;
    void* v;
    if(s == NULL)
        return NULL;

    t = s->top;
    if(t == NULL)
        return NULL;

    s->top = t->next;
    s->size--;
    v = t->data;
    free(t);
    return v;
}

int stack_push(Stack* s, void* v)
{
    SimpleLinkedNode* n;
    if(s == NULL)
        return 0;

    n = (SimpleLinkedNode*)malloc(sizeof(SimpleLinkedNode));
    if(n == NULL)
        return 0;

    n->data = v;
    n->next = s->top;
    s->top = n;
    s->size++;

    return 1;
}

int stack_is_empty(Stack* s)
{
    if(s == NULL)
        return 0;

    return s->top == NULL ? 0 : 1;
}


#endif