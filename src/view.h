#ifndef VIEWH
#define VIEWH

#ifndef CV_IGNORE_DEBUG_BUILD_GUARD
#define CV_IGNORE_DEBUG_BUILD_GUARD
#endif /* ifndef CV_IGNORE_DEBUG_BUILD_GUARD */

#include "project.h"
#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>

#define CV_WAIT_KEY_NO_KEY_PRESSED -1

/**
 * @brief Display the each images for the duration of the frame one by one with
 * the project filter applied GIF_REPEAT times.
 *
 * @param project The project to play.
 */
void view_play(const Project *project);

#endif
