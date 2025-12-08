#ifndef REPO_H
#define REPO_H 0

#include "./model.h"
#include "../collections/LinkedList.h"

// Definição de caminho para os arquivos CSV de acordo com o sistema operacional
#if defined(_WIN32) || defined(_WIN64)
    #define PARTIDA_CSV "FILE_PATH.csv"
    #define TIME_CSV "FILE_PATH.csv"
#else
    #define PARTIDA_CSV "FILE_PATH.csv"
    #define TIME_CSV "FILE_PATH.csv"
#endif

// Padrões de formato para leitura de CSV (para os arquivos de Time e Partida)
#define TIME_CSV_PATTERN "%d;%[^,\n]"
#define PARTIDA_CSV_PATTERN "%d;%d;%d;%d;%d"

// Definição da estrutura TimeDB, que representa o banco de dados de times
typedef struct TimeDB TimeDB;

/**
 * timeDBStarted
 * 
 * Verifica se o banco de dados de times foi iniciado com sucesso.
 * 
 * Retorna:
 *  - `true` se o banco de dados de times foi iniciado.
 *  - `false` caso contrário.
 */
bool timeDBStarted();

/**
 * addTime
 * 
 * Adiciona um novo time ao banco de dados de times.
 * 
 * Parâmetros:
 *  - `time_name`: Nome do time a ser adicionado, com comprimento máximo de `TIME_MAX_NAME_SIZE`.
 * 
 * Retorna:
 *  - `true` se o time foi adicionado com sucesso.
 *  - `false` caso ocorra algum erro.
 */
bool addTime(const char time_name[TIME_MAX_NAME_SIZE]);

/**
 * checkPrefix
 * 
 * Verifica se um time no banco de dados possui um prefixo correspondente.
 * 
 * Parâmetros:
 *  - `time`: Ponteiro para o time a ser verificado.
 * 
 * Retorna:
 *  - `true` se o prefixo do time corresponde.
 *  - `false` caso contrário.
 */
bool checkPrefix(void* time);

/**
 * setPrefix
 * 
 * Define o prefixo que será usado para identificar os times no banco de dados.
 * 
 * Parâmetros:
 *  - `prefix`: O prefixo a ser configurado, com comprimento máximo de `TIME_MAX_NAME_SIZE`.
 * 
 * Retorna:
 *  - Nenhum valor é retornado. O prefixo é definido para os times.
 */
void setPrefix(const char prefix[TIME_MAX_NAME_SIZE]);

/**
 * searchByPrefix
 * 
 * Realiza uma busca por times no banco de dados com um prefixo específico.
 * 
 * Parâmetros:
 *  - `prefix`: O prefixo a ser usado para a busca, com comprimento máximo de `TIME_MAX_NAME_SIZE`.
 * 
 * Retorna:
 *  - Uma lista (`LinkedList`) contendo todos os times que correspondem ao prefixo especificado.
 */
LinkedList* searchByPrefix(const char prefix[TIME_MAX_NAME_SIZE]);

/**
 * startTimeDB
 * 
 * Inicia o banco de dados de times, configurando a estrutura necessária.
 * 
 * Retorna:
 *  - `true` se o banco de dados de times foi iniciado com sucesso.
 *  - `false` caso ocorra algum erro durante a inicialização.
 */
bool startTimeDB();

/**
 * timeDBGetByID
 * 
 * Obtém um time do banco de dados pelo seu ID.
 * 
 * Parâmetros:
 *  - `id`: O ID do time a ser recuperado.
 * 
 * Retorna:
 *  - Um ponteiro para o time correspondente ao ID, ou `NULL` caso o time não seja encontrado.
 */
Time* timeDBGetByID(int id);

// Definição da estrutura PartidaDB, que representa o banco de dados de partidas
typedef struct PartidaDB PartidaDB;

/**
 * partidaDBStartInsertTransaction
 * 
 * Inicia uma transação de inserção no banco de dados de partidas.
 * 
 * Retorna:
 *  - `true` se a transação de inserção foi iniciada com sucesso.
 *  - `false` caso ocorra um erro.
 */
bool partidaDBStartInsertTransaction();

/**
 * partidaDBInsertCommit
 * 
 * Realiza o commit (confirmação) da transação de inserção no banco de dados de partidas.
 * 
 * Retorna:
 *  - `true` se a transação de inserção foi confirmada com sucesso.
 *  - `false` caso ocorra um erro.
 */
bool partidaDBInsertCommit();

/**
 * partidaDBInsertRollBack
 * 
 * Desfaz (rollback) a transação de inserção no banco de dados de partidas.
 * 
 * Retorna:
 *  - `true` se a transação de inserção foi desfeita com sucesso.
 *  - `false` caso ocorra um erro.
 */
void partidaDBInsertRollBack();

typedef enum {PARTIDA_DATABASE_NOT_STARTED_YET, ANOTHER_TRANSACTION_NOT_CLOSE, MEMORY_NOT_ENOUGH_EXCEPTION, TIME_1_EQUALS_TIME_2, TIME_1_DOES_NOT_EXISTS, TIME_2_DOES_NOT_EXISTS, SUCCESS} AddPartidaReponse;

/**
 * addPartida
 * 
 * Adiciona uma nova partida ao banco de dados de partidas.
 * 
 * Parâmetros:
 *  - `t1ID`: ID do primeiro time da partida.
 *  - `t2ID`: ID do segundo time da partida.
 *  - `gT1`: Número de gols marcados pelo primeiro time.
 *  - `gT2`: Número de gols marcados pelo segundo time.
 * 
 * Retorna:
 *  - Um valor do tipo `AddPartidaReponse`, indicando o status da operação.
 *    - `PARTIDA_DATABASE_NOT_STARTED_YET`: Banco de dados de partidas não iniciado.
 *    - `ANOTHER_TRANSACTION_NOT_CLOSE`: Outra transação não foi fechada.
 *    - `MEMORY_NOT_ENOUGH_EXCEPTION`: Falta de memória para a operação.
 *    - `TIME_1_EQUALS_TIME_2`: Os times da partida são iguais.
 *    - `TIME_1_DOES_NOT_EXISTS`: O primeiro time não existe.
 *    - `TIME_2_DOES_NOT_EXISTS`: O segundo time não existe.
 *    - `SUCCESS`: A partida foi adicionada com sucesso.
 */
AddPartidaReponse addPartida(int t1ID, int t2ID, int gT1, int gT2);

/**
 * startPartidaDB
 * 
 * Inicia o banco de dados de partidas, configurando a estrutura necessária.
 * 
 * Retorna:
 *  - `true` se o banco de dados de partidas foi iniciado com sucesso.
 *  - `false` caso ocorra um erro durante a inicialização.
 */
bool startPartidaDB();

/**
 * partidaDBMandantePrefixCheck
 * 
 * Verifica se a partida possui um prefixo correspondente ao do time mandante.
 * 
 * Parâmetros:
 *  - `partida`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - `true` se o prefixo do time mandante corresponde.
 *  - `false` caso contrário.
 */
bool partidaDBMandantePrefixCheck(void* partida);

/**
 * partidaDBSearchMandante
 * 
 * Realiza uma busca por partidas onde o time mandante tem o nome que começa com o prefixo especificado.
 * 
 * Parâmetros:
 *  - `timeName`: Nome do time mandante, com comprimento máximo de `TIME_MAX_NAME_SIZE`.
 * 
 * Retorna:
 *  - Uma lista (`LinkedList`) contendo todas as partidas onde o time mandante corresponde ao prefixo.
 */
LinkedList* partidaDBSearchMandante(char timeName[TIME_MAX_NAME_SIZE]);

/**
 * partidaDBVisitantePrefixCheck
 * 
 * Verifica se a partida possui um prefixo correspondente ao do time visitante.
 * 
 * Parâmetros:
 *  - `partida`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - `true` se o prefixo do time visitante corresponde.
 *  - `false` caso contrário.
 */
bool partidaDBVisitantePrefixCheck(void* partida);

/**
 * partidaDBSearchVisitante
 * 
 * Realiza uma busca por partidas onde o time visitante tem o nome que começa com o prefixo especificado.
 * 
 * Parâmetros:
 *  - `timeName`: Nome do time visitante, com comprimento máximo de `TIME_MAX_NAME_SIZE`.
 * 
 * Retorna:
 *  - Uma lista (`LinkedList`) contendo todas as partidas onde o time visitante corresponde ao prefixo.
 */
LinkedList* partidaDBSearchVisitante(char timeName[TIME_MAX_NAME_SIZE]);

/**
 * partidaDBMandanteOrVisitantePrefixCheck
 * 
 * Verifica se a partida possui um prefixo correspondente ao do time mandante ou visitante.
 * 
 * Parâmetros:
 *  - `partida`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - `true` se o prefixo corresponde a qualquer time (mandante ou visitante).
 *  - `false` caso contrário.
 */
bool partidaDBMandanteOrVisitantePrefixCheck(void* partida);

/**
 * partidaDBSearchMandanteOrVisitante
 * 
 * Realiza uma busca por partidas onde o nome do time mandante ou visitante começa com o prefixo especificado.
 * 
 * Parâmetros:
 *  - `timeName`: Nome do time (mandante ou visitante), com comprimento máximo de `TIME_MAX_NAME_SIZE`.
 * 
 * Retorna:
 *  - Uma lista (`LinkedList`) contendo todas as partidas que correspondem ao prefixo.
 */
LinkedList* partidaDBSearchMandanteOrVisitante(char timeName[TIME_MAX_NAME_SIZE]);

/**
 * partidaDBGetById
 * 
 * Obtém uma partida pelo seu ID.
 * 
 * Parâmetros:
 *  - `id`: ID da partida a ser recuperada.
 * 
 * Retorna:
 *  - Um ponteiro para a partida correspondente ao ID, ou `NULL` caso a partida não seja encontrada.
 */
Partida* partidaDBGetById(int id);

/**
 * printPartida
 * 
 * Exibe as informações de uma partida no formato legível.
 * 
 * Parâmetros:
 *  - `p`: Ponteiro para a instância de `Partida`.
 * 
 * Retorna:
 *  - Nenhum valor é retornado. A partida é impressa na saída padrão.
 */
void printPartida(Partida* p);

/**
 * partidaDBGetAllPartidas
 * 
 * Retorna uma lista de todas as partidas do banco de dados.
 * 
 * Retorna:
 *  - Uma lista (`LinkedList`) contendo todas as partidas.
 */
LinkedList* partidaDBGetAllPartidas();

/**
 * timeDBGetAllTimes
 * 
 * Retorna uma lista de todos os times do banco de dados.
 * 
 * Retorna:
 *  - Uma lista (`LinkedList`) contendo todos os times.
 */
LinkedList* timeDBGetAllTimes();

#endif
