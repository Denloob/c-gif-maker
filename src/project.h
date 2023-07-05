#ifndef PROJECTH
#define PROJECTH

#include "linkedList.h"
#include "filters.h"
#include <stdio.h>

#define PROJECT_LOAD_READ_LINE_START_SIZE 16

typedef struct Project
{
    FrameNode *frames;
    FilterConfig *filter_config;
    unsigned long filter_index;
} Project;

/**
 * @brief Creates a new project.
 *
 * @return A pointer to the new project.
 */
Project *project_create();

/**
 * @brief Cleans up the project.
 *
 * @param project The project to clean up.
 */
void project_cleanup(Project *project);

/**
 * @brief Saves the given project to the given file.
 *
 * @param project The project to save.
 * @param file The file to save to.
 */
void project_save(Project *project, FILE *file);

/**
 * @brief Loads the given project from the given file.
 *
 * @param file The file to load from.
 * @param out The project to loaded from the file.
 */
void project_load(FILE *file, Project **out);

#endif /* ifndef PROJECTH */
