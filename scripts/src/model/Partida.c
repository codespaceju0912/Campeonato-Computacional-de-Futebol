#ifndef PARTIDA_C
#define PARTIDA_C 0

#include <stdlib.h>
#include "../../inc/service/model.h"

// Estrutura que representa uma partida entre dois times.
struct Partida
{
    int id;          // ID único da partida
    Time* t1;        // Ponteiro para o time 1
    Time* t2;        // Ponteiro para o time 2
    int golsT1;      // Gols do time 1
    int golsT2;      // Gols do time 2
};

/**
 * newPartida
 * 
 * Cria uma nova partida entre dois times, com a quantidade de gols marcados por cada um.
 * 
 * Parâmetros:
 *  - `id`: ID único da partida.
 *  - `t1`: Ponteiro para o time 1.
 *  - `t2`: Ponteiro para o time 2.
 *  - `golsT1`: Gols marcados pelo time 1.
 *  - `golsT2`: Gols marcados pelo time 2.
 * 
 * Retorna:
 *  - Um ponteiro para a nova instância de `Partida`, ou `NULL` se a alocação de memória falhar.
 */
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

/**
 * freePartida
 * 
 * Libera a memória alocada para a partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida a ser liberada.
 */
void freePartida(void* p) {
    if(p == NULL)
        return;

    free(p);
}

/**
 * partidaGetId
 * 
 * Obtém o ID da partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida.
 * 
 * Retorna:
 *  - O ID da partida, ou `-1` se o ponteiro para a partida for `NULL`.
 */
int partidaGetId(Partida* p) {
    if(p == NULL)
        return -1;

    return p->id;
}

/**
 * partidaGetT1
 * 
 * Obtém o time 1 da partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida.
 * 
 * Retorna:
 *  - Ponteiro para o time 1, ou `NULL` se o ponteiro para a partida for `NULL`.
 */
Time* partidaGetT1(Partida* p) {
    if(p == NULL)
        return NULL;

    return p->t1;
}

/**
 * partidaGetT2
 * 
 * Obtém o time 2 da partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida.
 * 
 * Retorna:
 *  - Ponteiro para o time 2, ou `NULL` se o ponteiro para a partida for `NULL`.
 */
Time* partidaGetT2(Partida* p) {
    if(p == NULL)
        return NULL;

    return p->t2;
}

/**
 * partidaGetGolsT1
 * 
 * Obtém o número de gols marcados pelo time 1 na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida.
 * 
 * Retorna:
 *  - O número de gols marcados pelo time 1, ou `-1` se o ponteiro para a partida for `NULL`.
 */
int partidaGetGolsT1(Partida* p) {
    if(p == NULL)
        return -1;

    return p->golsT1;
}

/**
 * partidaGetGolsT2
 * 
 * Obtém o número de gols marcados pelo time 2 na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida.
 * 
 * Retorna:
 *  - O número de gols marcados pelo time 2, ou `-1` se o ponteiro para a partida for `NULL`.
 */
int partidaGetGolsT2(Partida* p) {
    if(p == NULL)
        return -1;

    return p->golsT2;
}

/**
 * partidaSetGolsT1
 * 
 * Define o número de gols marcados pelo time 1 na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida.
 *  - `gols`: Número de gols a ser definido para o time 1.
 * 
 * Retorna:
 *  - `true` se os gols foram definidos com sucesso.
 *  - `false` se o ponteiro para a partida for `NULL` ou o número de gols for inválido (menor que 0).
 */
bool partidaSetGolsT1(Partida* p, int gols) {
    if(p == NULL || gols < 0)
        return false;

    p->golsT1 = gols;
    
    return true;
}

/**
 * partidaSetGolsT2
 * 
 * Define o número de gols marcados pelo time 2 na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida.
 *  - `gols`: Número de gols a ser definido para o time 2.
 * 
 * Retorna:
 *  - `true` se os gols foram definidos com sucesso.
 *  - `false` se o ponteiro para a partida for `NULL` ou o número de gols for inválido (menor que 0).
 */
bool partidaSetGolsT2(Partida* p, int gols) {
    if(p == NULL || gols < 0)
        return false;

    p->golsT2 = gols;
    
    return true;
}

#endif
