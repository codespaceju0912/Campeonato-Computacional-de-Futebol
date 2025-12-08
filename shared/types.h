#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H 0

#include "./bool.h"

typedef bool (*searchFunc)(void*);
typedef void(*freeFunc)(void*);
typedef void(*foreachFunc)(void*);
typedef bool(*findFirstFunc)(void*);
typedef bool(*removeFunc)(void*);

typedef enum {less_than=-1, equal, greater_than} Order;
typedef Order(*orderFunc)(void* a, void* b);


#endif