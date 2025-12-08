#ifndef INSERIR_PARTIDA_VIEW_C
#define INSERIR_PARTIDA_VIEW_C 0

#include "./0_utils.c"
#include "../../inc/collections/LinkedList.h"
#include "../../inc/service/model.h"
#include "../../inc/service/repo.h"
#include "./2_partida.c"

extern Partida* partidaJournal;

// --------------------------------------------------------
// VIEW: Inserir nova partida
// --------------------------------------------------------
void viewInserirPartida()
{
    char confirm;
    printf("=== Inserir Nova Partida ===\n");

    // -----------------------------
    // Leitura dos inputs
    // -----------------------------
    int t1ID = readInt("Digite o ID do Time 1 (mandante): ");
    int t2ID = readInt("Digite o ID do Time 2 (visitante): ");

    int gT1  = readInt("Gols do Time 1: ");
    int gT2  = readInt("Gols do Time 2: ");

    // -----------------------------
    // Chamada da função principal
    // -----------------------------
    bool tx = partidaDBStartInsertTransaction();
    if(!tx) {
        printf("Erro interno: Não foi possível iniciar a transação.\n");
        return;
    }
    AddPartidaReponse resp = addPartida(t1ID, t2ID, gT1, gT2);

    // -----------------------------
    // Tratamento das respostas
    // -----------------------------
    switch (resp)
    {
        case PARTIDA_DATABASE_NOT_STARTED_YET:
            printf("Erro interno: Partida Database ainda não foi incializado ou foi inicializado incorretamente.\n");
            break;

        case ANOTHER_TRANSACTION_NOT_CLOSE:
            printf("Erro interno: Alguma transação de inserção de partida não foi finalizada corretamente.\n");
            break;

        case MEMORY_NOT_ENOUGH_EXCEPTION:
            printf("Erro: Memoria insuficiente para criar nova partida.\n");
            break;

        case TIME_1_EQUALS_TIME_2:
            printf("Erro: O Time 1 e o Time 2 nao podem ser iguais.\n");
            break;

        case TIME_1_DOES_NOT_EXISTS:
            printf("Erro: O Time 1 (ID %d) nao existe no banco.\n", t1ID);
            break;

        case TIME_2_DOES_NOT_EXISTS:
            printf("Erro: O Time 2 (ID %d) nao existe no banco.\n", t2ID);
            break;

        case SUCCESS:
            do {
                printf("Confirmar inserção do registro abaixo?\n");
                printPartidaViewHeader();
                imprimirPartida(partidaJournal);
                confirm = toupper(readChar("(S/N): "));
            } while (confirm != 'S' && confirm != 'N');

            if (confirm == 'N') {
                printf("Operacao cancelada.\n");
                partidaDBInsertRollBack();
                return;
            }

            tx = partidaDBInsertCommit();
            if(!tx) {
                partidaDBInsertRollBack();
                printf("Erro: não foi possível concluir a transação; possívelmente há memória insuficiente para o programa.");
            } else {            
                printf("Partida cadastrada com sucesso!\n");
            }
            break;

        default:
            printf("Erro desconhecido ao inserir partida.\n");
            break;
    }
}


#endif