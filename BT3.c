#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int x = 0;

void* processA(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("%d\n", x);
    }
    return NULL;
}

void* processB(void* arg) {
    while (1) {
        x = x + 1;
        if (x == 20)
            x = 0;
        printf("%d\n", x);
    }
    return NULL;
}

int main() {
    pthread_t thread_A, thread_B ;

    srand(time(NULL));

    pthread_create(&thread_A, NULL, processA, NULL);
    pthread_create(&thread_B, NULL, processB, NULL);
    
    sleep(10);
    return 0;
}