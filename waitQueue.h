//
// Created by shira on 12/16/19.
//

#ifndef CONCURRENCY_WAITQUEUE_SHIRAZALTSMAN_WAITQUEUE_H
#define CONCURRENCY_WAITQUEUE_SHIRAZALTSMAN_WAITQUEUE_H
#include <stdio.h>

#define SIZE 6
int size = 0;
int front = 0;
int rear = SIZE - 1;
unsigned capacity = SIZE;

int isFull() { return (size == capacity); }

int isEmpty() { return (size == 0); }

void enQueue(int queue[], int ele) {
    if (isFull()) {
        //wait here
        printf("Queue Overflow \n");
        return;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = ele;
    size = size + 1;
}

int deQueue(int queue[]) {
    int ele;
    if (isEmpty()) {
        //wait here
        printf("Queue Overflow \n");
        return -1;
    }
    ele = queue[front];
    front = (front + 1) % capacity;
    size = size - 1;
    return ele;
}

#endif //CONCURRENCY_WAITQUEUE_SHIRAZALTSMAN_WAITQUEUE_H
