#include <stdio.h>
#include <string.h>
#include "hash.h"


int hash_str(HashTable *h, void *data){

    char *str = (char*)data;
    unsigned long int hash_val = 0, base = 127;
    unsigned long int random_val = 31415;
    int size = strlen(str);

    for(int i = 0; i < size; i++){
        hash_val = (hash_val * base + str[i]) % hash_table_size(h);
        random_val = (random_val * base) % (hash_table_size(h) - 1);
    }

    return hash_val;
}


int cmp_str(void *a, void *b){
    
    return strcmp((char *)a, (char *)b);
}


int main(){

    return 0;
}