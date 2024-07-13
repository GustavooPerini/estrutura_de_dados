#include <stdio.h>
#include "vector.h"
#include "product.h"

int main(){

    int n, escolha = 0;
    int qtd;
    char nome[MAX_NAME_LENGTH + 1];
    float preco;

    Vector *produtos = vector_construct(product_destructor);

    printf("Digite a quantidade de produtos a serem cadastrados: ");
    scanf("%d%*c", &n);

    for(int i = 0; i < n; i++){

        printf("Digite o nome do produto: ");
        scanf("%[^\n]%*c", nome);

        printf("Digite o preco do produto: ");
        scanf("%f%*c", &preco);

        printf("Digite a quantidade do produto: ");
        scanf("%d%*c", &qtd);

        vector_push_back(produtos, product_constructor(nome, preco, qtd));
        printf("Produto cadastrado com sucesso\n");
    }

    while (escolha != 8){
        printf("1 - Vector get\n");
        printf("2 - Vector remove\n");
        printf("3 - Vector find\n");
        printf("4 - Vector insert\n");
        printf("5 - Vector swap\n");
        printf("6 - Vector sort\n");
        printf("7 - Listar produtos\n");
        printf("8 - Sair\n");
        printf("Sua escolha: ");
        scanf("%d%*c", &escolha);

        if(escolha == 1){
            int k;
            printf("Digite o indice: ");
            scanf("%d%*c", &k);
            product_print(vector_get(produtos, k));
        }
        else if(escolha == 2){
            int k;
            printf("Digite o indice para remover: ");
            scanf("%d%*c", &k);
            vector_remove(produtos, k);
        }
        else if(escolha == 3){
            Product *p = product_constructor("manga", 10.5, 20);
            int index = vector_find(produtos, p, compare_product_by_name);

            //a lista de itens precisa estar ordernada
            //int index = vector_binary_search(produtos, p, compare_product_by_name);

            product_destructor(p);

            if(index >= 0){
                printf("O produto se encontra no indice %d\n", index);
            }
            else{
                printf("Produto não encontrado\n");
            }

        }
        else if(escolha == 4){
            Product *p = product_constructor("manga", 10.5, 20);
            vector_insert(produtos, 1, p);
        }
        else if(escolha == 5){
            vector_swap(produtos, 1, 4);
        }
        else if(escolha == 6){
            vector_sort(produtos, compare_product_by_name);
        }
        else if(escolha == 7){
            for(int i = 0; i < vector_size(produtos); i++){
                product_print(vector_get(produtos, i));
            }
        }

    }
    
    vector_destroy(produtos);
}