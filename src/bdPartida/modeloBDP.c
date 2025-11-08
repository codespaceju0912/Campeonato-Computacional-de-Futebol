#include "./../partida/modeloP.c"
#define MAX_PARTIDA 90 

typedef struct bdpartida
{
    Partida partidas[MAX_PARTIDA];
}BDPartida;

BDTime *bdt_create(){
    BDTime *bdt = (BDTime *)malloc(sizeof(BDTime));
    return bdt;
}


Time* time_from_string(char* str) {
    int id;
    char* nome = (char*) malloc(sizeof(char) * MAIOR_NOME_POSSIVEL);
    Time* time;
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

    strncpy(nome, token, MAIOR_NOME_POSSIVEL - 1);
    nome[MAIOR_NOME_POSSIVEL - 1] = '\0'; // garante o nulo final

    time = t_create();
    if(time == NULL)
        return NULL;

    response = t_set_id(time, id);
    if(response == ID_MENOR_OU_IGUAL_A_ZERO)
    {
        t_free(time);
        return NULL;
    }

    response = t_set_nome(time, nome);

    if(response == NOME_MUITO_GRANDE)
    {
        t_free(time);
        return NULL;
    }

    return time;
}