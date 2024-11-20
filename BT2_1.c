#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int a[100];
int n = 0;
sem_t sem_produce;
sem_t sem_consume;

void* producer(void* arg) {
    while (1) {
        int num = rand() % 100;
        //sem_wait(&sem_produce);
        a[n++] = num;
        printf("[PRODUCER] Added %d, Array size: %d\n", num, n);
        //sem_post(&sem_consume);
        usleep(500000); // Giả lập quá trình bán chậm hơn
    }
    return NULL;
}

void* consumer(void* arg) {
    while (1) {
        //sem_wait(&sem_consume);
        if (n > 0) {
            int removed = a[--n];
            printf("[CONSUMER] Removed %d, Array size: %d\n", removed, n);
        }
        else {
            printf("[CONSUMER] Nothing in array a\n");
        }
        //sem_post(&sem_produce);
        usleep(300000); // Giả lập quá trình bán chậm hơn
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    srand(time(NULL)); 

    sem_init(&sem_produce, 0, 100);
    sem_init(&sem_consume, 0, 0);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&sem_produce);
    sem_destroy(&sem_consume);

    return 0;
}