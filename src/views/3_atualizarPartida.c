#ifndef ATUALIZAR_PARTIDA_C
#define ATUALIZAR_PARTIDA_C 0

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "./0_utils.c"
// TODO: alterar isso aqui para .h depois
#include "./../../inc/collections/LinkedList.h"
#include "./../model/Partida.c" 
#include "./../repo/PartidaDB.c" 
#include "./../repo/TimeDB.c" 

// -----------------------------------------------------
// VIEW: Atualizar Partida
// -----------------------------------------------------
void viewAtualizarPartida()
{
    printf("=== Atualizar Partida ===\n");

    int id = readInt("Digite o ID da partida que deseja editar: ");

    Partida* p = partidaDBGetById(id);

    if (p == NULL) {
        printf("Partida com ID %d não encontrada.\n", id);
        return;
    }

    printf("\nPartida encontrada:\n");
    printf("%d | %s (%d) x (%d) %s\n",
        p->id,
        p->t1->name, p->golsT1,
        p->golsT2, p->t2->name
    );

    char buffer[16];

    printf("\nDigite os novos valores de gols.\n");
    printf("Se quiser manter o valor anterior, digite '-'.\n");

    // --- Gols do time 1 ---
    readString("Novos gols para o mandante: ", buffer, sizeof(buffer));
    int novosGolsT1 = p->golsT1;  // default mantém o antigo

    if (strcmp(buffer, "-") != 0) {
        // validar número
        char *endptr;
        long val = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0' || val < 0) {
            printf("Valor inválido. Mantendo gols anteriores (%d).\n", p->golsT1);
        } else {
            novosGolsT1 = (int)val;
        }
    }

    // --- Gols do time 2 ---
    readString("Novos gols para o visitante: ", buffer, sizeof(buffer));
    int novosGolsT2 = p->golsT2;

    if (strcmp(buffer, "-") != 0) {
        char *endptr;
        long val = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0' || val < 0) {
            printf("Valor inválido. Mantendo gols anteriores (%d).\n", p->golsT2);
        } else {
            novosGolsT2 = (int)val;
        }
    }

    // --- Exibe preview do resultado ---
    printf("\nNovo resultado previsto:\n");
    printf("%d | %s (%d) x (%d) %s\n",
        p->id,
        p->t1->name, novosGolsT1,
        novosGolsT2, p->t2->name
    );

    // --- Confirmação ---
    char c;
    do {
        c = readChar("Confirmar atualização? (S/N): ");
        c = toupper(c);
    } while (c != 'S' && c != 'N');

    if (c == 'N') {
        printf("Operação cancelada.\n");
        return;
    }

    // --- Atualiza valores ---
    p->golsT1 = novosGolsT1;
    p->golsT2 = novosGolsT2;

    printf("Partida atualizada com sucesso!\n");
}

#endif