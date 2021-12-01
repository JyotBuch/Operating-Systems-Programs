#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#define SIZE 3 //size of buffer
//indices to simulate queue behaviour
int in = 0;
int out = 0;
int buffer[SIZE] = {[0 ... SIZE - 1] = 0}; //0 represents an empty slot
int full = 0;
pthread_mutex_t mutex,buff;
void display_buffer();
void* producer(void* _args)
{
    int item;
    while(1)
    {
        sleep(rand() % 5);
        item = (rand() % 10) + 1;
        if(pthread_mutex_trylock(&mutex) == EBUSY) // Checks if it is locked
        {
            printf("\nProducer blocked on access to critical section.");
            pthread_mutex_lock(&mutex); // It locks the mutex and returns 0
        }
        printf("\nProducer entered CS.");
        if(full == SIZE)
        {
            printf("Buffer full.");
            printf("\nBuffer : ");
            display_buffer();
            printf("Producer exiting CS.\n");
        }
        else
        {
            buffer[in] = item;
            full++;
            printf("Produced : %d",buffer[in]);
            printf("\nBuffer : "); //included in critical section so buffer doesn't change before we display it
            display_buffer();
            in = (in + 1)%SIZE; // circular queue
            printf("Producer exiting CS.\n");
        }
        pthread_mutex_unlock(&mutex); //It unlocks the mutex and returns 0
    }
}
void* consumer(void* _args)
{
    int item;
    while(1)
    {
        sleep(rand() % 5);
        if(pthread_mutex_trylock(&mutex) == EBUSY)
        {
            printf("\nConsumer blocked on access to critical section. Value of FULL = %d MUTEX = %d\n", full, pthread_mutex_trylock(&mutex));
            pthread_mutex_lock(&mutex);
        }
        printf("\nConsumer entered CS.\n");
        if(full == 0)
        {
            printf("Buffer empty");
            printf("\nBuffer : ");
            display_buffer();
            printf("\nConsumer exiting CS.\n");
        }
        else
        {
            full--;
            item = buffer[out];
            buffer[out] = 0;
            printf("Consumed : %d",item);
            printf("\nBuffer : ");
            display_buffer();
            out = (out + 1)%SIZE;
            printf("Consumer exiting CS.\n");
        }
        pthread_mutex_unlock(&mutex);
    }
}
void display_buffer()
{
    for (int i = 0; i < SIZE; i++)
        printf("%d ",buffer[i]);
    printf("\n");
}
int main()
{
    srand(time(NULL));
    pthread_t producerThread,consumerThread;
    pthread_mutex_init(&mutex,NULL); //if successful, it returns a value 0, if any error it returns some other number
    //Upon successful initialisation, the state of the mutex becomes initialised and unlocked
    pthread_create(&producerThread,NULL,producer,NULL); //starts a new thread in the calling process
    pthread_create(&consumerThread,NULL,consumer,NULL);
    pthread_join(producerThread,NULL);
    pthread_join(consumerThread,NULL);
    pthread_mutex_destroy(&mutex); //destroys the mutex object referenced by mutex; the mutex object becomes, in effect, uninitialised
    return 0;
}