#include "./modeloBDP.c"

typedef struct dsp_time
{
    int vitorias;
    int derrotas;
    int empate;
    int gols_marcados;
    int gols_sofridos;
    Time* time;
} DesempenhoTime;

DesempenhoTime* dspt_create()
{
    DesempenhoTime* d = (DesempenhoTime*)malloc(sizeof(DesempenhoTime));
    if(d == NULL)
        return NULL;

    d->vitorias = 0;
    d->derrotas = 0;
    d->empate = 0;
    d->gols_marcados = 0;
    d->gols_sofridos = 0;
    d->time = NULL;
    return d;
}


int desempenho_saldo(DesempenhoTime* desempenho)
{
    if(desempenho==NULL)
    {
        return 1;
    }
    return desempenho->gols_marcados - desempenho->gols_sofridos;
}

int desempenho_pontos_ganhos(DesempenhoTime* desempenho)
{
    if(desempenho==NULL)
    {
        return 1;
    }
    return 3 * (desempenho->vitorias) + (desempenho->empate); 
}


DesempenhoTime* bdp_desempenho(BDPartida* bd, Time* t)
{
    DesempenhoTime* d;
    
    if(bd == NULL || t == NULL)
        return NULL;
    
    d = dspt_create();
    if(d == NULL)
        return NULL;
    d->time = t;
    
    for(int i = 0; i < bd->qtd_partidas; i++)
    {
        Partida p = bd->partidas[i];
        // verificar se a partirda engloba o time t;
        if(strcmp(t->nome, p.time1->nome)== 0){
            if(p.golsTime1 > p.golsTime2){
                d->vitorias++;
            }
            else if(p.golsTime1 == p.golsTime2){
                d->empate++;
            }
            else{
                d->derrotas++;
            }
            d->gols_marcados += p.golsTime1;
            d->gols_sofridos += p.golsTime2;
        }
    }

    return d;
}




int main(){
    BDPartida bd;
    Time* t = t_create();
    t_set_id(t, 0);
    t_set_nome(t, "JAVAlis");
    
    // Exemplo de preenchimento dos índices 0, 1 e 2 de bd.partidas

    // Criação dos times
    Time* t1 = t_create();
    t_set_id(t1, 0);
    t_set_nome(t1, "JAVAlis");

    Time* t2 = t_create();
    t_set_id(t2, 1);
    t_set_nome(t2, "C Ball Master");

    Time* t3 = t_create();
    t_set_id(t3, 2);
    t_set_nome(t3, "StructBall");

    Time* t4 = t_create();
    t_set_id(t4, 3);
    t_set_nome(t4, "Pointer FC");

    // ===== Preenchendo as partidas =====

    // Partida 0
    bd.partidas[0].id = 0;
    bd.partidas[0].time1 = t1;
    bd.partidas[0].time2 = t2;
    bd.partidas[0].golsTime1 = 3;
    bd.partidas[0].golsTime2 = 1;

    // Partida 1
    bd.partidas[1].id = 1;
    bd.partidas[1].time1 = t3;
    bd.partidas[1].time2 = t4;
    bd.partidas[1].golsTime1 = 2;
    bd.partidas[1].golsTime2 = 2;

    // Partida 2
    bd.partidas[2].id = 2;
    bd.partidas[2].time1 = t1;
    bd.partidas[2].time2 = t3;
    bd.partidas[2].golsTime1 = 1;
    bd.partidas[2].golsTime2 = 0;

    bd.qtd_partidas = 3;


    DesempenhoTime* trem = bdp_desempenho(&bd, t);
    if(trem == NULL){
        return 1;
    }
    return 0;
}