#ifndef _ARRAY_H_
#define _ARRAY_H_

typedef void* data_type;

typedef struct carray C_array;

C_array *array_construct();

void array_destroy(C_array *c);

void array_push_back(C_array *c, data_type val);

int array_size(C_array *c);

data_type array_get(C_array *c, int i);

data_type array_pop_front(C_array *c);

data_type array_pop_back(C_array *c);


#endif