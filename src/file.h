#ifndef FILEH
#define FILEH

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Checks if a file exists.
 *
 * @param path The path to the file.
 * @return True if the file exists, false otherwise.
 */
bool file_exists(const char *path);

#endif /* ifndef FILEH */
