#ifndef MODEL_H
#define MODEL_H 0

#include "../../shared/bool.h"

// Definição do tamanho máximo permitido para o nome de um time
#define TIME_MAX_NAME_SIZE 11

// Flag indicando que um time não foi encontrado
#define TIME_NOT_FOUND_FLAG -1

// Definição da estrutura Time
typedef struct Time Time;

/**
 * newTime
 * 
 * Cria e inicializa uma nova instância de `Time` com um ID e nome específicos.
 * 
 * Parâmetros:
 *  - `id`: Identificador único do time.
 *  - `name`: Nome do time, com comprimento máximo de `TIME_MAX_NAME_SIZE` caracteres.
 * 
 * Retorna:
 *  - Um ponteiro para a nova instância de `Time`, ou `NULL` caso ocorra um erro de alocação.
 */
Time* newTime(const int id, const char name[TIME_MAX_NAME_SIZE]);

/**
 * freeTime
 * 
 * Libera a memória alocada para uma instância de `Time`.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para a instância de `Time` a ser liberada.
 * 
 * Retorna:
 *  - Nenhum valor é retornado. A memória do time é desalocada.
 */
void freeTime(void* t);

/**
 * timeGetId
 * 
 * Obtém o ID de um time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para a instância de `Time`.
 * 
 * Retorna:
 *  - O ID do time.
 */
int timeGetId(const Time* t);

/**
 * timeSetId
 * 
 * Define um novo ID para um time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para a instância de `Time`.
 *  - `id`: O novo ID a ser atribuído ao time.
 * 
 * Retorna:
 *  - `true` se o ID foi definido com sucesso.
 *  - `false` caso o time seja `NULL` ou ocorra um erro.
 */
bool timeSetId(Time* t, const int id);

/**
 * timeGetName
 * 
 * Obtém o nome de um time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para a instância de `Time`.
 * 
 * Retorna:
 *  - O nome do time, ou `NULL` se o time for `NULL`.
 */
char* timeGetName(Time* t);

/**
 * timeSetName
 * 
 * Define um novo nome para um time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para a instância de `Time`.
 *  - `new_nome`: O novo nome a ser atribuído ao time, com comprimento máximo de `TIME_MAX_NAME_SIZE` caracteres.
 * 
 * Retorna:
 *  - `true` se o nome foi definido com sucesso.
 *  - `false` caso o time seja `NULL`, ou o nome seja inválido.
 */
bool timeSetName(Time* t, char new_nome[TIME_MAX_NAME_SIZE]);

// Definição da estrutura Partida
typedef struct Partida Partida;

/**
 * newPartida
 * 
 * Cria e inicializa uma nova instância de `Partida` com os dados dos dois times e os gols marcados.
 * 
 * Parâmetros:
 *  - `id`: Identificador único da partida.
 *  - `t1`: Ponteiro para o primeiro time (Time*).
 *  - `t2`: Ponteiro para o segundo time (Time*).
 *  - `golsT1`: Número de gols marcados pelo primeiro time.
 *  - `golsT2`: Número de gols marcados pelo segundo time.
 * 
 * Retorna:
 *  - Um ponteiro para a nova instância de `Partida`, ou `NULL` caso ocorra um erro de alocação.
 */
Partida* newPartida(int id, Time* t1, Time* t2, int golsT1, int golsT2);

/**
 * freePartida
 * 
 * Libera a memória alocada para uma instância de `Partida`.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida` a ser liberada.
 * 
 * Retorna:
 *  - Nenhum valor é retornado. A memória da partida é desalocada.
 */
void freePartida(void* p);

/**
 * partidaGetId
 * 
 * Obtém o ID de uma partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - O ID da partida.
 */
int partidaGetId(Partida* p);

/**
 * partidaGetT1
 * 
 * Obtém o primeiro time (Time*) da partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - Um ponteiro para o primeiro time da partida.
 */
Time* partidaGetT1(Partida* p);

/**
 * partidaGetT2
 * 
 * Obtém o segundo time (Time*) da partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - Um ponteiro para o segundo time da partida.
 */
Time* partidaGetT2(Partida* p);

/**
 * partidaGetGolsT1
 * 
 * Obtém o número de gols marcados pelo primeiro time na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - O número de gols marcados pelo primeiro time.
 */
int partidaGetGolsT1(Partida* p);

/**
 * partidaGetGolsT2
 * 
 * Obtém o número de gols marcados pelo segundo time na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - O número de gols marcados pelo segundo time.
 */
int partidaGetGolsT2(Partida* p);

/**
 * partidaSetGolsT1
 * 
 * Define o número de gols marcados pelo primeiro time na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 *  - `gols`: O número de gols a ser definido para o primeiro time.
 * 
 * Retorna:
 *  - `true` se os gols foram definidos com sucesso.
 *  - `false` caso haja algum erro.
 */
bool partidaSetGolsT1(Partida* p, int gols);

/**
 * partidaSetGolsT2
 * 
 * Define o número de gols marcados pelo segundo time na partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 *  - `gols`: O número de gols a ser definido para o segundo time.
 * 
 * Retorna:
 *  - `true` se os gols foram definidos com sucesso.
 *  - `false` caso haja algum erro.
 */
bool partidaSetGolsT2(Partida* p, int gols);

#endif
