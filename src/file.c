#include "file.h"

bool file_exists(const char *path)
{
    FILE *stream = fopen(path, "rb");

    if (stream)
    {
        fclose(stream);
    }

    return stream != NULL;
}
