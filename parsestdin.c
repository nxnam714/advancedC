#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STDIN_SIZE 20
#define NUMBER_OF_STDIN 4
#define REGISTER_SIZE 4
#define MEM_SIZE (16*REGISTER_SIZE)

void *global_mem;

void init()
{
    global_mem = malloc(MEM_SIZE);
    memset(global_mem, 0, MEM_SIZE);
}
typedef struct cmdEvent {
    char key[MAX_STDIN_SIZE];
    int value;
} cmdEvent_t;

enum eventType {READ, WRITE, THREADSTART, THREADSTOP};

struct cmdEvent events_t[NUMBER_OF_STDIN] = 
{ {"rd", READ},
  {"threadstart", THREADSTART},
  {"threadstop", THREADSTOP},
  {"wr", WRITE}
};


int eventcmp(char *k, struct cmdEvent* b)
{
    return strcmp(k, b->key);
}

int processEvent()
{
    char code[MAX_STDIN_SIZE];
    while(1)
    {
        scanf("%s", code);
        //printf("%s %d", code, value);
        int address = 0, value = 0, tid = 0;

        cmdEvent_t *item = (cmdEvent_t*) bsearch (code, events_t, 
            NUMBER_OF_STDIN, sizeof (struct cmdEvent), eventcmp);
        
        if( item != NULL ) {
            switch (item->value)
            {
                case READ:
                    //int address = 0;
                    scanf("%d", &address);
                    printf("Read mem at %d adress: %d\n", address, *((int*)global_mem + address));
                    
                    break;
                case WRITE:
                    //int address = 0, value = 0;
                    scanf("%d %d", &address, &value);
                    memcpy(global_mem+address*4, &value, sizeof(int));
                    printf("write %d down at %d address\n",value, address);
                    break;
                case THREADSTART:
                    //int tid = 0;
                    scanf("%d", &tid);
                    printf("Start thread %d\n", tid);
                    break;
                case THREADSTOP:
                    //int tid = 0;
                    printf("Stop thread %d\n", &tid);
                    break;
            }
        } else {
            printf("Item = %s could not be found\n", item);
        }
    }

    return 1;
}
int main() 
{
    init();
    processEvent();
    return 0; 
} 
