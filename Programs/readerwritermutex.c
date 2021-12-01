#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
pthread_mutex_t clock_mutex,rc_mutex;
int rc = 0;
int hours,minutes,seconds;
void* writer(void* _args)
{
    while(1)
    {
        sleep(1);
        if (pthread_mutex_trylock(&clock_mutex) == EBUSY)
        {
            printf("\nWriter blocked on access to critical section");
            pthread_mutex_lock(&clock_mutex);
        }
        printf("\nWriter in critical section\n");
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
        printf("Writer exiting critical section\n");
        pthread_mutex_unlock(&clock_mutex);
    }
}
void* reader(void* args)
{
    int readerNumber = ((int)args);
    while(1)
    {
        sleep(rand() % 3);
        pthread_mutex_lock(&rc_mutex);
        rc++;
        if (rc == 1)
        {
            pthread_mutex_lock(&clock_mutex);
            printf("\nFirst reader entered critical section.\n");
        }
        pthread_mutex_unlock(&rc_mutex);
        printf("\nReader %d in critical section.",readerNumber);
        printf("\nTime read by reader %d - %02d:%02d:%02d.\n",readerNumber,hours,minutes,seconds);
        pthread_mutex_lock(&rc_mutex);
        rc--;
        if (rc == 0)
        {
            printf("\nFinal reader leaving critical section.\n");
            pthread_mutex_unlock(&clock_mutex);
        }
        pthread_mutex_unlock(&rc_mutex);
    }
}
int main()
{
    srand(time(NULL));
    pthread_t readerThread1,readerThread2,readerThread3,writerThread;
    int readerId[3] = {1,2,3};
    pthread_mutex_init(&clock_mutex,NULL);
    pthread_mutex_init(&rc_mutex,NULL);
    hours = 00;
    minutes = 00;
    seconds = 00;
    pthread_create(&writerThread,NULL,writer,NULL);
    pthread_create(&readerThread1,NULL,reader,(void*)&readerId[0]);
    pthread_create(&readerThread2,NULL,reader,(void*)&readerId[1]);
    pthread_create(&readerThread3,NULL,reader,(void*)&readerId[2]);
    pthread_join(writerThread,NULL);
    pthread_join(readerThread1,NULL);
    pthread_join(readerThread2,NULL);
    pthread_join(readerThread3,NULL);
    pthread_mutex_destroy(&clock_mutex);
    pthread_mutex_destroy(&rc_mutex);
    return 0;
}