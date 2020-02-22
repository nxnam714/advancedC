#include "AtOsal.h"
#include "AtHalSim.h"



void *inc_count(void* threadid)
{
	int tid = (int) threadid;
	
	while(thread_flag[tid])
	{
        int count = *(int*)registerRead(COUNTER_ADDR);
        count++;
		registerWrite(COUNTER_ADDR, &count);
		printf("%d - count = %d\n", tid, count);
		sleep(1);
	}
	return 0;
}

void startThread(int tid)
{
    if (thread_flag[tid] == 0) {
        thread_flag[tid] = 1;
        pthread_create(&threads[tid], NULL, inc_count, (void*) tid);
    }
}

void stopThread(int tid)
{
    thread_flag[tid] = 0;
}

void joinThread(int tid)
{
    pthread_join(threads[tid], NULL);
}