#ifndef TIME_H
#define TIME_H

//struct é tipo uma classe em java

typedef struct {
    int id;
    char nome[50]; // Espaço para o nome do time

    int vitorias;  // Vitórias
    int empates;  // Empates
    int derrotas;  // Derrotas
    int golsMarcados; // Gols Marcados
    int golsSofridos; // Gols Sofridos
} Time;

void Time_inicializar(Time *t, int id, const char *nome);
int Time_calcular_pg(const Time *t); // PG = Pontos Ganhos
int Time_calcular_saldo(const Time *t); // Saldo de Gols

#endif