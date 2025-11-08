#include "./../bdTime/modeloBDT.c"
#define MAX_TIMES 10

typedef struct buscaTime
{
    Time **pt_time;
    int quantidade;
}BDBuscaT;

BDBuscaT *bdbt_create(int quantidade){
    BDBuscaT *bdb = (BDBuscaT *)malloc(sizeof(BDBuscaT));
    if(bdb == NULL)
        return NULL;

    bdb->pt_time = (Time**)calloc(sizeof(Time*), quantidade);
    if(bdb->pt_time == NULL)
    {
        free(bdb);
        return NULL;
    }

    bdb->quantidade = quantidade;
    
    return bdb;
}

