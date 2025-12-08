#ifndef PARTIDA_DB_C
#define PARTIDA_DB_C 0

#include <stdio.h>

#include "./../model/Partida.c"
#include "./TimeDB.c"
#include "./../../inc/collections/LinkedList.h"

#define PARTIDA_CSV_PATTERN "%d;%d;%d;%d;%d%[^,\n]"

#if defined(_WIN32) || defined(_WIN64)
    #define PARTIDA_CSV "FILE_PATH.csv"
#else
    #define PARTIDA_CSV "FILE_PATH.csv"
#endif


typedef struct PartidaDB
{
    LinkedList* partidas;
} PartidaDB;


static PartidaDB partidaDB;
static int partidaIDSearch;
static Partida* partidaJournal = NULL;

bool partidaDBStartInsertTransaction() {
    if(partidaJournal == NULL)
        return true;
    return false;
}

bool partidaDBInsertCommit() {
    bool ok;

    ok = sllAdd(partidaDB.partidas, partidaJournal);
    if(!ok) {
        return false;
    }
    partidaJournal = NULL;
}

void partidaDBInsertRollBack() {
    if(partidaJournal != NULL) {
        freePartida(partidaJournal);
        partidaJournal = NULL;
    }
}

static int nextPartidaID() {
    Partida* last = (Partida*)llGetLast(partidaDB.partidas);
    return last->id+1;
}

typedef enum {PARTIDA_DATABASE_NOT_STARTED_YET, ANOTHER_TRANSACTION_NOT_CLOSE, MEMORY_NOT_ENOUGH_EXCEPTION, TIME_1_EQUALS_TIME_2, TIME_1_DOES_NOT_EXISTS, TIME_2_DOES_NOT_EXISTS, SUCCESS} AddPartidaReponse;

AddPartidaReponse addPartida(int t1ID, int t2ID, int gT1, int gT2) {
    Time* t1;
    Time* t2;
    bool ok;

    if(partidaDB.partidas == NULL)
        return PARTIDA_DATABASE_NOT_STARTED_YET;
    
    if(partidaJournal != NULL)
        return ANOTHER_TRANSACTION_NOT_CLOSE;


    if(t1ID == t2ID)
        return TIME_1_EQUALS_TIME_2;

    t1 = timeDBGetByID(t1ID);
    if(t1 == NULL)
        return TIME_1_DOES_NOT_EXISTS;

    t2 = timeDBGetByID(t2ID);
    if(t2 == NULL)
        return TIME_2_DOES_NOT_EXISTS;

    if(llIsEmpty(partidaDB.partidas))
        partidaJournal = newPartida(0, t1, t2, gT1, gT2);
    else
        partidaJournal = newPartida(nextPartidaID(), t1, t2, gT1, gT2);

    if(partidaJournal == NULL) {
        return MEMORY_NOT_ENOUGH_EXCEPTION;
    }

    return SUCCESS;
}

static Partida* partidaFromFile(const char* buff) {
    int id;
    int t1ID;
    int t2ID;
    int gT1;
    int gT2;

    Time* t1;
    Time* t2;

    sscanf(buff, PARTIDA_CSV_PATTERN, &id, &t1ID, &t2ID, &gT1, &gT2);

    t1 = timeDBGetByID(t1ID);
    if(t1 == NULL)
        return NULL;
    t2 = timeDBGetByID(t2ID);
    if(t2 == NULL)
        return NULL;

    return newPartida(id, t1, t2, gT1, gT2);
}

bool startPartidaDB() {
    char buffer[100];
    Partida* p;
    FILE* f;

    if(partidaDB.partidas == NULL) {
        partidaDB.partidas = newLinkedList();

        if(partidaDB.partidas == NULL)
            return false;
        
        f = fopen(PARTIDA_CSV, "r");
        
        if(f == NULL) {
            perror("fopen");
            return false;
        }

        // clean header
        fgets(buffer, 100, f);

        while(fgets(buffer, 100, f))
        {
            p = partidaFromFile(buffer);
            if(p == NULL) {
                llFullFree(partidaDB.partidas, freePartida);
                return false;
            }
            llAdd(partidaDB.partidas, p);
        }
    }

    return true;
}

bool partidaDBMandantePrefixCheck(void* partida) {
    if(partida == NULL)
        return false;

    return checkPrefix(((Partida*)partida)->t1);
}

LinkedList* partidaDBSearchMandante(char timeName[TIME_MAX_NAME_SIZE]) {
    if(timeDB.times == NULL || partidaDB.partidas == NULL)
        return NULL;

    setPrefix(timeName);
    return llSearchAll(partidaDB.partidas, partidaDBMandantePrefixCheck);
}

bool partidaDBVisitantePrefixCheck(void* partida) {
    if(partida == NULL)
        return false;

    return checkPrefix(((Partida*)partida)->t2);
}

LinkedList* partidaDBSearchVisitante(char timeName[TIME_MAX_NAME_SIZE]) {
    if(timeDB.times == NULL || partidaDB.partidas == NULL)
        return NULL;

    setPrefix(timeName);
    return llSearchAll(partidaDB.partidas, partidaDBVisitantePrefixCheck);
}

bool partidaDBMandanteOrVisitantePrefixCheck(void* partida) {
    if(partida == NULL)
        return false;

    return checkPrefix(((Partida*)partida)->t1) || checkPrefix(((Partida*)partida)->t2);
}

LinkedList* partidaDBSearchMandanteOrVisitante(char timeName[TIME_MAX_NAME_SIZE]) {
    if(timeDB.times == NULL || partidaDB.partidas == NULL)
        return NULL;

    setPrefix(timeName);
    return llSearchAll(partidaDB.partidas, partidaDBMandanteOrVisitantePrefixCheck);
}

static bool partidaGetById(void* p) {
    if(p == NULL)
        return false;

    return ((Partida*)p)->id == partidaIDSearch;
}

Partida* partidaDBGetById(int id) {
    if(partidaDB.partidas == NULL)
        return NULL;

    partidaIDSearch = id;

    return llFindFirst(partidaDB.partidas, partidaGetById);
}

void printPartida(Partida* p) {
    if(p == NULL)
        printf("Partida Indefinida\n");
    else
        printf("ID: %d, Time 1: %s, Time 2: %s, Gols Time 1: %d, Gols Time 2: %d\n", p->id, p->t1->name, p->t2->name, p->golsT1, p->golsT2);
}


LinkedList* partidaDBGetAllPartidas() {
    return partidaDB.partidas;
}

#endif