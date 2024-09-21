#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H


typedef void* data_type;
typedef struct ForwardList ForwardList;
typedef struct ForwardListIterator ForwardListIterator;


//Forwar List headers
ForwardList *forward_list_construct();

int forward_list_size(ForwardList *l);

void forward_list_push_front(ForwardList *l, data_type data);

data_type forward_list_get(ForwardList *l, int idx);

data_type forward_list_pop_front(ForwardList *l);

void forward_list_destroy(ForwardList *l);

ForwardListIterator *forward_list_iterator_construct(ForwardList *l);

//Iterator headers
data_type forward_list_iterator_next(ForwardListIterator *it);

int forward_list_iterator_is_over(ForwardListIterator *it);

void forward_list_destroy_itens(ForwardList *l);

void forward_list_iterator_destroy(ForwardListIterator *it);

#endif