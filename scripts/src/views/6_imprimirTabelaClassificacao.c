#ifndef IMPRIMIR_TABELA_CLASSIFICACAO_C
#define IMPRIMIR_TABELA_CLASSIFICACAO_C 0

#include <stdio.h>
#include <ctype.h>
#include "./0_utils.c"
#include "../../inc/collections/LinkedList.h"
#include "../../inc/service/model.h"
#include "../../inc/service/repo.h"
#include "./1_time.c"
#include "./2_partida.c"


static LinkedList* gCalcContext = NULL;

static void ctxcp(CalcContext* ctx) {
    ctx->id = gContext.id;
    ctx->derrotas = gContext.derrotas;
    ctx->vitorias = gContext.vitorias;
    ctx->empates = gContext.empates;
    strcpy(ctx->nome, gContext.nome);
    ctx->gm = gContext.gm;
    ctx->gs = gContext.gs;
}

static void forEachTimeLoadContext(void* t) {
    CalcContext* ctx;
    bool ok;

    if(gCalcContext == NULL || t == NULL)
        return;

    ctx = (CalcContext*)malloc(sizeof(CalcContext));
    if(ctx == NULL)
        return;

    calcularEstatisticas((Time*) t);
    ctxcp(ctx);

    ok = llAdd(gCalcContext, ctx);
    if(!ok)
        free(ctx);
}

static bool loadContext() {
    if(gCalcContext != NULL)
        return false;

    gCalcContext = newLinkedList();
    if(gCalcContext == NULL)
        return false;

    llForeach(timeDBGetAllTimes(), forEachTimeLoadContext);

    return true;
}


// ===============================================
// Função de comparação para BubbleSort
// ===============================================
static Order orderResult(void* a, void* b)
{
    CalcContext* r1 = (CalcContext*)a;
    CalcContext* r2 = (CalcContext*)b;

    int pg1 = (r1->vitorias*3)+r1->empates;
    int pg2 = (r2->vitorias*3)+r2->empates;

    // Ordem decrescente
    if (pg1 > pg2) return greater_than;
    if (pg1 < pg2) return less_than;

    // Se empatar, ordenar pelo menor ID
    return equal;
}

// ===============================================
// VIEW PAGINADA
// ===============================================

static void printCalcWrapper(void* calc) {
    printCalc((CalcContext*)calc);
}

void viewTabelaClassificacao()
{
    printf("=== Partidas (Listagem Paginada) ===\n");

    if(!loadContext()) {
        printf("Erro: algum erro ocorreu.");
        return;
    }
    

    // Ordenar
    llBoubleSort(gCalcContext, orderResult);

    const int porPagina = 5;
    int totalItens = llGetSize(gCalcContext);
    int totalPaginas = (totalItens + porPagina - 1) / porPagina;
    int paginaAtual = 1;

    while (1) {
        printf("\nPágina %d de %d\n", paginaAtual, totalPaginas);
        printf("Itens restantes: %d\n", (totalPaginas-paginaAtual)*porPagina);
        printTimeViewHeader();

        int start = (paginaAtual - 1) * porPagina;
        int end   = start + porPagina - 1;
        end = end > llGetSize(gCalcContext) ? llGetSize(gCalcContext) : end;

        // Criar view da página
        LinkedList* pagina = llDeepCopy(gCalcContext, start, end);

        // Mostrar partidas
        llForeach(pagina, printCalcWrapper);

        llFullFree(pagina, NULL);

        // Perguntar próxima página
        char buffer[16];
        readString("\nDigite número da página ou 'Q' para sair: ",
                   buffer, sizeof(buffer));

        // Cancelar
        if (toupper(buffer[0]) == 'Q')
            break;

        // Validar número
        char* endptr;
        long p = strtol(buffer, &endptr, 10);

        if (endptr == buffer || p < 1 || p > totalPaginas) {
            printf("Página inválida.\n");
            continue;
        }

        paginaAtual = (int)p;
    }

    llFullFree(gCalcContext, free);
    gCalcContext = NULL;
}

#endif