#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H


typedef void* data_type;
typedef struct ForwardList ForwardList;


ForwardList *forward_list_construct();

int forward_list_size(ForwardList *fl);

void forward_list_push_front(ForwardList *fl, data_type data);

void forward_list_push_back(ForwardList *fl, data_type data);

data_type forward_list_pop_front(ForwardList *fl);

void forward_list_destroy(ForwardList *fl);

#endif