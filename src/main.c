#include "./collections/LinkedList.c"
#include "./repo/TimeDB.c"
#include "./repo/PartidaDB.c"
#include "./views/1_time.c"
#include "./views/2_partida.c"
#include "./views/3_atualizarPartida.c"
#include "./views/4_excluirPartida.c"
#include "./views/5_inserirPartida.c"
#include "./views/6_imprimirTabelaClassificacao.c"
#include "./views/menu.c"

void printFPartida(void* p) {
    printPartida((Partida*)p);
}


int main() {
    startTimeDB();
    startPartidaDB();

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