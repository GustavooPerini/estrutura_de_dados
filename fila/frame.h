#ifndef _FRAME_H_
#define _FRAME_H_

typedef struct Frame Frame;

// Função para criar um frame
Frame *frame_constructor(char *video_id, int frame_id, float timestamp);

// Funções para acessar os campos do frame
char *frame_get_video_id(Frame *frame);
int frame_get_frame_id(Frame *frame);
float frame_get_timestamp(Frame *frame);

// Função para destruir um frame
void frame_destroy(Frame *frame);

#endif
