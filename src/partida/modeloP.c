#include "./../time/modeloT.c"
#define GOL_NAO_POSSUI_FLAG -1
typedef struct partida {
    int id;
    Time* time1;
    Time* time2;
    int golsTime1;
    int golsTime2;
} Partida;

Partida *p_create(){
    Partida *p = (Partida *)malloc(sizeof(Partida));
    if(p == NULL) 
        return NULL;
    p->id = 0;
    p->time1 = NULL;
    p->time2 = NULL;
    p->golsTime1 = 0;
    p->golsTime2 = 0;
    return p;
}

void p_free(Partida *p){
    if(p != NULL)
        free(p);
}

int p_get_id(Partida *p) {
    if (p == NULL)
        return OBJETO_COM_ID_ESPECIFICADO_NAO_EXISTE_FLAG;
    return p->id;
}

Time* p_get_time1(Partida *p) {
    if (p == NULL)
        return NULL;
    return p->time1;
}

Time* p_get_time2(Partida *p) {
    if (p == NULL)
        return NULL;
    return p->time2;
}

int p_get_gols_time1(Partida *p) {
    if (p == NULL)
        return GOL_NAO_POSSUI_FLAG;
    return p->golsTime1;
}

int p_get_gols_time2(Partida *p) {
    if (p == NULL)
        return GOL_NAO_POSSUI_FLAG;
    return p->golsTime2;
}

// Enum para códigos de retorno das funções set
typedef enum {
    PARTIDA_SUCESSO,
    PARTIDA_PONTEIRO_NULO,
    PARTIDA_ID_INVALIDO,
    PARTIDA_TIME_NULO,
    PARTIDA_TIMES_IGUAIS,
    PARTIDA_GOLS_INVALIDOS
} p_set_resposta;

p_set_resposta p_set_id(Partida *p, int id) {
    if (p == NULL)
        return PARTIDA_PONTEIRO_NULO;

    if (id <= 0)
        return PARTIDA_ID_INVALIDO;

    p->id = id;
    return PARTIDA_SUCESSO;
}

p_set_resposta p_set_times(Partida *p, Time *t1, Time *t2) {
    if (p == NULL)
        return PARTIDA_PONTEIRO_NULO;

    if (t1 == NULL || t2 == NULL)
        return PARTIDA_TIME_NULO;

    if (t_get_id(t1) == t_get_id(t2))
        return PARTIDA_TIMES_IGUAIS;

    p->time1 = t1;
    p->time2 = t2;
    return PARTIDA_SUCESSO;
}

p_set_resposta p_set_gols(Partida *p, int gols1, int gols2) {
    if (p == NULL)
        return PARTIDA_PONTEIRO_NULO;

    if (gols1 < 0 || gols2 < 0)
        return PARTIDA_GOLS_INVALIDOS;

    p->golsTime1 = gols1;
    p->golsTime2 = gols2;
    return PARTIDA_SUCESSO;
}

// int main(){
//     Partida *q = p_create();
//     return 0;
// }