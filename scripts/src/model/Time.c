#ifndef TIME_C
#define TIME_C 0

#include <stdlib.h>
#include "../../inc/service/model.h"
#include "./../../shared/bool.h"

// Estrutura que representa um time com ID e nome.
struct Time {
    int id;                  // ID único do time
    char name[TIME_MAX_NAME_SIZE]; // Nome do time
};

/**
 * tSetName
 * 
 * Define o nome do time na estrutura `Time`, garantindo que o nome não ultrapasse o tamanho máximo especificado por `TIME_MAX_NAME_SIZE`.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para o time.
 *  - `n`: Nome do time (string) a ser atribuído ao time.
 */
static void tSetName(Time* t, const char* n) {
    int i;
    char c;

    for(i = 0; i < TIME_MAX_NAME_SIZE; i++)
    {
        c = n[i];
        t->name[i] = c;
        if(c == '\0')
            return;
    }
    
    t->name[TIME_MAX_NAME_SIZE] = '\0'; // Garante que a string será terminada com '\0'
}

/**
 * newTime
 * 
 * Cria um novo time com um ID e um nome fornecidos.
 * 
 * Parâmetros:
 *  - `id`: ID único do time.
 *  - `name`: Nome do time (string).
 * 
 * Retorna:
 *  - Um ponteiro para a nova instância de `Time`, ou `NULL` se a alocação de memória falhar.
 */
Time* newTime(const int id, const char name[TIME_MAX_NAME_SIZE]) {
    Time* t = (Time*)malloc(sizeof(Time));
    if(t == NULL)
        return NULL;

    t->id = id;
    tSetName(t, name);
    
    return t;
}

/**
 * freeTime
 * 
 * Libera a memória alocada para o time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para o time a ser liberado.
 */
void freeTime(void* t) {
    if(t == NULL)
        return;

    free(t);
}

/**
 * timeGetId
 * 
 * Obtém o ID do time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para o time.
 * 
 * Retorna:
 *  - O ID do time, ou `TIME_NOT_FOUND_FLAG` se o ponteiro para o time for `NULL`.
 */
int timeGetId(const Time* t) {
    if(t == NULL)
        return TIME_NOT_FOUND_FLAG;

    return t->id;
}

/**
 * timeSetId
 * 
 * Define o ID de um time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para o time.
 *  - `id`: Novo ID do time.
 * 
 * Retorna:
 *  - `true` se o ID foi definido com sucesso.
 *  - `false` se o ponteiro para o time for `NULL` ou o ID for inválido (menor que 0).
 */
bool timeSetId(Time* t, const int id) {
    if(t == NULL || id < 0)
        return false;
    
    t->id = id;
    return true;
}

/**
 * timeGetName
 * 
 * Obtém o nome do time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para o time.
 * 
 * Retorna:
 *  - O nome do time (string), ou `NULL` se o ponteiro para o time for `NULL`.
 */
char* timeGetName(Time* t) {
    if(t == NULL)
        return NULL;

    return t->name;
}

/**
 * timeSetName
 * 
 * Define o nome de um time.
 * 
 * Parâmetros:
 *  - `t`: Ponteiro para o time.
 *  - `new_nome`: Novo nome do time (string).
 * 
 * Retorna:
 *  - `true` se o nome foi definido com sucesso.
 *  - `false` se o ponteiro para o time for `NULL`.
 */
bool timeSetName(Time* t, char new_nome[TIME_MAX_NAME_SIZE]) {
    if(t == NULL)
        return false;

    tSetName(t, new_nome);
    return true;
}

#endif
