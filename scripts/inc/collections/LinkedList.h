#ifndef LINKED_LIST_H
#define LINKED_LIST_H 0

#include "./../../shared/bool.h"
#include "./../../shared/types.h"

// Forward declaration for the LinkedList struct
typedef struct LinkedList LinkedList;

/**
 * newLinkedList
 * 
 * Constrói e inicializa uma nova lista encadeada (LinkedList).
 * 
 * Retorna:
 *  - Um ponteiro para uma nova instância de LinkedList.
 */
LinkedList* newLinkedList();

/**
 * llAdd
 * 
 * Adiciona um novo elemento ao final da lista encadeada (LinkedList* list).
 * Permite adicionar um elemento de tipo `void*` ao final da lista.
 * 
 * Atenção:
 *  - É possível adicionar um elemento `NULL`, o que pode levar a comportamentos inesperados.
 *  - Para evitar adicionar um valor `NULL`, considere utilizar a função `sllAdd()`.
 * 
 * Retorna:
 *  - `false` se a lista for `NULL`, o elemento for `NULL`, ou se não houver memória suficiente para adicionar o elemento.
 *  - `true` se a operação for bem-sucedida.
 */
bool llAdd(LinkedList* list, void* element);

/**
 * sllAdd
 * 
 * Adiciona um novo elemento ao final da lista encadeada (LinkedList* list).
 * Este método evita a adição de elementos `NULL`.
 * 
 * Retorna:
 *  - `false` se a lista for `NULL`, o elemento for `NULL`, ou se não houver memória suficiente para adicionar o elemento.
 *  - `true` se a operação for bem-sucedida.
 */
bool sllAdd(LinkedList* list, void* element);

/**
 * llGet
 * 
 * Obtém o elemento da lista encadeada (LinkedList* list) no índice fornecido (int index).
 * 
 * Exemplo de comportamento:
 *  1. Se a lista estiver vazia e você tentar acessar o índice 0, a função retornará `NULL`.
 *  2. Se a lista contiver 2 elementos:
 *     - O índice 0 retorna o primeiro elemento.
 *     - O índice 1 retorna o último elemento.
 *     - O índice 2 retornará `NULL` (índice inválido).
 * 
 * Retorna:
 *  - O elemento no índice especificado, ou `NULL` caso a lista seja `NULL` ou o índice seja inválido.
 */
void* llGet(LinkedList* list, const int index);

/**
 * llGetLast
 * 
 * Obtém o último elemento da lista encadeada (LinkedList* list).
 * 
 * Retorna:
 *  - O último elemento da lista, ou `NULL` se a lista estiver vazia ou `list` for `NULL`.
 */
void* llGetLast(LinkedList* list);

/**
 * llIsEmpty
 * 
 * Verifica se a lista encadeada (LinkedList* list) está vazia.
 * 
 * Retorna:
 *  - `true` se a lista estiver vazia.
 *  - `false` caso contrário.
 */
bool llIsEmpty(LinkedList* list);

/**
 * llSearchAll
 * 
 * Pesquisa a lista encadeada (LinkedList* list) utilizando a função de busca fornecida (`searchFunc func`).
 * Retorna uma nova lista contendo todos os elementos que atendem à condição especificada pela função `func`.
 * 
 * Retorna:
 *  - Uma nova lista com os elementos que atendem à condição da função `func`.
 */
LinkedList* llSearchAll(LinkedList* list, searchFunc func);

/**
 * llFullFree
 * 
 * Libera completamente a memória ocupada pela lista encadeada, incluindo os elementos internos.
 * A função `freeFunction` é chamada para liberar a memória de cada elemento da lista.
 * Caso não queria desalocar os elementos internos, passe como argumento para `freeFunction` `NULL`.
 */
void llFullFree(LinkedList* list, freeFunc freeFunction);

/**
 * llForeach
 * 
 * Executa uma função fornecida (`foreachFunc f`) para cada elemento da lista encadeada (LinkedList* list).
 */
void llForeach(LinkedList* list, foreachFunc f);

/**
 * llFindFirst
 * 
 * Encontra e retorna o primeiro elemento da lista encadeada (LinkedList* list) que satisfaça a condição definida pela função `findFirstFunc f`.
 * 
 * Retorna:
 *  - O primeiro elemento que satisfaz a condição da função `f`, ou `NULL` caso nenhum elemento seja encontrado.
 */
void* llFindFirst(LinkedList* list, findFirstFunc f);

/**
 * llBoubleSort
 * 
 * Ordena a lista encadeada (LinkedList* list) utilizando o algoritmo de ordenação por bolha (Bubble Sort).
 * A função de comparação `orderFunc f` é usada para determinar a ordem de ordenação dos elementos.
 * 
 * Retorna:
 *  - `true` se a lista for ordenada com sucesso.
 *  - `false` se houver um erro durante a ordenação (exemplo: se a lista for `NULL`).
 */
bool llBoubleSort(LinkedList* list, orderFunc f);

/**
 * llDeepCopy
 * 
 * Realiza uma cópia profunda (deep copy) da lista encadeada (LinkedList* list) entre os índices fornecidos (int start, int end).
 * 
 * Retorna:
 *  - Uma nova lista contendo uma cópia profunda dos elementos entre os índices fornecidos.
 * 
 * ATENÇÃO:
 * - A cópia profunda não copia os ELEMENTOS TAMBÉM. Então, para liberar a memória de uma cópia utilize `llFullFree(copia, NULL)`.
 */
LinkedList* llDeepCopy(LinkedList* list, int start, int end);

/**
 * llGetSize
 * 
 * Obtém o tamanho (número de elementos) da lista encadeada (LinkedList* list).
 * 
 * Retorna:
 *  - O número de elementos na lista.
 *  - `-1` caso `list` seja `NULL`.
 */
int llGetSize(LinkedList* list);

/**
 * llRemoveFirstFound
 * 
 * Remove o primeiro elemento da lista encadeada (LinkedList* list) que satisfaça a condição definida pela função `removeFunc f`.
 * 
 * Retorna:
 *  - `true` se um elemento foi removido com sucesso.
 *  - `false` se nenhum elemento foi encontrado ou removido.
 */
bool llRemoveFirstFound(LinkedList* list, removeFunc f);

#endif
