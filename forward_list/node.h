#ifndef _NODE_H_
#define _NODE_H_


typedef int data_type;

typedef struct node Node;

Node *node_construct(data_type val, Node *node);

data_type node_val(Node *node);

Node *node_next(Node *node);

void set_node_next(Node *node, Node *destiny);

void node_destroy(Node *node);

#endif