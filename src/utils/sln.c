#ifndef SLN_C
#define SLN_C 0

#include <stdlib.h>


typedef struct sln
{
    void* data;
    SimpleLinkedNode* next;
} SimpleLinkedNode;


void sln_free(SimpleLinkedNode* n)
{
    if(n != NULL)
        free(n);
}


void sln_rec_free(SimpleLinkedNode* n)
{
    for(SimpleLinkedNode* next; next != NULL; n = next)
    {
        next = n->next;
        sln_free(n);
    }
}

#endif