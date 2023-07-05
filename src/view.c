#include "view.h"

void view_play(const Project *project)
{
    FilterFunction filter = filter_functions[project->filter_index];
    const FrameNode *const head = project->frames;
    const FrameNode *list = head;
    cvNamedWindow("Display window", CV_WINDOW_AUTOSIZE); //create a window
    // First const makes the FrameNode immutable, while the second makes the
    // variable `head` immutable.
    IplImage *raw_image = NULL;
    IplImage *filtered_image = NULL;
    bool stop_playing = 0;

    stop_playing =
        head == NULL; // Make sure that there is something to display :)
                      // With early returns it would be much, much clearer.

    while (!stop_playing)
    {
        while (list && !stop_playing)
        {
            raw_image = cvLoadImage(list->frame->path, 1);
            if (raw_image)
            {
                filtered_image = filter(raw_image, project->filter_config);
                cvShowImage("Display window", filtered_image);
                stop_playing = cvWaitKey(list->frame->duration) !=
                               CV_WAIT_KEY_NO_KEY_PRESSED;

                cvReleaseImage(&raw_image);
                cvReleaseImage(&filtered_image);
            }
            else
            {
                printf("Could not open or find image located at %s\n",
                       list->frame->path);
            }
            // It's important to skip the frame on error, and not just keep trying to open it.
            list = list->next;
        }
        list = head; // rewind
    }
    cvDestroyWindow("Display window");
}
