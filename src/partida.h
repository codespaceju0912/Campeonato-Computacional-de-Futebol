#ifndef PARTIDA_H
#define PARTIDA_H

typedef enum{
    TIME1, //Indica o nó que contém dados do time 1
    TIME2 // Indica o nó que contém dados do time 2
}NodeTime;

typedef struct {
    int id;
    int time1;
    int time2;
    int golsTime1;
    int golsTime2;
} Partida;

#endif 