#ifndef MENU_VIEW_C
#define MENU_VIEW_C 0

#include <stdio.h>
#include <ctype.h>
#include "./0_utils.c"   // para readChar()

// ----------------------------------------------
// VIEW — MENU PRINCIPAL
// ----------------------------------------------
char viewMenuPrincipal()
{
    printf("\n=====================================\n");
    printf("           MENU PRINCIPAL\n");
    printf("=====================================\n");
    printf("1 - Consultar Time\n");
    printf("2 - Consultar Partidas\n");
    printf("3 - Atualizar Partida\n");
    printf("4 - Remover Partida\n");
    printf("5 - Inserir Partida\n");
    printf("6 - Imprimir Tabela de Classificacao\n");
    printf("Q - Sair\n");
    printf("=====================================\n");

    char opcao;

    while (1) {
        opcao = toupper(readChar("Opcao: "));
        if (opcao == '1' || opcao == '2' || opcao == '3' ||
            opcao == '4' || opcao == '5' || opcao == '6' ||
            opcao == 'Q')
            break;

        printf("Opcao invalida! Tente novamente.\n");
    }

    return opcao;
}

#endif
