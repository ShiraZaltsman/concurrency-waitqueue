//
// Created by shira on 12/16/19.
//

#ifndef CONCURRENCY_WAITQUEUE_SHIRAZALTSMAN_MYTHREAD_H
#define CONCURRENCY_WAITQUEUE_SHIRAZALTSMAN_MYTHREAD_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/queue.h>
#include <time.h>
#include <stdlib.h>
#include "waitQueue.h"

sem_t semCreate;
sem_t semBuy;
size_t NUM_THREADS_PRO = 3;
size_t NUM_THREADS_CON = 4;
const int SEM_OF_CREATE = 6;
const int SEM_OF_BUY = 0;
int q[SIZE];
const char prod = 40;
const char cons = 30;

void *producers(void *threadid) {
    int pro[prod], val;
    size_t i;
    long tid;
    tid = (long) threadid;
    char sumProduct = prod;
    while (sumProduct) {
        sem_wait(&semCreate);
        --sumProduct;
        val = rand() % 1000000;
        enQueue(q, val);
        /*/printf("producer/Thread ID: %li , count= %d num= %d\n", tid, sumProduct, val);*/
        pro[sumProduct] = val;
        sem_post(&semBuy);
    }
    printf("pro %d:\n", tid);
    for (i = 0; i < prod; ++i) {
        printf("%d ", pro[i]);

    }
    printf("\n");
    return (void *) (threadid + 1);
}

void *consumers(void *threadid) {
    int con[cons];
    size_t i;
    long tid;
    tid = (long) threadid;
    char sumConsumers = cons;
    while (sumConsumers) {
        sem_wait(&semBuy);
        --sumConsumers;
        con[sumConsumers] = deQueue(q);
        /*/printf("Consumers/Thread ID: %li , count= %d num= %d\n", tid, sumConsumers, con[sumConsumers]);*/
        sem_post(&semCreate);
    }
    printf("Consumers %d:\n", tid);
    for (i = 0; i < cons; ++i) {
        printf("%d ", con[i]);

    }
    printf("\n");
    return (void *) (threadid + 1);
}

#endif //CONCURRENCY_WAITQUEUE_SHIRAZALTSMAN_MYTHREAD_H
