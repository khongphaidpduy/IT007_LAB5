#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sells = 0, products = 0;
sem_t sem;
const int MSSV_SUFFIX = 0362;
void *processA(void *arg) {
    while (1) {
        sem_wait(&sem);
        if (products > sells) {
            sells++;
            printf("Sold 1 product. Sells: %d, Products: %d\n", sells, products);
        }
        sem_post(&sem);
        usleep(500000); // Giả lập quá trình bán chậm hơn
    }
    return NULL;
}

void *processB(void *arg) {
    while (1) {
        sem_wait(&sem);
        if (products < sells + MSSV_SUFFIX) {
            products++;
            printf("Produced 1 product. Sells: %d, Products: %d\n", sells, products);
        }
        sem_post(&sem);
        usleep(300000); // Giả lập quá trình sản xuất nhanh hơn
    }
    return NULL;
}

int main() {
    pthread_t threadA, threadB;

    sem_init(&sem, 0, 1);

    pthread_create(&threadA, NULL, processA, NULL);
    pthread_create(&threadB, NULL, processB, NULL);

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);

    sem_destroy(&sem);
    return 0;
}
