#include <stdio.h>
#include <string.h>
#include "deque.h"
#include "product.h"

int main(){

    int escolha = 10;
    int qtd;
    char nome[MAX_NAME_LENGTH + 1];
    float preco;

    Deque *produtos = deque_construct();

    while (escolha != 0){
        printf("1 - Deque push front\n");
        printf("2 - Deque push back\n");
        printf("3 - Deque pop front\n");
        printf("4 - Deque pop back\n");
        printf("0 - Sair\n");
        printf("Sua escolha: ");
        scanf("%d%*c", &escolha);

        if(escolha == 1){
            printf("Digite o nome do produto: ");
            scanf("%[^\n]%*c", nome);

            printf("Digite o preco do produto: ");
            scanf("%f%*c", &preco);

            printf("Digite a quantidade do produto: ");
            scanf("%d%*c", &qtd);

            deque_push_front(produtos, product_constructor(nome, preco, qtd));
        }
        else if(escolha == 2){
            printf("Digite o nome do produto: ");
            scanf("%[^\n]%*c", nome);

            printf("Digite o preco do produto: ");
            scanf("%f%*c", &preco);

            printf("Digite a quantidade do produto: ");
            scanf("%d%*c", &qtd);

            deque_push_back(produtos, product_constructor(nome, preco, qtd));
        }
        else if(escolha == 3){
            void *data = deque_pop_front(produtos);
            product_print(data);
            product_destructor(data);
        }
        else if(escolha == 4){
            void *data = deque_pop_back(produtos);
            product_print(data);
            product_destructor(data);
        }
    }

    deque_destroy(produtos);
}