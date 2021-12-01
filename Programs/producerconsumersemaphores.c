#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define SIZE 2 //size of buffer
//indices to simulate queue behaviour

int in = 0;
int out = 0;
int buffer[SIZE] = {[0 ... SIZE - 1] = 0}; //0 represents an empty slot
//required semaphores
sem_t empty;
sem_t full;
sem_t mutex;
void display_buffer();

void* producer(void* _args)
{
    int item;
    while(1)
    {
        sleep(rand() % (1 + (rand() % 5)));
        item = 1 + (rand() % 10);
        if (sem_trywait(&empty) == -1)
        {
            printf("\nProducer blocked as there as no empty slots\n");
            sem_wait(&empty);
        }
        if (sem_trywait(&mutex) == -1)
        {
            printf("\nProducer blocked for access to critical section");
            sem_wait(&mutex);
        }
        printf("\nProducer entered CS.\n");
        buffer[in] = item;
        printf("Produced : %d",buffer[in]);
        printf("\nBuffer : "); //included in critical section so buffer doesn't change before we display it
        display_buffer();
        printf("Producer exiting CS.\n");
        sem_post(&mutex);
        sem_post(&full); //signal that an item has been produced
        in = (in + 1)%SIZE; // circular queue
    }
}
void* consumer(void* _args)
{
    int item;
    while(1)
    {
        sleep(rand() % (1 + (rand() % 5)));
        if (sem_trywait(&full) == -1)
        {
            printf("\nConsumer blocked as there as no full slots\n");
            sem_wait(&full);
        }
        if (sem_trywait(&mutex) == -1)
        {
            printf("\nConsumer blocked for access to critical section");
            sem_wait(&mutex);
        }
        printf("\nConsumer entered CS.\n");
        item = buffer[out];
        buffer[out] = 0;
        printf("Consumed : %d",item);
        printf("\nBuffer : ");
        display_buffer();
        printf("Consumer exiting CS.\n");
        sem_post(&mutex);
        sem_post(&empty); //signal that an item has been consumed
        out = (out + 1)%SIZE;
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
    sem_init(&mutex,0,1);
    sem_init(&empty,0,SIZE);
    sem_init(&full,0,0);
    pthread_create(&producerThread,NULL,producer,NULL);
    pthread_create(&consumerThread,NULL,consumer,NULL);
    pthread_join(producerThread,NULL);
    pthread_join(consumerThread,NULL);
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}