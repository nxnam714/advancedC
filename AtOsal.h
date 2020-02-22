#include <pthread.h>
#include <stdio.h>

#define MAX_THREAD 2
#define COUNTER_ADDR 0

pthread_mutex_t count_mutex;
int thread_flag[MAX_THREAD];
pthread_t threads[MAX_THREAD];

void *inc_count(void* threadid);
void joinThread(int tid);
void stopThread(int tid);
void startThread(int tid);