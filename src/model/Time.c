#ifndef TIME_C
#define TIME_C 0

#include <stdlib.h>
#include "./../../shared/bool.h"

#define TIME_MAX_NAME_SIZE 11
#define TIME_NOT_FOUND_FLAG -1

typedef struct Time {
    int id;
    char name[TIME_MAX_NAME_SIZE];
} Time;


static void tSetName(Time* t, const char* n) {
    register unsigned char i;
    register char c;

    for(i = 0; i < TIME_MAX_NAME_SIZE; i++)
    {
        c = n[i];
        t->name[i] = c;
        if(c == '\0')
            return;
    }
    
    t->name[TIME_MAX_NAME_SIZE] = '\0';
}

Time* newTime(const int id, const char name[TIME_MAX_NAME_SIZE]) {
    Time* t = (Time*)malloc(sizeof(Time));
    if(t == NULL)
        return NULL;

    t->id = id;

    tSetName(t, name);
    
    return t;
}

void freeTime(void* t) {
    if(t == NULL)
        return;

    free(t);
}

int timeGetId(const Time* t) {
    if(t == NULL)
        return TIME_NOT_FOUND_FLAG;

    return t->id;
}

bool timeSetId(Time* t, const int id) {
    if(t == NULL || id < 0)
        return false;
    t->id = id;
    
    return true;
}

char* timeGetName(Time* t) {
    if(t == NULL)
        return NULL;

    return t->name;
}

bool timeSetName(Time* t, char new_nome[TIME_MAX_NAME_SIZE]) {
    if(t == NULL)
        return false;

    tSetName(t, new_nome);
    return true;
}

#endif