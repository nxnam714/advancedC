#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "AtOsal.h"

#define MAX_STDIN_SIZE 20
#define NUMBER_OF_STDIN 4
#define REGISTER_SIZE 4
#define MEM_SIZE (16*REGISTER_SIZE)

void *global_mem;

void memInit();

typedef struct cmdEvent {
    char key[MAX_STDIN_SIZE];
    int value;
} cmdEvent_t;

enum eventType {READ, WRITE, THREADSTART, THREADSTOP};

int getcmdtype(char* code);

int eventcmp(char *k, struct cmdEvent* b);

void *registerRead(int addr);

void registerWrite(int addr, void *value);