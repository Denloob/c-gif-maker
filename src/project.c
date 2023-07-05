#include "project.h"

Project *project_create()
{
    Project *project = (Project *)malloc(sizeof(Project));

    project->frames = NULL;
    // We use calloc to initialize the filter_config to 0.
    project->filter_config = (FilterConfig *)calloc(1, sizeof(FilterConfig));
    project->filter_index = 0;

    return project;
}

void project_cleanup(Project *project)
{
    frame_list_cleanup(project->frames);
    free(project->filter_config);
    free(project);
}

void project_save(Project *project, FILE *file)
{
    FrameNode *curr = project->frames;
    Frame *frame = NULL;

    //                                          We have only one, thus n=1
    fwrite(project->filter_config, sizeof(*project->filter_config), 1, file);
    fwrite(&project->filter_index, sizeof(project->filter_index), 1, file);

    while (curr)
    {
        frame = curr->frame;

        // +1 for the null byte
        fwrite(frame->name, sizeof(*frame->name), strlen(frame->name) + 1,
               file);
        fwrite(frame->path, sizeof(*frame->path), strlen(frame->path) + 1,
               file);
        // We have only one duration, so we write only one of it. Thus the 1.
        fwrite(&frame->duration, sizeof(frame->duration), 1, file);

        curr = curr->next;
    }
}

void project_load(FILE *file, Project **out)
{
    Project *project = project_create();
    Frame *frame = NULL;

    char *frame_name = NULL;
    char *frame_path = NULL;
    unsigned int frame_duration = 0;

    fread(project->filter_config, sizeof(*project->filter_config), 1, file);
    fread(&project->filter_index, sizeof(project->filter_index), 1, file);

    while (!feof(file))
    {
        frame_name = read_line(file, PROJECT_LOAD_READ_LINE_START_SIZE, '\0');
        frame_path = read_line(file, PROJECT_LOAD_READ_LINE_START_SIZE, '\0');

        // Append only if the reads where successful
        if (fread(&frame_duration, sizeof(frame_duration), 1, file) &&
            strlen(frame_name) && strlen(frame_path))
        {
            frame = frame_create(frame_name, frame_duration, frame_path);

            frame_list_append(&project->frames, frame);
        }
        else
        {
            free(frame_name);
            free(frame_path);
        }
    }

    *out = project;
}
