#ifndef TIME_VIEW_C
#define TIME_VIEW_C 0

#include <stdio.h>
#include <string.h>

#include "./0_utils.c"
#include "./../../inc/collections/LinkedList.h"
#include "./../model/Partida.c" 
#include "./../repo/PartidaDB.c" 
#include "./../repo/TimeDB.c" 

typedef struct {
    int id;
    char nome[TIME_MAX_NAME_SIZE];
    int vitorias;
    int empates;
    int derrotas;
    int gm;
    int gs;
} CalcContext;


// Banco global existente
extern PartidaDB partidaDB;

// Contexto de Busca Global
CalcContext gContext;

// --------------------------------------------------
// Função auxiliar que calcula estatísticas de um time
// --------------------------------------------------
static void processPartida(void* p)
{
    Partida* pt = (Partida*)p;

    int marcou = 0, sofreu = 0;

    // Verifica se o time é mandante ou visitante
    if (strcmp(pt->t1->name, gContext.nome) == 0) {
        marcou = pt->golsT1;
        sofreu = pt->golsT2;
    } else {
        marcou = pt->golsT2;
        sofreu = pt->golsT1;
    }

    gContext.gm += marcou;
    gContext.gs += sofreu;

    if (marcou > sofreu) gContext.vitorias++;
    else if (marcou == sofreu) gContext.empates++;
    else gContext.derrotas++;
}


static void calcularEstatisticas(Time* t)
{
    gContext.id = t->id;
    gContext.vitorias = 0;
    gContext.derrotas = 0;
    gContext.empates = 0;
    gContext.gm = 0;
    gContext.gs = 0;
    strcpy(gContext.nome, t->name);

    LinkedList* partidas = partidaDBSearchMandanteOrVisitante(gContext.nome);

    if (partidas == NULL || llIsEmpty(partidas)) {
        if(partidas) llFullFree(partidas, NULL);
        return;
    }

    llForeach(partidas, processPartida);

    llFullFree(partidas, NULL);
}



// --------------------------------------------------
// VIEW PRINCIPAL
// --------------------------------------------------
static void printCalc(CalcContext* ctx) {
    if(ctx == NULL) {
        printf("Erro: contexto não definido\n");
        return;
    }

    int saldo = ctx->gm - ctx->gs;
    int pontos = ctx->vitorias * 3 + ctx->empates;

    printf("%2d | %-11s | %1d | %1d | %1d | %2d | %2d | %3d | %2d\n",
            ctx->id,
            ctx->nome,
            ctx->vitorias, ctx->empates, ctx->derrotas,
            ctx->gm, ctx->gs,
            saldo,
            pontos
        );
}

static void printTime(void* t) {
    Time* time = (Time*)t;
    calcularEstatisticas(time);
    printCalc(&gContext);
}

static void printTimeViewHeader() {
    printf("ID | Time        | V | E | D | GM | GS |  S | PG\n");
    printf("--------------------------------------------------\n");
}

void viewPrintTime(Time* time) {
    printTimeViewHeader();
    if(time == NULL)
        printf("Time Indefinido");
    else
        printTime(time);
}

void viewPrintTimes(LinkedList* listaDeTimes)
{
    if(llIsEmpty(listaDeTimes)) {
        printf("Nenhum time encontrado.\n");
        return;
    }

    printTimeViewHeader();
    

    llForeach(listaDeTimes, printTime);
}

void viewBuscarTimesPorPrefixo()
{
    printf("=== Buscar Times por Prefixo ===\n");

    char prefix[TIME_MAX_NAME_SIZE];
    readString("Digite o prefixo do nome do time: ", prefix, TIME_MAX_NAME_SIZE);

    LinkedList* encontrados = searchByPrefix(prefix);

    if (encontrados == NULL || llIsEmpty(encontrados)) {
        printf("Nenhum time encontrado com prefixo \"%s\".\n", prefix);
        if (encontrados) llFullFree(encontrados, NULL);
        return;
    }

    printf("\nTimes encontrados:\n");
    viewPrintTimes(encontrados);

    // Importante: liberar apenas a lista wrapper, não os times reais
    llFullFree(encontrados, NULL);
}



#endif
