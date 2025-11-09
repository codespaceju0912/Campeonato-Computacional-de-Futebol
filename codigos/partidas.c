#include "partida.h"
#include <stdio.h>

// Implementação básica para imprimir o resultado (será usada na consulta de partidas)
void Partida_imprimir_resultado(const Partida *p, const char *nome1, const char *nome2) {
    printf("%-3d %-10s %2d x %-2d %-10s\n", 
           p->id, nome1, p->golsTime1, p->golsTime2, nome2);
}