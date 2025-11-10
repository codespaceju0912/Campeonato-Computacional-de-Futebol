#include "./../time/caso_de_usoT.c"
#include <stdio.h>
#define MAX_TIMES 10
#define DB_TIME_ARQUIVO "file.csv"


typedef struct bdtime
{
    Time times[MAX_TIMES];
}BDTime;

BDTime *bdt_create(){
    BDTime *bdt = (BDTime *)malloc(sizeof(BDTime));
    return bdt;
}


Time* time_from_string(char* str, Time* time) { // Converte uma string CSV em um objeto Time
    int id;
    char* nome = (char*) malloc(sizeof(char) * MAIOR_NOME_POSSIVEL);
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


void load_dbt(BDTime* bd) //Carrega o banco de dados de times a partir do arquivo CSV
{
    FILE *times = fopen("./../../data/times.csv", "r");
    if(times == NULL){
        fclose(times);
        return;
    } 
    
    char* str;
    char linha[100];
    fgets(linha, sizeof(linha), times); // removendo o cabeçalho
    for(int i = 0; (str = fgets(linha, sizeof(linha), times))!=NULL; i++)
        time_from_string(str, &(bd->times[i]));

    fclose(times);
}

Time* bdt_get_time(BDTime* bd, unsigned int index) {
    if(bd == NULL)
        return NULL;

    if(index > MAX_TIMES)
        return NULL;

    return &bd->times[index];
}

int main(){
    BDTime bd;
    BDTime* bd_ptr = &bd;
    load_dbt(bd_ptr);

    int id_time_x = 50;
    id_time_x = bd.times[0].id;
    id_time_x = bd.times[5].id;
    id_time_x = bd.times[9].id;
    id_time_x = bd.times[1].id;

    char str[30];

    printf("qual o prefixo? ");
    scanf("%s", str);
    

    for(int i = 0; i < MAX_TIMES+1; i++)
        if(t_tem_prefixo(bdt_get_time(bd_ptr, i), str)){
            printf("%d: %s",bdt_get_time(bd_ptr, i)->id, bdt_get_time(bd_ptr, i)->nome);
        }

    return 0;
}