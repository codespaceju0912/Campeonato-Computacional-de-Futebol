#include "partida.h"
#include <stdio.h>
#define MAX_PARTIDA 90

typedef struct partida {
    int id;
    int* time1;
    int* time2;
    int golsTime1;
    int golsTime2;
} Partida;

typedef struct bdpartida{
    int partida[MAX_PARTIDA];
}BDPartida;

FILE 