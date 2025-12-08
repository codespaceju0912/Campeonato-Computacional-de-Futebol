#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H 0

#include "./bool.h"

// Definição de tipos de função para operações genéricas em listas e outros elementos

/**
 * searchFunc
 * 
 * Tipo de função utilizado para definir uma condição de busca em elementos.
 * A função retorna `true` se o elemento corresponder ao critério de busca, e `false` caso contrário.
 * 
 * Parâmetros:
 *  - `void*`: Um ponteiro para o elemento a ser verificado.
 * 
 * Retorna:
 *  - `true` se o elemento corresponde à condição de busca.
 *  - `false` caso contrário.
 */
typedef bool (*searchFunc)(void*);

/**
 * freeFunc
 * 
 * Tipo de função utilizado para liberar a memória de um elemento.
 * A função deve liberar qualquer memória alocada para o elemento passado como parâmetro.
 * 
 * Parâmetros:
 *  - `void*`: Um ponteiro para o elemento a ser liberado.
 * 
 * Retorna:
 *  - Nenhum valor é retornado. A função é responsável apenas por desalocar a memória.
 */
typedef void(*freeFunc)(void*);

/**
 * foreachFunc
 * 
 * Tipo de função utilizado para realizar uma operação em cada elemento de uma lista ou coleção.
 * A função é chamada para cada elemento, permitindo a execução de ações específicas.
 * 
 * Parâmetros:
 *  - `void*`: Um ponteiro para o elemento em que a operação será realizada.
 * 
 * Retorna:
 *  - Nenhum valor é retornado. A função pode realizar ações sobre o elemento, como modificações ou exibição.
 */
typedef void(*foreachFunc)(void*);

/**
 * findFirstFunc
 * 
 * Tipo de função utilizado para verificar se um elemento atende a um critério específico e deve ser retornado primeiro.
 * A função retorna `true` se o elemento atender ao critério e `false` caso contrário.
 * 
 * Parâmetros:
 *  - `void*`: Um ponteiro para o elemento a ser verificado.
 * 
 * Retorna:
 *  - `true` se o elemento atende ao critério.
 *  - `false` caso contrário.
 */
typedef bool(*findFirstFunc)(void*);

/**
 * removeFunc
 * 
 * Tipo de função utilizado para determinar se um elemento deve ser removido de uma coleção.
 * A função retorna `true` se o elemento deve ser removido e `false` caso contrário.
 * 
 * Parâmetros:
 *  - `void*`: Um ponteiro para o elemento a ser verificado.
 * 
 * Retorna:
 *  - `true` se o elemento deve ser removido.
 *  - `false` caso contrário.
 */
typedef bool(*removeFunc)(void*);

// Definição do tipo de enumeração `Order`, utilizado para comparar elementos

/**
 * Order
 * 
 * Enumeração utilizada para representar o resultado de uma comparação entre dois elementos.
 * O valor `less_than` indica que o primeiro elemento é menor que o segundo, `equal` indica que são iguais, e `greater_than` indica que o primeiro elemento é maior que o segundo.
 */
typedef enum {less_than=-1, equal, greater_than} Order;

/**
 * orderFunc
 * 
 * Tipo de função utilizado para comparar dois elementos de acordo com um critério específico.
 * A função deve retornar um valor do tipo `Order`, indicando o resultado da comparação.
 * 
 * Parâmetros:
 *  - `a`: Um ponteiro para o primeiro elemento a ser comparado.
 *  - `b`: Um ponteiro para o segundo elemento a ser comparado.
 * 
 * Retorna:
 *  - `less_than` se o primeiro elemento é menor que o segundo.
 *  - `equal` se os dois elementos são iguais.
 *  - `greater_than` se o primeiro elemento é maior que o segundo.
 */
typedef Order(*orderFunc)(void* a, void* b);

#endif
