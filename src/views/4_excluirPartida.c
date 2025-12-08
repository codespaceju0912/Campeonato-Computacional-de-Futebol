#ifndef EXCLUIR_PARTIDA_VIEW
#define EXCLUIR_PARTIDA_VIEW 0

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "./0_utils.c"
#include "./../../inc/collections/LinkedList.h"
#include "./../model/Partida.c" 
#include "./../repo/PartidaDB.c" 
#include "./../repo/TimeDB.c" 

static int gSearchID;



bool removePredicate(void* p) {
    if(p == NULL)
        return false;

    if (((Partida*)p)->id == gSearchID) {
        freePartida(p);
        return true; 
    }

    return false;
}


// =====================================================
// VIEW: Exclusão de Partida
// =====================================================
void viewExcluirPartida()
{
    printf("=== Excluir Partida ===\n");
    printf("Selecione o modo de busca:\n");
    printf("1 - Mandante\n");
    printf("2 - Visitante\n");
    printf("3 - Mandante ou Visitante\n");
    printf("4 - Todos\n");
    printf("Q - Cancelar\n");

    char opcao;
    while (1) {
        opcao = toupper(readChar("Opcao: "));
        if (opcao == '1' || opcao == '2' || opcao == '3' ||
            opcao == '4' || opcao == 'Q')
            break;

        printf("Opcao invalida. Tente novamente.\n");
    }

    if (opcao == 'Q') {
        printf("Operacao cancelada.\n");
        return;
    }

    // -------------------------------
    // Busca das partidas
    // -------------------------------
    char nome[TIME_MAX_NAME_SIZE];
    LinkedList* resultado = NULL;

    switch (opcao) {
        case '1':
            readString("Nome do mandante: ", nome, TIME_MAX_NAME_SIZE);
            resultado = partidaDBSearchMandante(nome);
            break;

        case '2':
            readString("Nome do visitante: ", nome, TIME_MAX_NAME_SIZE);
            resultado = partidaDBSearchVisitante(nome);
            break;

        case '3':
            readString("Nome do time (mandante/visitante): ", nome, TIME_MAX_NAME_SIZE);
            resultado = partidaDBSearchMandanteOrVisitante(nome);
            break;

        case '4':
            resultado = partidaDBGetAllPartidas();
            break;
    }

    if (resultado == NULL || llIsEmpty(resultado)) {
        printf("Nenhuma partida encontrada.\n");
        if (resultado) llFullFree(resultado, NULL);
        return;
    }

    // -------------------------------
    // Exibir lista encontrada
    // -------------------------------
    printf("\nPartidas encontradas:\n");
    viewPartidas(resultado);

    // -------------------------------
    // Selecionar ID
    // -------------------------------
    int id = readInt("\nDigite o ID da partida para excluir: ");

    // -------------------------------
    // Confirmar exclusão
    // -------------------------------
    char confirm;
    do {
        confirm = toupper(readChar("Confirmar exclusao? (S/N): "));
    } while (confirm != 'S' && confirm != 'N');

    if (confirm == 'N') {
        printf("Operacao cancelada.\n");
        llFullFree(resultado, NULL);
        return;
    }


    bool removed = llRemoveFirstFound(partidaDB.partidas, removePredicate);

    if (!removed) {
        printf("Erro: Nao foi possivel remover a partida.\n");
    } else {
        printf("Partida removida com sucesso.\n");
    }

    if(opcao != '4') // Caso a opção seja == 4 pega-se a lista do database. Então, desalocar ela porvocará um seguimentation fault
        llFullFree(resultado, NULL);
}



#endif
