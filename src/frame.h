#ifndef FRAMEH
#define FRAMEH

#include "file.h"
#include "input.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FRAME_DISPLAY_BUF_SIZE 20

#define FRAME_DISPLAY_JUSTIFICATION -15

typedef struct Frame
{
    char *name;
    char *path;
    unsigned int duration;
} Frame;

typedef void (*FrameMethod)(Frame *);

/**
 * @brief Creates a new frame. Makes sure that frame->path file exists.
 *
 * @param name The name of the frame.
 * @param duration The duration of the frame.
 * @param path The path to the frame's image.
 * @return A pointer to the new frame.
 */
Frame *frame_create(char *name, unsigned int duration, char *path);

/**
 * @brief Creates a new frame using data from stdin.
 *
 * @return A pointer to the new frame.
 */
Frame *frame_create_stdin();

/**
 * @brief Cleans up the frame.
 *
 * @param frame The frame to clean up.
 */
void frame_cleanup(Frame *frame);

/**
 * @brief Changes the duration of the given frame to duration specified on stdin.
 *
 * @param frame The frame to change the duration of.
 */
void frame_change_duration_stdin(Frame *frame);

/**
 * @brief Displays the frame.
 *
 * @param frame The frame to display.
 */
void frame_display(Frame *frame);

#endif /* ifndef FRAMEH */
