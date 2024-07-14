#ifndef _DEQUE_H_
#define _DEQUE_H_

#define DEQUE_GROWTH 2

typedef struct Deque Deque;

Deque *deque_construct();

void deque_push_back(Deque *f, void *item);

void deque_push_front(Deque *f, void *item);

void *deque_pop_back(Deque *f);

void *deque_pop_front(Deque *f);

int deque_size(Deque *f);

void deque_destroy(Deque *f);

#endif