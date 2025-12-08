#ifndef PARTIDA_DB_C
#define PARTIDA_DB_C 0

#include <stdio.h>

#include "./../../inc/service/repo.h"
#include "./../../inc/collections/LinkedList.h"

// Estrutura que representa o banco de dados de partidas.
struct PartidaDB {
    LinkedList* partidas;  // Lista de partidas
};

// Instância global do banco de dados de partidas
static PartidaDB partidaDB;
static int partidaIDSearch;  // ID da partida sendo pesquisada
Partida* partidaJournal = NULL;  // Partida em transação

/**
 * partidaDBStartInsertTransaction
 * 
 * Inicia uma transação de inserção para a partida.
 * 
 * Retorna:
 *  - `true` se a transação de inserção já não estiver em andamento.
 *  - `false` caso contrário (se já houver uma transação aberta).
 */
bool partidaDBStartInsertTransaction() {
    if(partidaJournal == NULL)
        return true;
    return false;
}

/**
 * partidaDBInsertCommit
 * 
 * Commit da transação de inserção, adicionando a partida ao banco de dados de partidas.
 * 
 * Retorna:
 *  - `true` se a operação foi bem-sucedida.
 *  - `false` caso contrário (em caso de falha na adição).
 */
bool partidaDBInsertCommit() {
    bool ok;

    ok = sllAdd(partidaDB.partidas, partidaJournal);
    if(!ok) {
        return false;
    }
    partidaJournal = NULL;

    return true;
}

/**
 * partidaDBInsertRollBack
 * 
 * Cancela a transação de inserção, liberando a memória alocada para a partida em transação.
 */
void partidaDBInsertRollBack() {
    if(partidaJournal != NULL) {
        freePartida(partidaJournal);
        partidaJournal = NULL;
    }
}

/**
 * nextPartidaID
 * 
 * Retorna o próximo ID disponível para uma nova partida com base no ID da última partida.
 * 
 * Retorna:
 *  - O próximo ID disponível para uma nova partida.
 */
static int nextPartidaID() {
    Partida* last = (Partida*)llGetLast(partidaDB.partidas);
    return partidaGetId(last) + 1;
}

/**
 * addPartida
 * 
 * Adiciona uma nova partida ao banco de dados de partidas.
 * 
 * Parâmetros:
 *  - `t1ID`: ID do time 1.
 *  - `t2ID`: ID do time 2.
 *  - `gT1`: Gols do time 1.
 *  - `gT2`: Gols do time 2.
 * 
 * Retorna:
 *  - `SUCCESS` se a partida foi adicionada com sucesso.
 *  - Outros valores para indicar erros específicos (ex: time com IDs iguais, memória insuficiente, time inexistente).
 */
AddPartidaReponse addPartida(int t1ID, int t2ID, int gT1, int gT2) {
    Time* t1;
    Time* t2;

    if(partidaDB.partidas == NULL)
        return PARTIDA_DATABASE_NOT_STARTED_YET;
    
    if(partidaJournal != NULL)
        return ANOTHER_TRANSACTION_NOT_CLOSE;

    if(t1ID == t2ID)
        return TIME_1_EQUALS_TIME_2;

    t1 = timeDBGetByID(t1ID);
    if(t1 == NULL)
        return TIME_1_DOES_NOT_EXISTS;

    t2 = timeDBGetByID(t2ID);
    if(t2 == NULL)
        return TIME_2_DOES_NOT_EXISTS;

    if(llIsEmpty(partidaDB.partidas))
        partidaJournal = newPartida(0, t1, t2, gT1, gT2);
    else
        partidaJournal = newPartida(nextPartidaID(), t1, t2, gT1, gT2);

    if(partidaJournal == NULL) {
        return MEMORY_NOT_ENOUGH_EXCEPTION;
    }

    return SUCCESS;
}

/**
 * partidaFromFile
 * 
 * Cria uma partida a partir de uma string do arquivo CSV.
 * 
 * Parâmetros:
 *  - `buff`: Buffer contendo os dados da partida no formato CSV.
 * 
 * Retorna:
 *  - Um ponteiro para a nova partida criada, ou `NULL` em caso de falha.
 */
static Partida* partidaFromFile(const char* buff) {
    int id;
    int t1ID;
    int t2ID;
    int gT1;
    int gT2;

    Time* t1;
    Time* t2;

    sscanf(buff, PARTIDA_CSV_PATTERN, &id, &t1ID, &t2ID, &gT1, &gT2);

    t1 = timeDBGetByID(t1ID);
    if(t1 == NULL)
        return NULL;
    t2 = timeDBGetByID(t2ID);
    if(t2 == NULL)
        return NULL;

    return newPartida(id, t1, t2, gT1, gT2);
}

/**
 * startPartidaDB
 * 
 * Inicializa o banco de dados de partidas, lendo as partidas de um arquivo CSV.
 * 
 * Retorna:
 *  - `true` se o banco de dados foi inicializado corretamente.
 *  - `false` em caso de falha (como falha ao abrir o arquivo ou alocar memória).
 */
bool startPartidaDB() {
    char buffer[100];
    Partida* p;
    FILE* f;

    if(partidaDB.partidas == NULL) {
        partidaDB.partidas = newLinkedList();

        if(partidaDB.partidas == NULL)
            return false;
        
        f = fopen(PARTIDA_CSV, "r");
        
        if(f == NULL) {
            perror("fopen");
            return false;
        }

        // Limpa o cabeçalho do CSV
        fgets(buffer, 100, f);

        while(fgets(buffer, 100, f))
        {
            p = partidaFromFile(buffer);
            if(p == NULL) {
                llFullFree(partidaDB.partidas, freePartida);
                return false;
            }
            llAdd(partidaDB.partidas, p);
        }
    }

    return true;
}

/**
 * partidaDBMandantePrefixCheck
 * 
 * Verifica se a partida tem o time mandante com o prefixo especificado.
 * 
 * Parâmetros:
 *  - `partida`: Ponteiro para a partida a ser verificada.
 * 
 * Retorna:
 *  - `true` se o time mandante tiver o prefixo especificado.
 *  - `false` caso contrário.
 */
bool partidaDBMandantePrefixCheck(void* partida) {
    if(partida == NULL)
        return false;

    return checkPrefix(partidaGetT1((Partida*)partida));
}

/**
 * partidaDBSearchMandante
 * 
 * Pesquisa todas as partidas em que o time mandante tenha o prefixo especificado.
 * 
 * Parâmetros:
 *  - `timeName`: Nome do time (prefixo) a ser buscado.
 * 
 * Retorna:
 *  - Uma lista de partidas que correspondem à pesquisa, ou `NULL` se não houver partidas.
 */
LinkedList* partidaDBSearchMandante(char timeName[TIME_MAX_NAME_SIZE]) {
    if(!timeDBStarted() || partidaDB.partidas == NULL)
        return NULL;

    setPrefix(timeName);
    return llSearchAll(partidaDB.partidas, partidaDBMandantePrefixCheck);
}

/**
 * partidaDBVisitantePrefixCheck
 * 
 * Verifica se a partida tem o time visitante com o prefixo especificado.
 * 
 * Parâmetros:
 *  - `partida`: Ponteiro para a partida a ser verificada.
 * 
 * Retorna:
 *  - `true` se o time visitante tiver o prefixo especificado.
 *  - `false` caso contrário.
 */
bool partidaDBVisitantePrefixCheck(void* partida) {
    if(partida == NULL)
        return false;

    return checkPrefix(partidaGetT2((Partida*)partida));
}

/**
 * partidaDBSearchVisitante
 * 
 * Pesquisa todas as partidas em que o time visitante tenha o prefixo especificado.
 * 
 * Parâmetros:
 *  - `timeName`: Nome do time (prefixo) a ser buscado.
 * 
 * Retorna:
 *  - Uma lista de partidas que correspondem à pesquisa, ou `NULL` se não houver partidas.
 */
LinkedList* partidaDBSearchVisitante(char timeName[TIME_MAX_NAME_SIZE]) {
    if(!timeDBStarted() || partidaDB.partidas == NULL)
        return NULL;

    setPrefix(timeName);
    return llSearchAll(partidaDB.partidas, partidaDBVisitantePrefixCheck);
}

/**
 * partidaDBMandanteOrVisitantePrefixCheck
 * 
 * Verifica se a partida tem o time mandante ou visitante com o prefixo especificado.
 * 
 * Parâmetros:
 *  - `partida`: Ponteiro para a partida a ser verificada.
 * 
 * Retorna:
 *  - `true` se algum dos times (mandante ou visitante) tiver o prefixo especificado.
 *  - `false` caso contrário.
 */
bool partidaDBMandanteOrVisitantePrefixCheck(void* partida) {
    if(partida == NULL)
        return false;

    return checkPrefix(partidaGetT1((Partida*)partida)) || checkPrefix(partidaGetT2((Partida*)partida));
}

/**
 * partidaDBSearchMandanteOrVisitante
 * 
 * Pesquisa todas as partidas em que o time mandante ou visitante tenha o prefixo especificado.
 * 
 * Parâmetros:
 *  - `timeName`: Nome do time (prefixo) a ser buscado.
 * 
 * Retorna:
 *  - Uma lista de partidas que correspondem à pesquisa, ou `NULL` se não houver partidas.
 */
LinkedList* partidaDBSearchMandanteOrVisitante(char timeName[TIME_MAX_NAME_SIZE]) {
    if(!timeDBStarted() || partidaDB.partidas == NULL)
        return NULL;

    setPrefix(timeName);
    return llSearchAll(partidaDB.partidas, partidaDBMandanteOrVisitantePrefixCheck);
}

/**
 * partidaGetById
 * 
 * Função auxiliar para encontrar uma partida pelo ID.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida a ser verificada.
 * 
 * Retorna:
 *  - `true` se o ID da partida corresponder ao ID de pesquisa.
 *  - `false` caso contrário.
 */
static bool partidaGetById(void* p) {
    if(p == NULL)
        return false;

    return partidaGetId((Partida*)p) == partidaIDSearch;
}

/**
 * partidaDBGetById
 * 
 * Pesquisa uma partida pelo seu ID.
 * 
 * Parâmetros:
 *  - `id`: ID da partida a ser pesquisada.
 * 
 * Retorna:
 *  - A partida correspondente ao ID, ou `NULL` se não encontrar.
 */
Partida* partidaDBGetById(int id) {
    if(partidaDB.partidas == NULL)
        return NULL;

    partidaIDSearch = id;

    return llFindFirst(partidaDB.partidas, partidaGetById);
}

/**
 * printPartida
 * 
 * Imprime os detalhes de uma partida.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a partida a ser impressa.
 */
void printPartida(Partida* p) {
    if(p == NULL)
        printf("Partida Indefinida\n");
    else
        printf("ID: %d, Time 1: %s, Time 2: %s, Gols Time 1: %d, Gols Time 2: %d\n", partidaGetId(p), timeGetName(partidaGetT1(p)), timeGetName(partidaGetT2(p)), partidaGetGolsT1(p), partidaGetGolsT2(p));
}

/**
 * partidaDBGetAllPartidas
 * 
 * Retorna todas as partidas armazenadas no banco de dados de partidas.
 * 
 * Retorna:
 *  - Lista com todas as partidas.
 */
LinkedList* partidaDBGetAllPartidas() {
    return partidaDB.partidas;
}

#endif
