#include "AtHalSim.h"

void memInit()
{
    global_mem = malloc(MEM_SIZE);
    memset(global_mem, 0, MEM_SIZE);
}
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

int getcmdtype(char* code)
{
    int ret = -1;
    cmdEvent_t *item = (cmdEvent_t*) bsearch (code, events_t, 
            NUMBER_OF_STDIN, sizeof (struct cmdEvent), eventcmp);
    if( item != NULL ) {
        ret = item->value;
    } else {
        printf("Item = %s could not be found\n", item);
        
    }
    return ret;
}
void *registerRead(int addr){
    return (global_mem + addr*REGISTER_SIZE);
}

void registerWrite(int addr, void *value)
{
    switch (addr)
    {
    case 0:
        pthread_mutex_lock(&count_mutex);
        memcpy(global_mem+addr*4, value, REGISTER_SIZE);
        pthread_mutex_unlock(&count_mutex);
        break;
    
    default:
        memcpy(global_mem+addr*4, value, REGISTER_SIZE);
        break;
    }
}