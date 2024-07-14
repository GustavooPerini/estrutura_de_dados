#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


struct Queue{

    int start;
    int end;
    int size;
    int allocated;
    void **data;
};

Queue *queue_constructor(int max_capacity){

    Queue *q = (Queue*)malloc(sizeof(Queue));

    q->start = 0;
    q->end = 0;
    q->size = 0;
    q->allocated = max_capacity;
    q->data = (void**)malloc(sizeof(void*) * q->allocated);

    return q;
}

void queue_add(Queue *queue, void *data){

    queue->data[queue->end] = data;
    queue->end = (queue->end + 1) % queue->allocated;
    queue->size++;
}

void* queue_remove(Queue *queue){

    void *data = queue->data[queue->start];
    queue->start = (queue->start + 1) % queue->allocated;
    queue->size--;
    return data;
}

int queue_size(Queue *queue){
    return queue->size;
}

int queue_is_full(Queue *queue){

    if(queue->size == queue->allocated){
        return 1;
    }
    return 0;
}

int queue_is_empty(Queue *queue){

    if(queue->size == 0){
        return 1;
    }
    return 0;
}

void queue_destroy(Queue *queue){

    free(queue->data);
    free(queue);
}