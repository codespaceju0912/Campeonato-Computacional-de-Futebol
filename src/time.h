#ifndef TIME_H
#define TIME_H

//struct é tipo uma classe em java

typedef struct {
    int id;
    char nome[50]; // Espaço para o nome do time

    int vitorias;  
    int empates;  
    int derrotas;  
    int golsMarcados; 
    int golsSofridos; 
} Time;

void TimeInicializar(Time *t, int id, const char *nome);
int TimeCalcularPG(const Time *t); // PG = Pontos Ganhos
int TimeCalcularSaldo(const Time *t); // Saldo de Gols

#endif