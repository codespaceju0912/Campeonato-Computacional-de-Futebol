#ifndef PARTIDA_H
#define PARTIDA_H

typedef struct {
    int id; //identificador

    int time1; //id do time 1
    int time2; //id do time 2

    int golsTime1;
    int golsTime2;

} Partida;

void Partida_imprimir_resultado(const Partida *p, const char *nome1, const char *nome2);

#endif