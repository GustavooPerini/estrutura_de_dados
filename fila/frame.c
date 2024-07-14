#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frame.h"

struct Frame
{
    char video_id[50];
    int frame_id;
    float timestamp;
};

Frame *frame_constructor(char *video_id, int frame_id, float timestamp)
{
    Frame *frame = (Frame *)malloc(sizeof(Frame));

    if (!frame)
        return NULL;

    strcpy(frame->video_id, video_id);
    frame->frame_id = frame_id;
    frame->timestamp = timestamp;

    return frame;
}

char *frame_get_video_id(Frame *frame)
{
    return frame->video_id;
}

int frame_get_frame_id(Frame *frame)
{
    return frame->frame_id;
}

float frame_get_timestamp(Frame *frame)
{
    return frame->timestamp;
}

void frame_destroy(Frame *frame)
{
    if (frame)
        free(frame);
}
