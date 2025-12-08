#ifndef TIME_DB_C
#define TIME_DB_C 0

#include <stdio.h>

#include "./../../inc/service/repo.h"
#include "./../../inc/collections/LinkedList.h"

// Estrutura que representa o banco de dados de times
struct TimeDB {
    LinkedList* times;  // Lista de times
};

// Instância global do banco de dados de times
static TimeDB timeDB;
static char prefixSearch[TIME_MAX_NAME_SIZE];  // Prefixo de pesquisa para busca de times
static int timeIDSearch;  // ID do time sendo pesquisado

/**
 * timeDBStarted
 * 
 * Verifica se o banco de dados de times foi iniciado.
 * 
 * Retorna:
 *  - `true` se o banco de dados de times foi iniciado.
 *  - `false` caso contrário.
 */
bool timeDBStarted() {
    return timeDB.times != NULL;
}

/**
 * addFirstTime
 * 
 * Adiciona o primeiro time ao banco de dados (quando a lista está vazia).
 * 
 * Parâmetros:
 *  - `time_name`: Nome do time a ser adicionado.
 * 
 * Retorna:
 *  - `true` se a operação foi bem-sucedida.
 *  - `false` em caso de erro (falha na alocação de memória ou inserção).
 */
static bool addFirstTime(const char time_name[TIME_MAX_NAME_SIZE]) {
    Time* t = newTime(0, time_name);
    bool ok;

    if(t == NULL)
        return false;

    ok = sllAdd(timeDB.times, t);
    if(!ok) {
        freeTime(t);
        return false;
    }

    return true;
}

/**
 * addNewTime
 * 
 * Adiciona um novo time ao banco de dados com um novo ID sequencial.
 * 
 * Parâmetros:
 *  - `time_name`: Nome do time a ser adicionado.
 * 
 * Retorna:
 *  - `true` se a operação foi bem-sucedida.
 *  - `false` em caso de erro (falha na alocação de memória ou inserção).
 */
static bool addNewTime(const char time_name[TIME_MAX_NAME_SIZE]) {
    Time* last;
    Time* new;
    bool ok;

    last = llGetLast(timeDB.times);
    new = newTime(timeGetId(last) + 1, time_name);
    
    if(new == NULL)
        return false;

    ok = sllAdd(timeDB.times, new);
    if(!ok) {
        freeTime(new);
        return false;
    }

    return true;
}

/**
 * addTime
 * 
 * Adiciona um time ao banco de dados de times. Se o banco de dados estiver vazio, o primeiro time será adicionado.
 * Caso contrário, um novo time com ID sequencial será adicionado.
 * 
 * Parâmetros:
 *  - `time_name`: Nome do time a ser adicionado.
 * 
 * Retorna:
 *  - `true` se a operação foi bem-sucedida.
 *  - `false` se o banco de dados não foi inicializado ou ocorreu algum erro na inserção.
 */
bool addTime(const char time_name[TIME_MAX_NAME_SIZE]) {
    if(timeDB.times == NULL)
        return false;

    if(llIsEmpty(timeDB.times))
        return addFirstTime(time_name);
    else
        return addNewTime(time_name);
}

/**
 * checkPrefix
 * 
 * Verifica se o nome do time começa com o prefixo armazenado em `prefixSearch`.
 * 
 * Parâmetros:
 *  - `time`: Ponteiro para o time a ser verificado.
 * 
 * Retorna:
 *  - `true` se o nome do time começar com o prefixo especificado.
 *  - `false` caso contrário.
 */
bool checkPrefix(void* time) {
    char* timeName = timeGetName((Time*)time);
    int i;

    for(i = 0; i < TIME_MAX_NAME_SIZE; i++) {
        if(prefixSearch[i] == '\0')
            return true; // Stop early if prefix is exhausted
        if(timeName[i] != prefixSearch[i])
            return false;
    }

    return true;
}

/**
 * setPrefix
 * 
 * Define o prefixo de pesquisa para os nomes dos times.
 * 
 * Parâmetros:
 *  - `prefix`: O prefixo de nome a ser usado nas buscas.
 */
void setPrefix(const char prefix[TIME_MAX_NAME_SIZE]) {
    int i;

    for(i = 0; i < TIME_MAX_NAME_SIZE; i++)
        prefixSearch[i] = prefix[i];

    prefixSearch[TIME_MAX_NAME_SIZE] = '\0';  // Garante que o prefixo tenha um fim de string válido
}

/**
 * searchByPrefix
 * 
 * Pesquisa todos os times cujo nome começa com o prefixo especificado.
 * 
 * Parâmetros:
 *  - `prefix`: O prefixo a ser utilizado na busca.
 * 
 * Retorna:
 *  - Uma lista de times cujo nome começa com o prefixo, ou `NULL` se não encontrar nenhum.
 */
LinkedList* searchByPrefix(const char prefix[TIME_MAX_NAME_SIZE]) {
    setPrefix(prefix);

    return llSearchAll(timeDB.times, checkPrefix);
}

/**
 * timeFromFile
 * 
 * Cria uma estrutura `Time` a partir de uma linha de um arquivo CSV.
 * 
 * Parâmetros:
 *  - `buff`: Linha do arquivo CSV contendo os dados do time.
 * 
 * Retorna:
 *  - Um ponteiro para a estrutura `Time` criada a partir dos dados da linha, ou `NULL` em caso de erro.
 */
static Time* timeFromFile(const char* buff) {
    char timeName[TIME_MAX_NAME_SIZE];
    int timeID;

    sscanf(buff, TIME_CSV_PATTERN, &timeID, timeName);
    return newTime(timeID, timeName);
}

/**
 * startTimeDB
 * 
 * Inicializa o banco de dados de times, lendo os dados a partir de um arquivo CSV.
 * 
 * Retorna:
 *  - `true` se o banco de dados foi inicializado com sucesso.
 *  - `false` em caso de erro (falha ao alocar memória ou ao ler o arquivo).
 */
bool startTimeDB() {
    char buffer[100];
    Time* t;
    FILE* f;

    if(timeDB.times == NULL) {
        timeDB.times = newLinkedList();

        if(timeDB.times == NULL)
            return false;
        
        f = fopen(TIME_CSV, "r");

        if(f == NULL) {
            perror("fopen");
            return false;
        }

        // Limpa o cabeçalho do CSV
        fgets(buffer, 100, f);

        while(fgets(buffer, 100, f))
        {
            t = timeFromFile(buffer);
            if(t == NULL) {
                llFullFree(timeDB.times, freeTime);
                return false;
            }
            llAdd(timeDB.times, t);
        }
    }

    return true;
}

/**
 * timeGetById
 * 
 * Função auxiliar para encontrar um time pelo ID.
 * 
 * Parâmetros:
 *  - `time`: Ponteiro para o time a ser verificado.
 * 
 * Retorna:
 *  - `true` se o ID do time corresponder ao ID de pesquisa.
 *  - `false` caso contrário.
 */
static bool timeGetById(void* time) {
    return timeGetId((Time*)time) == timeIDSearch;
}

/**
 * timeDBGetByID
 * 
 * Pesquisa um time pelo seu ID.
 * 
 * Parâmetros:
 *  - `id`: ID do time a ser pesquisado.
 * 
 * Retorna:
 *  - O time correspondente ao ID, ou `NULL` se não encontrar.
 */
Time* timeDBGetByID(int id) {
    timeIDSearch = id;
    return llFindFirst(timeDB.times, timeGetById);
}

/**
 * timeDBGetAllTimes
 * 
 * Retorna todos os times armazenados no banco de dados de times.
 * 
 * Retorna:
 *  - A lista de todos os times.
 */
LinkedList* timeDBGetAllTimes() {
    return timeDB.times;
}

#endif
