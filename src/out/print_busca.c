#include <stdio.h>
#include "./../bdTime/casos_de_usoBDT.c"
#include "./../bdPartida/caso_de_usoBDP.c"


void print_busca_time(Stack* s)
{
    if(s == NULL)
        return;

    while (!stack_is_empty(s))
    {
        DesempenhoTime* dt = (DesempenhoTime*)stack_pop(s);
        imprime_time(dt);
    }
}

void imprime_time(DesempenhoTime* dt)
{
    int saldo = desempenho_saldo(dt);
    int pontos = desempenho_pontos_ganhos(dt);
    Time* time = dt->time;
    printf("%-5d %-15s %-5d %-5d %-5d %-5d %-5d %-5d %-5d", time->id, time->nome, dt->vitorias, dt->empate, dt->derrotas, dt->gols_marcados, dt->gols_sofridos, saldo, pontos);

}

Stack* constroi_desempenho_time(BDPartida* bdp, Stack* s)
{
    Stack* result;
    Time* t;

    result = stack_create();
    if(result == NULL)
        return NULL;

    for(t = stack_pop(s); t != NULL; t = stack_pop(s))
    {
        DesempenhoTime* d = bdp_desempenho(bdp, t);
        if(d == NULL)
        {
            stack_free(result);
            return NULL;
        }
        stack_push(result, d);
    }

    return result;
}

void busca_time_e_imprime_resultado(BDTime* bd,BDPartida* bdp, char* prefix)
{
    if(bd == NULL)
    {
        perror("Banco de Dados Time foi passado vazio.");
        return;
    }
    if(prefix == NULL)
    {
        perror("Prefixo para busca passado é nulo");
        return;
    }

    Stack* search_results = bdt_busca(bd, prefix);
    if(search_results == NULL)
    {
        perror("Time com préfixo fornecido não encontrado");
        return;
    }

    Stack* desempenhos = constroi_desempenho_time(bdp, search_results);
    if(desempenhos == NULL)
    {
        stack_free(search_results);
        perror("Memória insuficiente para executar a operação");
        return;
    }

    print_busca_time(desempenhos);
    stack_free(search_results);
    stack_free(desempenhos);
}