#ifndef VIEW_H
#define VIEW_H 0

/**
 * viewBuscarTimesPorPrefixo
 * 
 * Exibe a interface para o usuário buscar times no banco de dados através de um prefixo.
 * O usuário fornecerá um prefixo e a função exibirá os times correspondentes.
 */
void viewBuscarTimesPorPrefixo();

/**
 * viewBuscarPartidas
 * 
 * Exibe a interface para o usuário buscar partidas no banco de dados.
 * O usuário poderá buscar partidas e a função exibirá os resultados correspondentes.
 */
void viewBuscarPartidas();

/**
 * viewAtualizarPartida
 * 
 * Exibe a interface para o usuário atualizar os dados de uma partida existente no banco de dados.
 * O usuário poderá alterar os gols ou times da partida.
 */
void viewAtualizarPartida();

/**
 * viewExcluirPartida
 * 
 * Exibe a interface para o usuário excluir uma partida do banco de dados.
 * O usuário fornecerá um identificador de partida e a função excluirá a partida correspondente.
 */
void viewExcluirPartida();

/**
 * viewInserirPartida
 * 
 * Exibe a interface para o usuário inserir uma nova partida no banco de dados.
 * O usuário fornecerá os dados da partida (times e gols) e a função adicionará a partida ao banco.
 */
void viewInserirPartida();

/**
 * viewTabelaClassificacao
 * 
 * Exibe a tabela de classificação atualizada dos times no torneio, com base nas partidas já realizadas.
 * A função calculará a classificação com base nos pontos e exibe a tabela na interface.
 */
void viewTabelaClassificacao();

/**
 * viewMenuPrincipal
 * 
 * Exibe o menu principal da interface, permitindo ao usuário escolher a ação desejada, como buscar times, buscar partidas, atualizar, excluir ou inserir partidas, entre outras.
 */
char viewMenuPrincipal();

#endif
