#ifndef PARTIDA_C
#define PARTIDA_C 0

#include "./time.c"

typedef struct Partida
{
    int id;
    Time* t1;
    Time* t2;
    int golsT1;
    int golsT2;
} Partida;


Partida* newPartida(int id, Time* t1, Time* t2, int golsT1, int golsT2) {
    Partida* p = (Partida*)malloc(sizeof(Partida));
    if(p == NULL)
        return NULL;

    p->id = id;
    p->t1 = t1;
    p->t2 = t2;
    p->golsT1 = golsT1;
    p->golsT2 = golsT2;

    return p;
}

void freePartida(void* p) {
    if(p == NULL)
        return;

    free(p);
}

#endif