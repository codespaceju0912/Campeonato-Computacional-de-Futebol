#include <stdio.h>

int main(){
    FILE *teste = fopen("../data/partidas_vazio.csv", "r");

    if(teste == NULL){
        printf("f");
    }
    else{
        printf("eh nois");
    }
    return 0;

}