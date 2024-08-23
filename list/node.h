
#ifndef _NODE_H_
#define _NODE_H_

typedef int data_type;

typedef struct Node Node;

Node *node_construct(data_type value, Node *prev, Node *next);

Node *node_next(Node *n);

Node *node_prev(Node *n);

void set_node_next(Node *n, Node *next);

void set_node_prev(Node *n, Node *prev);

data_type node_val(Node *n);

data_type *node_val_address(Node *n);

void node_destroy(Node *n);

void node_print(Node *l, void (*print_fn)(data_type));

#endif