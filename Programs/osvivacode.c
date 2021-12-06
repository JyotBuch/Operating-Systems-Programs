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
    int producerNumber = *(int*)_args;
    while(1)
    {
        sleep(rand() % 5);
        item = (rand() % 10) + 1;
        if(pthread_mutex_trylock(&mutex) == EBUSY) // Checks if it is locked
        {
            printf("\nProducer %d blocked on access to critical section." ,producerNumber);
            pthread_mutex_lock(&mutex); // It locks the mutex and returns 0
        }
        printf("\nProducer %d entered CS." ,producerNumber);
        if(full == SIZE)
        {
            printf("Buffer full.");
            printf("\nBuffer : \n");
            display_buffer();
            printf("\n");
            printf("Producer %d exiting CS.\n", producerNumber);
        }
        else
        {
            buffer[in] = item;
            full++;
            printf("Produced : %d",buffer[in]);
            printf("\nBuffer : "); //included in critical section so buffer doesn't change before we display it
            display_buffer();
            in = (in + 1)%SIZE; // circular queue
            printf("Producer %d exiting CS.\n" ,producerNumber);
        }
        pthread_mutex_unlock(&mutex); //It unlocks the mutex and returns 0
    }
}
void* consumer(void* _args)
{
    int item;
    int consumerNumber = *(int*)_args;
    while(1)
    {
        sleep(rand() % 5);
        if(pthread_mutex_trylock(&mutex) == EBUSY)
        {
            printf("\nConsumer %d blocked on access to critical section.\n", consumerNumber);
            pthread_mutex_lock(&mutex);
        }
        printf("\nConsumer %d entered CS.\n" ,consumerNumber);
        if(full == 0)
        {
            printf("Buffer empty");
            printf("\nBuffer : ");
            display_buffer();
            printf("\n");
            printf("\nConsumer %d exiting CS.\n" ,consumerNumber);
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
            printf("\nConsumer %d exiting CS.\n" ,consumerNumber);
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
    pthread_t producerThread1, producerThread2, consumerThread1, consumerThread2;
    int producerId[2] = {1,2};
    int consumerId[2] = {1,2};

    pthread_mutex_init(&mutex,NULL);

    pthread_create(&producerThread1, NULL, producer, (void*)&producerId[0]);
    pthread_create(&producerThread2, NULL, producer, (void*)&producerId[1]);
    pthread_create(&consumerThread1, NULL, consumer, (void*)&consumerId[0]);
    pthread_create(&consumerThread2, NULL, consumer, (void*)&consumerId[1]);

    pthread_join(producerThread1,NULL);
    pthread_join(producerThread2,NULL);
    pthread_join(consumerThread1,NULL);
    pthread_join(consumerThread2,NULL);

    pthread_mutex_destroy(&mutex);
}