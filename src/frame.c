#include "frame.h"

Frame *frame_create(char *name, unsigned int duration, char *path)
{
    Frame *frame = (Frame *)malloc(sizeof(Frame));

    frame->name = name;
    frame->duration = duration;
    frame->path = path;

    return frame;
}

Frame *frame_create_stdin()
{
    Frame *frame = frame_create(NULL, 0, NULL);

    puts("Please insert frame path:");
    frame->path = input();

    puts("Please insert frame duration (in miliseconds):");
    scanf("%u", &frame->duration);
    flush_input();

    puts("Please choose a name for that frame:");
    frame->name = input();

    if (!file_exists(frame->path))
    {
        puts("Can\'t find file! Frame will not be added");
        frame_cleanup(frame);
        frame = NULL;
    }

    return frame;
}

void frame_cleanup(Frame *frame)
{
    free(frame->name);
    free(frame->path);

    free(frame);
}

void frame_change_duration_stdin(Frame *frame)
{
    puts("Enter the duration for the frame:");
    scanf("%u", &frame->duration);
    flush_input();
}

void frame_display(Frame *frame)
{
    char duration_buf[FRAME_DISPLAY_BUF_SIZE] = {0};
    int duration_justification =
        FRAME_DISPLAY_JUSTIFICATION +
        max_int((int)strlen(frame->name) + FRAME_DISPLAY_JUSTIFICATION, 0);
    snprintf(duration_buf, FRAME_DISPLAY_BUF_SIZE, "%u ms", frame->duration);
    printf("\t\t%*s %*s %s\n", FRAME_DISPLAY_JUSTIFICATION, frame->name,
           duration_justification, duration_buf, frame->path);
}
