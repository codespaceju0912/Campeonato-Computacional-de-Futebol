#include "./../bdTime/modeloBDT.c"
#include "./../utils/stack.c"
#include "./../bdPartida/caso_de_usoBDP.c"
#define QUANT 2


Stack* bdt_busca(BDTime* bd, char *prefix){
    Stack* s = stack_create();
    if(s == NULL)
        return NULL;
    
    for(int i = MAX_TIMES-1; i >= 0; i--)
    {
        Time* t = bdt_get_time(bd, i);
        if(t_tem_prefixo(t, prefix))
            stack_push(s, t);
    }

    return s;
}

Stack* bdt_imprime_tudo(BDTime* bd){
    Stack* s = stack_create();
    if(s == NULL)
        return NULL;
    
    for(int i = MAX_TIMES-1; i >= 0; i--)
    {
        Time* t = bdt_get_time(bd, i);
        print_busca_time(s);
    }

    return s;
}


