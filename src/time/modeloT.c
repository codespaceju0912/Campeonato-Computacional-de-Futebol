#include <stdlib.h>
#include <string.h>
#include "./../shared/id_utils.h"
#define MAIOR_NOME_POSSIVEL 25

typedef struct time{
    int id;
    char nome [MAIOR_NOME_POSSIVEL];
}Time;

//TODO colocar  vitórias (V), empates (E), derrotas (D), gols marcados (GM) e gols sofridos (GS)

Time *t_create(){
    Time *t = (Time *)malloc(sizeof(Time));
    if(t == NULL )
        return NULL;
    t->id = 0;
    register char empty = '\0';
    for(register int i = 0; i < MAIOR_NOME_POSSIVEL; i++){
        t->nome[i] = empty;
    }
    return t;
}

void t_free(Time *t){
    if(t != NULL)
        free(t);
}

int t_get_id(Time *t){
    if(t != NULL)
        return t->id;
    return OBJETO_COM_ID_ESPECIFICADO_NAO_EXISTE_FLAG;
}

char *t_get_nome(Time *t){
    if(t!=NULL)
        return t->nome;
    return NULL;
}

typedef enum { 
    TIME_PONTEIRO_NULO, 
    ID_MENOR_QUE_ZERO,
    NOME_NULO,NOME_MUITO_GRANDE, 
    SUCESSO 
} t_set_resposta;

t_set_resposta t_set_id(Time *t, int id){
    if(t == NULL)
        return TIME_PONTEIRO_NULO;

    if(id < 0)
        return ID_MENOR_QUE_ZERO;

    t->id = id;
    return SUCESSO;
}

t_set_resposta t_set_nome(Time *t, char *nome){
    if(t == NULL)
        return TIME_PONTEIRO_NULO;
    if(nome == NULL)
        return NOME_NULO;
    if(strlen(nome) >= MAIOR_NOME_POSSIVEL)
        return NOME_MUITO_GRANDE;
    strcpy(t->nome, nome);
    return SUCESSO;
}

