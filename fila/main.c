#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "atendimento.h"
#include "frame.h"

#define FRAME_CAPACITY 20
#define ATENDIMENTO_CAPACITY 10

int main(){

    char comando[15], acao[15];
    int n;

    scanf("%s", comando);
    scanf("%d", &n);

    if(!strcmp(comando, "STREAMING")){

        Queue *queue = queue_constructor(FRAME_CAPACITY);

        char video_id[50];
        int frame_id;
        float timeStamp;

        for(int i = 0; i < n; i++){
            
            scanf("%s", acao);

            if(!strcmp(acao, "ADICIONAR")){
                
                scanf("%s %d %f", video_id, &frame_id, &timeStamp);

                if(queue_is_full(queue)){
                    printf("FILA CHEIA\n");
                    continue;
                }

                queue_add(queue, frame_constructor(video_id, frame_id, timeStamp));

            }
            else if(!strcmp(acao, "PLAY")){

                if(queue_is_empty(queue)){
                    printf("FILA VAZIA\n");
                    continue;
                }
                else if(queue_size(queue) < 5){
                    printf("AGUARDE\n");
                    continue;
                }

                for(int i = 0; i < 5; i++){
                    
                    Frame *f = (Frame*)queue_remove(queue);
                    printf("ID: %d, Timestamp: %.2f\n", frame_get_frame_id(f), frame_get_timestamp(f));
                    frame_destroy(f);
                }

            }

        }

        int j = queue_size(queue);
        if(j > 0){
            
            for(int i = 0; i < j; i++){
                Frame *f = (Frame*)queue_remove(queue);
                frame_destroy(f);
            }
        }

        queue_destroy(queue);
    }
    else if(!strcmp(comando, "SENHAS")){
        
        Queue *queue = queue_constructor(ATENDIMENTO_CAPACITY);

        char nome[50];
        char cpf[12];

        for(int i = 0; i < n; i++){
            
            scanf("%s", acao);

            if(!strcmp(acao, "ADICIONAR")){

                scanf("%s %s", nome, cpf);

                if(queue_is_full(queue)){
                    printf("FILA CHEIA\n");
                    continue;
                }

                queue_add(queue, atendimento_constructor(nome, cpf));

            }
            else if(!strcmp(acao, "CHAMAR")){

                if(queue_is_empty(queue)){
                    printf("FILA VAZIA\n");
                    continue;
                }

                Atendimento *a = (Atendimento*)queue_remove(queue);
                printf("%s\n", atendimento_get_nome(a));
                atendimento_destroy(a);
            }

        }

        int j = queue_size(queue);
        if(j > 0){
            
            for(int i = 0; i < j; i++){
                Atendimento *a = (Atendimento*)queue_remove(queue);
                atendimento_destroy(a);
            }
        }

        queue_destroy(queue);

    }

    return 0;
}