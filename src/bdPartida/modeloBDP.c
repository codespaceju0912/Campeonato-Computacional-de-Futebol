#include "./../partida/modeloP.c"
#include "./../bdTime/modeloBDT.c"
#include <stdio.h>
#define MAX_PARTIDA 90

typedef struct bdpartida
{
    Partida partidas[MAX_PARTIDA];
    int qtd_partidas;
}BDPartida;

BDPartida *bdp_create(){
    BDPartida *bdp = (BDPartida *)malloc(sizeof(BDPartida));
    bdp->qtd_partidas = 0;
    return bdp;
}


Partida* partida_from_string(char* str, Partida* partida, BDTime* bdt) {
    int id;
    int golsTime1;
    int golsTime2;
    Time* time1 = (Time*) malloc(sizeof(Time*));
    Time* time2 = (Time*) malloc(sizeof(Time*));
    int response;

    if(str == NULL)
        return NULL;

    // coletando os dados da string
    char* token = strtok(str, ",");
    if (token == NULL)
        return NULL;

    id = atoi(token); // converte a parte numérica para int
    
    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;

        
    time1 = bdt_get_time(bdt, atoi((token)));

    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;

    time2 = bdt_get_time(bdt, atoi((token)));

    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;

    golsTime1 = atoi(token);

    token = strtok(NULL, ",");
    if (token == NULL)
        return NULL;

    golsTime2 = atoi(token);

    if(partida == NULL)
        return NULL;

    response = p_get_id(partida);//envia para TAD Partida o id
    if(response == OBJETO_COM_ID_ESPECIFICADO_NAO_EXISTE_FLAG) //verifica se o id é menor que 0
    {
        t_free(partida);
        return NULL;
    }

    response = p_get_time1(partida);//envia para TAD Partida o time1
    response = p_get_time2(partida);//envia para TAD Partida o time2

    response = p_get_gols_time1(partida);//envia para TAD Partida a quantidade de jogo
    if(response == GOL_NAO_POSSUI_FLAG) //verifica se o gol possui flag
    {
        t_free(partida);
        return NULL;
    }
    response = p_get_gols_time2(partida);//envia para TAD Partida a quantidade de jogo
    if(response == GOL_NAO_POSSUI_FLAG) //verifica se o gol possui flag
    {
        t_free(partida);
        return NULL;
    }
    
    return partida;
}


void load_dbt(BDPartida* bd, BDTime* time)
{
    int i;
    FILE *partidas = fopen("./../../data/partidas_completo.csv", "r");
    if(partidas == NULL){
        fclose(partidas);
        return;
    } 
    
    char* str;
    char linha[100];
    fgets(linha, sizeof(linha), partidas); // removendo o cabeçalho
    for(i = 0; (str = fgets(linha, sizeof(linha), partidas))!=NULL; i++)
        partida_from_string(str, &(bd->partidas[i]), time);
    bd->qtd_partidas = i;
    fclose(partidas);
}

Partida* bdp_get_partida(BDPartida* bd, unsigned int index) {
    if(bd == NULL)
        return NULL;

    if(index > MAX_PARTIDA)
        return NULL;

    return &bd->partidas[index];
}