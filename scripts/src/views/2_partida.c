#ifndef PARTIDA_VIEW_C
#define PARTIDA_VIEW_C 0

#include <stdio.h>
#include <string.h>

#include "./0_utils.c"
#include "../../inc/collections/LinkedList.h"
#include "../../inc/service/model.h"
#include "../../inc/service/repo.h"


// -------------------------------------------------------
// VIEW PRINCIPAL — Exibir todas as partidas cadastradas
// -------------------------------------------------------
static void imprimirPartida(void* p) {
    Partida* pt = (Partida*)p;

    char resultado;

    if (partidaGetGolsT1(pt) > partidaGetGolsT2(pt)) resultado = 'M';       // Mandante venceu
    else if (partidaGetGolsT1(pt) < partidaGetGolsT2(pt)) resultado = 'V';  // Visitante venceu
    else resultado = 'E';                               // Empate

    printf("%2d | %-11s | %-11s | %2d | %2d | %c\n",
            partidaGetId(pt),
            timeGetName(partidaGetT1(pt)),
            timeGetName(partidaGetT2(pt)),
            partidaGetGolsT1(pt),
            partidaGetGolsT2(pt),
            resultado);
}

void printPartidaViewHeader() {
    printf("ID | Mandante   | Visitante  | GM | GS | R\n");
    printf("---------------------------------------------------\n");   
}

void viewPartidas(LinkedList* listaDePartidas)
{
    if (llIsEmpty(listaDePartidas)) {
        printf("Nenhuma partida cadastrada.\n");
        return;
    }

    printPartidaViewHeader();

    llForeach(listaDePartidas, imprimirPartida);
}

void viewBuscarPartidas()
{
    printf("=== Buscar Partidas ===\n");
    printf("Selecione o modo de busca:\n");
    printf("1 - Mandante\n");
    printf("2 - Visitante\n");
    printf("3 - Mandante ou Visitante\n");
    printf("Q - Cancelar\n");

    char opcao;
    LinkedList* lista = NULL;
    char prefix[TIME_MAX_NAME_SIZE];

    // Leitura da opção
    while (1) {
        opcao = toupper(readChar("Opcao: "));
        if (opcao == '1' || opcao == '2' || opcao == '3' || opcao == 'Q')
            break;

        printf("Opcao invalida!\n");
    }

    if (opcao == 'Q') {
        printf("Operacao cancelada.\n");
        return;
    }

    // Leitura do prefixo
    readString("Digite o prefixo do nome do time: ", prefix, TIME_MAX_NAME_SIZE);

    // Realiza a busca correta
    switch (opcao) {
        case '1':
            lista = partidaDBSearchMandante(prefix);
            break;

        case '2':
            lista = partidaDBSearchVisitante(prefix);
            break;

        case '3':
            lista = partidaDBSearchMandanteOrVisitante(prefix);
            break;
    }

    // Verifica se encontrou algo
    if (lista == NULL || llIsEmpty(lista)) {
        printf("Nenhuma partida encontrada com esse criterio.\n");
        if (lista) llFullFree(lista, NULL);
        return;
    }

    // Exibe lista
    printPartidaViewHeader();
    viewPartidas(lista);

    // Importante: liberar apenas a lista wrapper
    llFullFree(lista, NULL);
}

#endif