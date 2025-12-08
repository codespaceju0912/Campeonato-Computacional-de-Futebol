#ifndef TIME_DB_C
#define TIME_DB_C 0

#include <stdio.h>

#include "./../model/Time.c"
#include "./../../inc/collections/LinkedList.h"

#define TIME_CSV_PATTERN "%d;%[^,\n]"

#if defined(_WIN32) || defined(_WIN64)
    #define TIME_CSV "FILE_PATH.csv"
#else
    #define TIME_CSV "FILE_PATH.csv"
#endif


typedef struct TimeDB
{
    LinkedList* times;
} TimeDB;


static TimeDB timeDB;
static char prefixSearch[TIME_MAX_NAME_SIZE];
static int timeIDSearch;

static bool addFirstTime(const char time_name[TIME_MAX_NAME_SIZE]) {
    Time* t = newTime(0, time_name);
    bool ok;

    if(t == NULL)
        return false;

    ok = sllAdd(timeDB.times, t);
    if(!ok) {
        freeTime(t);
        return false;
    }

    return true;
}

static bool addNewTime(const char time_name[TIME_MAX_NAME_SIZE]) {
    Time* last;
    Time* new;
    bool ok;

    last = llGetLast(timeDB.times);
    new = newTime(last->id+1, time_name);
    
    if(new == NULL)
        return false;

    ok = sllAdd(timeDB.times, new);
    if(!ok) {
        freeTime(new);
        return false;
    }

    return true;
}

bool addTime(const char time_name[TIME_MAX_NAME_SIZE]) {
    if(timeDB.times == NULL)
        return false;

    if(llIsEmpty(timeDB.times))
        return addFirstTime(time_name);
    else
        return addNewTime(time_name);
}

static bool checkPrefix(void* time) {
    Time* cast = (Time*)time;
    register int i;

    for(i = 0; i < TIME_MAX_NAME_SIZE; i++) {
        if(prefixSearch[i] == '\0')
            return true; // early stop
        if(cast->name[i] != prefixSearch[i])
            return false;
    }

    return true;
}

static void setPrefix(const char prefix[TIME_MAX_NAME_SIZE]) {
    register unsigned int i;

    for(i = 0; i < TIME_MAX_NAME_SIZE; i++)
        prefixSearch[i] = prefix[i];

    prefixSearch[TIME_MAX_NAME_SIZE] = '\0';
}

LinkedList* searchByPrefix(const char prefix[TIME_MAX_NAME_SIZE]) {
    setPrefix(prefix);

    return llSearchAll(timeDB.times, checkPrefix);
}

static char* strchar(char* str, const char ch) {
    register unsigned int i;

    while (str[i] != ch)
        i++;
    
    return &str[i];
}

/*
timeFromFile
@brief creates a new Time struct based on csv line, passed as buff.

@param buff contains the csv line that contains the Time data.

@returns Time* a pointer to created Time struct. If there is not enough memory, it will return NULL.
*/
static Time* timeFromFile(const char* buff) {
    char timeName[TIME_MAX_NAME_SIZE];
    int timeID;

    sscanf(buff, TIME_CSV_PATTERN, &timeID, timeName);
    return newTime(timeID, timeName);
}

bool startTimeDB() {
    char buffer[100];
    Time* t;
    FILE* f;

    if(timeDB.times == NULL) {
        timeDB.times = newLinkedList();

        if(timeDB.times == NULL)
            return false;
        
        f = fopen(TIME_CSV, "r");

        if(f == NULL) {
            perror("fopen");
            return false;
        }

        // clean header
        fgets(buffer, 100, f);

        while(fgets(buffer, 100, f))
        {
            t = timeFromFile(buffer);
            if(t == NULL) {
                llFullFree(timeDB.times, freeTime);
                return false;
            }
            llAdd(timeDB.times, t);
        }
    }

    return true;
}

static bool timeGetById(void* time) {
    return ((Time*)time)->id == timeIDSearch;
}

Time* timeDBGetByID(int id) {
    timeIDSearch = id;
    return llFindFirst(timeDB.times, timeGetById);
}

#endif