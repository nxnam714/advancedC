#include <stdio.h>
#include "AtHalSim.h"
#include "AtOsal.h"

extern void *global_mem;

int processEvent()
{
    char code[MAX_STDIN_SIZE];
    while(1)
    {
        scanf("%s", code);
        //printf("%s %d", code, value);
        int address = 0, value = 0, tid = 0;

        int cmType = getcmdtype(code);
        
        switch (cmType)
        {
            case READ:
                //int address = 0;
                scanf("%d", &address);
                printf("Read mem at %d adress: %d\n", address, *(int*)registerRead(address));
                
                break;
            case WRITE:
                //int address = 0, value = 0;
                scanf("%d %d", &address, &value);
                registerWrite(address, &value);
                printf("write %d down at %d address\n",value, address);
                break;
            case THREADSTART:
                //int tid = 0;
                scanf("%d", &tid);
                //printf("Start thread %d\n", tid);
                startThread(tid);
                break;
            case THREADSTOP:
                //int tid = 0;
                scanf("%d", &tid);
                //printf("Stop thread %d\n", tid);
                stopThread(tid);
                joinThread(tid);
                break;
        }
    }

    return 1;
}

int main()
{
    memInit();
    processEvent();
    return 0;
}