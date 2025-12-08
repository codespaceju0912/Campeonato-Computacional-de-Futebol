#include <stdio.h>
#include "../inc/service/repo.h"
#include "../inc/views/view.h"

int main() {
    bool ok;

    ok = startTimeDB();
    if(!ok) {
        printf("Can't start TIME DB, check the var path at inc/service/repo.h");
        return 1;
    }

    ok = startPartidaDB();
    if(!ok) {
        printf("Can't start PARTIDA DB, check the var path at inc/service/repo.h");
        return 1;
    }

    while (1) {
    char opc = viewMenuPrincipal();

    if (opc == 'Q') break;

    switch (opc) {
        case '1': viewBuscarTimesPorPrefixo(); break;
        case '2': viewBuscarPartidas(); break;
        case '3': viewAtualizarPartida(); break;
        case '4': viewExcluirPartida(); break;
        case '5': viewInserirPartida(); break;
        case '6': viewTabelaClassificacao(); break;
        }
    }

    return 0;
}