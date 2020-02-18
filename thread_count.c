#include <pthread.h>
#include <stdio.h>

#define MAX_THREAD 2

static int count = 0;
pthread_mutex_t count_mutex;

void *inc_count(void* threadid)
{
	while(1)
	{
		pthread_mutex_lock(&count_mutex);
		count++;
		int tid = (int) threadid;
		printf("%d - count = %d\n", tid, count);
		pthread_mutex_unlock(&count_mutex);
		sleep(1);
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int i;
	pthread_t threads[MAX_THREAD];

	pthread_mutex_init(&count_mutex, NULL);

	for (i = 0; i < MAX_THREAD; i++)
		pthread_create(&threads[i], NULL, inc_count, (void*) i);

	for (i = 0; i < MAX_THREAD; i++)
		pthread_join(threads[i], NULL);

	pthread_mutex_destroy(&count_mutex);

	return 0;
}
