#include "./../partida/modeloP.c"
#include <stdio.h>
#define MAX_PARTIDA 90 



typedef struct bdpartida
{
    Partida partidas[MAX_PARTIDA];
}BDPartida;

BDPartida *bdp_create(){
    BDPartida *bdp = (BDPartida *)malloc(sizeof(BDPartida));
    return bdp;
}

// Converte uma string CSV em um objeto Partida
Partida* partida_from_string(char* str, Partida* partida) {

    int id; //id da partida
    int IDTime1; //id do time1
    int IDTime2; //id do time2
    int golsTime1;
    int golsTime2;
 
    int response;// resposta das funções set

    if(str == NULL)
        return NULL;

    // Pegando e preenchendo ID da partida
    char* token = strtok(str, ",");
    if (token == NULL)
        return NULL;
    id = atoi(token); // converte a parte numérica para int

    // Pegando e preenchendo ID do time1
    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;
    IDTime1 = atoi(token);

    // Pegando e preenchendo ID do time2
    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;
    IDTime2 = atoi(token);

    // Pegando e preenchendo gols do time1
    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;
    golsTime1 = atoi(token);    

    // Pegando e preenchendo gols do time2
    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;
    golsTime2 = atoi(token);    

    // Criando a partida
    partida = t_create();
    if(partida == NULL)
        return NULL;

    // Preenchendo os dados da partida
    response = t_set_id(partida, id);
    if(response == ID_MENOR_OU_IGUAL_A_ZERO)
    {
        t_free(partida);
        return NULL;
    }

    response = t_set_times(partida, nome);

    if(response == NOME_MUITO_GRANDE)
    {
        t_free(time);
        return NULL;
    }

    return time;
}

void load_dbp(BDPartida* bd){ //Carrega o banco de dados de times a partir do arquivo CSV
    
    FILE *partidas = fopen("./../../data/partidas_completo.csv", "r");

    if(partidas == NULL){
        printf("Erro ao abrir o arquivo de times.\n");
        return;
    }

    char* str;
    char linha[100];
    fgets(linha, sizeof(linha), partidas); // removendo o cabeçalho
    for(int i = 0; (str = fgets(linha, sizeof(linha), partidas))!=NULL; i++)
        partida_from_string(str, &(bd->partidas[i]));



    fclose(partidas);
}