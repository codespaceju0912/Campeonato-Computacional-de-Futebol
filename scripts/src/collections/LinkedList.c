#ifndef LINKED_LIST_C
#define LINKED_LIST_C 0

#include <stdlib.h>
#include "./../../shared/types.h"

// Estrutura Node usada para representar os elementos da lista encadeada
typedef struct Node
{
    void* data;          // Dados do nó (elemento genérico)
    struct Node* next;   // Ponteiro para o próximo nó na lista
} Node;

/*
    @struct LinkedList
    Esta estrutura encapsula o conceito de lista encadeada (LinkedList).
    Como nenhum comportamento específico foi definido, ela será utilizada como uma fila,
    facilitando a ordenação dos elementos (ex: ordenação por ID dos times).
*/
typedef struct LinkedList
{
    Node* first;  // Ponteiro para o primeiro nó da lista
    Node* last;   // Ponteiro para o último nó da lista
    int size;     // Tamanho da lista (quantidade de elementos)
} LinkedList;

/**
 * newLinkedList
 * 
 * Cria uma nova lista encadeada vazia.
 * 
 * Retorna:
 *  - Um ponteiro para a nova instância de `LinkedList`, ou `NULL` se a alocação falhar.
 */
LinkedList* newLinkedList() {
    LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
    
    if(l == NULL)
        return NULL;

    l->first = NULL;
    l->last = NULL;
    l->size = 0;

    return l;
}

/**
 * llAddN
 * 
 * Função auxiliar que adiciona um nó (Node) ao final da lista encadeada.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista onde o nó será adicionado.
 *  - `n`: Ponteiro para o nó a ser adicionado.
 */
static void llAddN(LinkedList* l, Node* n) {
    if(l->first == NULL) {
        l->first = n;
        l->last = n;
    } else {
        l->last->next = n;
        l->last = n;
    }

    l->size++;
}

/**
 * llAdd
 * 
 * Adiciona um novo elemento (void*) ao final da lista encadeada.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista onde o elemento será adicionado.
 *  - `elmt`: Ponteiro para o elemento a ser adicionado.
 * 
 * Retorna:
 *  - `true` se o elemento foi adicionado com sucesso.
 *  - `false` se a lista for `NULL` ou se houver falha na alocação.
 */
bool llAdd(LinkedList* l, void* elmt) {
    Node* n;

    if(l == NULL || elmt == NULL)
        return false;

    n = (Node*)malloc(sizeof(Node));
    if(n == NULL)
        return false;

    n->data = elmt;
    n->next = NULL;

    llAddN(l, n);

    return true;
}

/**
 * sllAdd
 * 
 * Adiciona um novo elemento (void*) ao final da lista encadeada.
 * Função que impede a inserção de `NULL` como elemento.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista onde o elemento será adicionado.
 *  - `elmt`: Ponteiro para o elemento a ser adicionado.
 * 
 * Retorna:
 *  - `true` se o elemento foi adicionado com sucesso.
 *  - `false` se o elemento for `NULL`.
 */
bool sllAdd(LinkedList* l, void* elmt) {
    if(elmt == NULL)
        return false;
    
    return llAdd(l, elmt);
}

/**
 * getAt
 * 
 * Função auxiliar para obter o nó na lista encadeada no índice especificado.
 * 
 * ATENÇÃO:
 *  - Esta função não é segura. Se a lista for `NULL` ou o índice for inválido, causará falha de segmentação.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `idx`: Índice do nó a ser obtido.
 * 
 * Retorna:
 *  - O nó no índice especificado ou `NULL` se o índice for inválido.
 */
static Node* getAt(LinkedList* l, const  int idx) {
      int i;
      int stop = idx;

    Node* n = l->first;

    for(i = 0; i < stop; i++)
        n = n->next;

    return n;
}

/**
 * llGet
 * 
 * Obtém o elemento armazenado no nó na posição indicada pelo índice.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `index`: Índice do elemento a ser obtido.
 * 
 * Retorna:
 *  - O elemento armazenado no nó ou `NULL` se a lista for `NULL` ou o índice for inválido.
 */
void* llGet(LinkedList* l, const int index) {
    Node* n;

    if(l == NULL)
        return NULL;

    if(index >= l->size)
        return NULL;

    n = getAt(l, index);

    if(n == NULL)
        return NULL;

    return n->data;
}

/**
 * llGetLast
 * 
 * Obtém o último elemento armazenado na lista.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 * 
 * Retorna:
 *  - O último elemento ou `NULL` se a lista for `NULL` ou vazia.
 */
void* llGetLast(LinkedList* l) {
    if(l == NULL || l->last == NULL)
        return NULL;

    return l->last->data;
}

/**
 * llIsEmpty
 * 
 * Verifica se a lista encadeada está vazia.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 * 
 * Retorna:
 *  - `true` se a lista estiver vazia.
 *  - `false` caso contrário.
 */
bool llIsEmpty(LinkedList* l) {
    if(l == NULL)
        return false;

    return l->first == NULL;
}

/**
 * llFree
 * 
 * Libera todos os nós da lista, sem liberar os dados armazenados neles.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 */
static void llFree(LinkedList* l) {
    Node* last; 
    Node* current;

    for(current = l->first; current != NULL;) {
        last = current;
        current = current->next;
        free(last);
    }
}

/**
 * llFreeData
 * 
 * Libera todos os nós da lista, além de liberar os dados armazenados em cada nó usando a função fornecida.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `f`: Função de liberação dos dados (ex: `free`).
 */
static void llFreeData(LinkedList* l, freeFunc f) {
    Node* last; 
    Node* current;

    for(current = l->first; current != NULL;) {
        f(current->data);
        last = current;
        current = current->next;
        free(last);
    }
}

/**
 * llFullFree
 * 
 * Libera todos os nós da lista, liberando também os dados associados com a função `freeFunc` fornecida.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `f`: Função de liberação dos dados (pode ser `NULL`).
 */
void llFullFree(LinkedList* l, freeFunc f) {
    if(l == NULL)
        return;

    if(f == NULL)
        llFree(l);
    else
        llFreeData(l, f);

    free(f);
}

/**
 * llSearchAll
 * 
 * Busca todos os elementos da lista que atendem à condição especificada pela função `searchFunc`.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `func`: Função que define a condição de busca.
 * 
 * Retorna:
 *  - Uma nova lista contendo todos os elementos que atendem à condição da função `searchFunc`.
 */
LinkedList* llSearchAll(LinkedList* l, searchFunc func) {
    LinkedList* nl = newLinkedList();
    Node* n;
    bool ok;
    if(l == NULL || func == NULL || nl == NULL)
        return NULL;

    for(n = l->first; n != NULL; n = n->next)
        if(func(n->data)) {
            ok = llAdd(nl, n->data);
            if(!ok) {
                llFullFree(nl, NULL);
                return NULL;
            }
        }

    return nl;
}

/**
 * llForeach
 * 
 * Aplica a função `foreachFunc` a cada elemento da lista.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `f`: Função a ser aplicada em cada elemento.
 */
void llForeach(LinkedList* l, foreachFunc f) {
    Node* n;
    if(l == NULL || f == NULL)
        return;

    for(n = l->first; n != NULL; n = n->next)
        f(n->data);
}

/**
 * llFindFirst
 * 
 * Encontra e retorna o primeiro elemento da lista que atende à condição definida pela função `findFirstFunc`.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `f`: Função que define a condição de busca.
 * 
 * Retorna:
 *  - O primeiro elemento que atende à condição ou `NULL` se nenhum elemento atender.
 */
void* llFindFirst(LinkedList* l, findFirstFunc f) {
    Node* n;
    if(l == NULL || f == NULL)
        return NULL;
    
    for(n = l->first; n != NULL; n = n->next)
        if(f(n->data))
            return n->data;
    
    return NULL;
}

/**
 * llRemoveFirstFound
 * 
 * Remove o primeiro elemento da lista que atende à condição especificada pela função `removeFunc`.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `f`: Função que define a condição para remoção.
 * 
 * Retorna:
 *  - `true` se o elemento foi removido com sucesso.
 *  - `false` se nenhum elemento foi removido.
 */
bool llRemoveFirstFound(LinkedList* l, removeFunc f) {
    Node* n;
    Node* b = NULL;
    if(l == NULL || f == NULL)
        return false;

    for(n = l->first; n != NULL; n = n->next) {
        if(f(n->data)) {
            if(b == NULL) {
                l->first = n->next;
                if(l->first == NULL)
                    l->last = NULL;
                free(n);
            } else {
                b->next = n->next;
                if(b->next == NULL)
                    l->last = b;
                free(n);
            }

            l->size--;
            return true;
        }

        b = n;
    }

    return false;
}

/**
 * llBoubleSort
 * 
 * Realiza a ordenação por bolha (bubble sort) na lista encadeada, usando a função `orderFunc` para comparar os elementos.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `f`: Função de comparação que determina a ordem dos elementos.
 * 
 * Retorna:
 *  - `true` se a lista foi ordenada com sucesso.
 *  - `false` caso haja algum erro (por exemplo, se a lista ou a função de comparação forem `NULL`).
 */
bool llBoubleSort(LinkedList* l, orderFunc f) {
    Node* a;
    Node* b;
    void* swapAux;
    
    if(l == NULL || f == NULL)
        return false;

    for(a=l->first; a != NULL; a = a->next)
        for(b=l->first; b != NULL; b = b->next)
            if(f(a->data, b->data) == greater_than) {
                swapAux = b->data;
                b->data = a->data;
                a->data = swapAux;
            }

    return true;
}

/**
 * nodeCopy
 * 
 * Cria uma cópia de um nó da lista.
 * 
 * Parâmetros:
 *  - `n`: Ponteiro para o nó a ser copiado.
 * 
 * Retorna:
 *  - Uma cópia do nó ou `NULL` se a alocação falhar.
 */
static Node* nodeCopy(Node* n) {
    Node* cp;

    if(n == NULL)
        return NULL;

    cp = (Node*)malloc(sizeof(Node));
    if(cp == NULL)
        return NULL;

    cp->data = n->data;
    cp->next = NULL;
    return cp;
}

/**
 * llDeepCopy
 * 
 * Cria uma cópia profunda de uma parte da lista encadeada, entre os índices `start` e `end`.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 *  - `start`: Índice de início da cópia.
 *  - `end`: Índice de término da cópia.
 * 
 * Retorna:
 *  - Uma nova lista encadeada contendo a cópia dos elementos entre os índices especificados.
 *  - `NULL` se ocorrer algum erro (por exemplo, índices inválidos ou falha de alocação).
 */
LinkedList* llDeepCopy(LinkedList* l, int start, int end) {
    LinkedList* lCopy;
    Node* n;
    Node* copy;
    Node* lastCopy;
    int i;

    if(l == NULL || l->first == NULL || start < 0 || end < start || end > l->size)
        return NULL;

    lCopy = newLinkedList();
    if(lCopy == NULL)
        return NULL;

    n = l->first;
    for(i=0; i < start; i++)
        n = n->next;

    copy = nodeCopy(n);
    if(copy == NULL) {
        free(copy);
        return NULL;
    }

    lCopy->first = copy;
    lastCopy = copy;
    for(; i < end; i++) {
        n = n->next;
        if(n == NULL)
            break; // early stop
        copy = nodeCopy(n);
        if(copy == NULL) {
            llFullFree(lCopy, NULL);
            return NULL;
        }
        lastCopy->next = copy;
        lastCopy = copy;
    }

    lCopy->last = copy;
    lCopy->size = end-start;

    return lCopy;
}

/**
 * llGetSize
 * 
 * Retorna o número de elementos presentes na lista encadeada.
 * 
 * Parâmetros:
 *  - `l`: Ponteiro para a lista encadeada.
 * 
 * Retorna:
 *  - O número de elementos na lista, ou `-1` se a lista for `NULL`.
 */
int llGetSize(LinkedList* l) {
    if(l == NULL)
        return -1;

    return l->size;
}

#endif
