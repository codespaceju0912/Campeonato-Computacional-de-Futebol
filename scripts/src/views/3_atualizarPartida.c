#ifndef ATUALIZAR_PARTIDA_C
#define ATUALIZAR_PARTIDA_C 0

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "./0_utils.c"
#include "../../inc/collections/LinkedList.h"
#include "../../inc/service/model.h"
#include "../../inc/service/repo.h"

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
        partidaGetId(p),
        timeGetName(partidaGetT1(p)), partidaGetGolsT1(p),
        partidaGetGolsT2(p), timeGetName(partidaGetT1(p))
    );

    char buffer[16];

    printf("\nDigite os novos valores de gols.\n");
    printf("Se quiser manter o valor anterior, digite '-'.\n");

    // --- Gols do time 1 ---
    readString("Novos gols para o mandante: ", buffer, sizeof(buffer));
    int novosGolsT1 = partidaGetGolsT1(p);  // default mantém o antigo

    if (strcmp(buffer, "-") != 0) {
        // validar número
        char *endptr;
        long val = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0' || val < 0) {
            printf("Valor inválido. Mantendo gols anteriores (%d).\n", partidaGetGolsT1(p));
        } else {
            novosGolsT1 = (int)val;
        }
    }

    // --- Gols do time 2 ---
    readString("Novos gols para o visitante: ", buffer, sizeof(buffer));
    int novosGolsT2 = partidaGetGolsT2(p);

    if (strcmp(buffer, "-") != 0) {
        char *endptr;
        long val = strtol(buffer, &endptr, 10);

        if (endptr == buffer || *endptr != '\0' || val < 0) {
            printf("Valor inválido. Mantendo gols anteriores (%d).\n", partidaGetGolsT2(p));
        } else {
            novosGolsT2 = (int)val;
        }
    }

    // --- Exibe preview do resultado ---
    printf("\nNovo resultado previsto:\n");
    printf("%d | %s (%d) x (%d) %s\n",
        partidaGetId(p),
        timeGetName(partidaGetT1(p)), novosGolsT1,
        novosGolsT2, timeGetName(partidaGetT2(p))
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
    bool ok;

    ok = partidaSetGolsT1(p, novosGolsT1);
    if(!ok) {
        printf("Erro interno: talvez você tenha passado um valor negativo para número de gols");
        return;
    }

    ok = partidaSetGolsT2(p, novosGolsT2);
    if(!ok) {
        printf("Erro interno: talvez você tenha passado um valor negativo para número de gols");
        return;
    }

    printf("Partida atualizada com sucesso!\n");
}

#endif