#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <semaphore.h>
sem_t rc_mutex,army_clock;
int rc = 0;
int hours,minutes,seconds;
void* writer(void* _args)
{
	while(1)
	{
		sleep(1);
		if (sem_trywait(&army_clock) == EAGAIN)
		{
			printf("\nWriter blocked on access to critical section");
			sem_wait(&army_clock);
		}
		printf("\nWriter in critical section.\n");
		seconds++;
		if (seconds == 60)
		{
			seconds = 0;
			minutes++;
			if (minutes == 60)
			{
				minutes = 0;
				hours++;
				if (hours == 24)
				{
					hours = 0;
				}
			}
		}
		printf("Writer exiting critical section.\n");
		sem_post(&army_clock);
	}
}
void* reader(void* args)
{
	int readerNumber = ((int)args);
	while(1)
	{
		sleep(rand() % 3);
		sem_wait(&rc_mutex);
		rc++;
		if (rc == 1)
		{
			if (sem_trywait(&army_clock) == EAGAIN)
			{
				printf("\nReader %d blocked for access to reader count.",readerNumber);
				sem_wait(&army_clock);
			}
			printf("\nFirst reader entered critical section.\n");
		}
		sem_post(&rc_mutex);
		//printf("\nReader %d in critical section.",readerNumber);
		printf("\nTime read by reader %d - %02d:%02d:%02d.\n",readerNumber,hours,minutes,seconds);
		sem_wait(&rc_mutex);
		rc--;
		if (rc == 0)
		{
			printf("\nFinal reader leaving critical section.\n");
			sem_post(&army_clock);
		}
		sem_post(&rc_mutex);
	}
}
int main()
{
	srand(time(NULL));
	pthread_t readerThread1,readerThread2,readerThread3,writerThread;
	int readerId[3] = {1,2,3};
	sem_init(&rc_mutex,0,1);
	sem_init(&army_clock,0,1);
	hours = 23;
	minutes = 59;
	seconds = 55;
	pthread_create(&readerThread1,NULL,reader,(void*)&readerId[0]);
	pthread_create(&readerThread2,NULL,reader,(void*)&readerId[1]);
	pthread_create(&readerThread3,NULL,reader,(void*)&readerId[2]);
	pthread_create(&writerThread,NULL,writer,NULL);
	pthread_join(writerThread,NULL);
	pthread_join(readerThread1,NULL);
	pthread_join(readerThread2,NULL);
	pthread_join(readerThread3,NULL);
	sem_destroy(&rc_mutex);
	sem_destroy(&army_clock);
	return 0;
}