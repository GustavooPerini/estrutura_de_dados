#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"


struct product{

    char name[MAX_NAME_LENGTH + 1];
    float price;
    float discount;
    int qtd;
    int sales;
};


Product *product_constructor(const char *name, float price, int qtd){

    Product *p = (Product*)malloc(sizeof(Product));

    strcpy(p->name, name);
    p->price = price;
    p->discount = 0;
    p->qtd = qtd;
    p->sales = 0;

    return p;
}


void product_print(void *data){

    if(data != NULL){
        Product *product = (Product*)data;
        printf("Product(%s, %.2f, %d)\n", product->name, product->price, product->qtd);
    }
}

int compare_product_by_name(const void *data1, const void *data2){

    /*Product *p1 = *((Product**)data1);
    Product *p2 = *((Product**)data2);*/

    Product *p1 = (Product*)data1;
    Product *p2 = (Product*)data2;

    return strcmp(p1->name, p2->name);
}


void product_destructor(void *data){
    
    if(data != NULL){
        Product *p = (Product*)data;
        free(p);
    }
}