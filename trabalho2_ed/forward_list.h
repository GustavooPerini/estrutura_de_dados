#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

typedef void* data_type;

typedef struct Node Node;

typedef struct ForwardList ForwardList;

typedef struct ForwardListIterator ForwardListIterator;


ForwardList *forward_list_contruct();

void forward_list_push_front(ForwardList *l, data_type value);

int forward_list_size(ForwardList *l);

data_type forward_list_get(ForwardList *l, int idx);

data_type forward_list_pop_index(ForwardList *l, int index);

void forward_list_destroy(ForwardList *l);

ForwardListIterator *forward_list_iterator_construct(ForwardList *l);

data_type forward_list_iterator_next(ForwardListIterator *it);

int forward_list_iterator_is_over(ForwardListIterator *it);

void forward_list_iterator_destroy(ForwardListIterator *it);

#endif