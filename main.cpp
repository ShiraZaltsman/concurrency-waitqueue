#include <iostream>

#include "mythread.h"

int main() {
    pthread_t threadsPro[NUM_THREADS_PRO];
    pthread_t threadsCon[NUM_THREADS_CON];
    sem_init(&semCreate, 0, SEM_OF_CREATE);
    sem_init(&semBuy, 6, SEM_OF_BUY);
    srand(time(0));
    size_t i;
    for (i = 0; i < NUM_THREADS_PRO; i++) {
        if (pthread_create(&threadsPro[i], NULL,
                           (void *(*)(void *)) producers, (void *) (i))) {

            printf("Error:unable to create thread,");
            exit(-1);
        }
    }
    for (i = 0; i < NUM_THREADS_CON; i++) {
        if (pthread_create(&threadsCon[i], NULL,
                           (void *(*)(void *)) consumers, (void *) (i))) {

            printf("Error:unable to create thread,");
            exit(-1);
        }
    }
    for (i = 0; i < NUM_THREADS_PRO; i++) {
        pthread_join(threadsPro[i], NULL);
    }
    for (i = 0; i < NUM_THREADS_CON; i++) {
        pthread_join(threadsCon[i], NULL);
    }
    sem_destroy(&semCreate);
    sem_destroy(&semBuy);
    pthread_exit(NULL);

}