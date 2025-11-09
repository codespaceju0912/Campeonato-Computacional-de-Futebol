#include "./modeloT.c"

typedef enum {MENOR_QUE=-1,
     IGUAL,
     MAIOR_QUE, 
     PONTEIRO_1_NULO, 
     PONTEIRO_2_NULO
} comparacao;

comparacao t_comparar(Time *t1, Time *t2){
    if(t1 == NULL)
        return PONTEIRO_1_NULO;
    if(t2 == NULL)
        return PONTEIRO_2_NULO;
    if(t1->id == t2->id)
        return IGUAL;
    if(t1->id > t2->id)
        return MAIOR_QUE;
    return MENOR_QUE;
}

typedef enum{FALSE, TRUE} bool;


bool t_tem_prefixo(Time *t, char *prefixo){
    if(t == NULL || prefixo == NULL || strlen(prefixo) > strlen(t->nome))
        return FALSE;
    return strncmp(t->nome, prefixo, strlen(prefixo)) == 0;
}

/*
// test case
int main(){
    Time *t = t_create();
    t_set_nome(t, "Julia");
    t_set_id(t, 2);

    t_set_nome(t, "Bruno da Fonseca Chevitarese");
    t_set_nome(t, NULL);
    t_set_nome(NULL, NULL);
    t_set_id(t, 0);
    t_set_id(t, -1);
    t_set_id(NULL, -1);
    
    bool r;
    r = t_tem_prefixo(t, "Ju");
    r = t_tem_prefixo(NULL, "J");
    r = t_tem_prefixo(t, "ju");
    r = t_tem_prefixo(t, "Juh");

    t_free(t);
    return 0;
}
*/