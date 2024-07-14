
#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct Queue Queue;

// Create an queue
Queue *queue_constructor(int max_capacity);

// Add an element
void queue_add(Queue *queue, void *data);

// Remove the oldest element in the queue
void* queue_remove(Queue *queue);

// Return the number of elements in the queue
int queue_size(Queue *queue);

// Return 1 if the queue is full and 0, otherwise
int queue_is_full(Queue *queue);

// Return 1 if the queue is empty and 0, otherwise
int queue_is_empty(Queue *queue);

// Free the data structure.
// IMPORTANT: the user of the lib is responsible for removing and freeing elements
// remaining in the queue. In the queue is not empty when the functions is called,
// the function will not release them.
void queue_destroy(Queue *queue);

#endif