#include "menu.h"

const MenuFunction menu_functions[] = {menu_exit,
                                       menu_add_frame,
                                       menu_remove_frame,
                                       menu_move_frame,
                                       menu_change_frame_duration,
                                       menu_change_frame_duration_all,
                                       menu_display_frames,
                                       menu_play_project,
                                       menu_set_filter,
                                       menu_reverse_frame_order,
                                       menu_save_project};

const char *menu_items_names[] = {
    "Exit",
    "Add new Frame",
    "Remove a Frame",
    "Change frame index",
    "Change frame duration",
    "Change duration of all frames",
    "List frames",
    "Play movie!",
    "Set a filter",
    "Reverse frame order",
    "Save project",
};

const LoadingMenuFunction loading_menu_functions[] = {
    loading_menu_new_project,
    loading_menu_load_project,
};

const char *loading_menu_items_names[] = {"Create a new project",
                                          "Load existing project"};

void loading_menu_print()
{
    for (unsigned long i = 0; i < LOADING_MENU_SIZE; i++)
    {
        printf(" [%lu] %s\n", i, loading_menu_items_names[i]);
    }
}

LoadingMenuFunction loading_menu_input()
{
    unsigned long choice =
        input_choice_max(LOADING_MENU_SIZE, loading_menu_print, "",
                         "Invalid choice, try again:\n");

    return loading_menu_functions[choice];
}

void loading_menu_new_project(Project **out)
{
    puts("Working on a new project.");
    *out = project_create();
}

void loading_menu_load_project(Project **out)
{
    FILE *file_ptr = NULL;
    char *file_path = NULL;

    puts("Enter the path of the project (including project name):");
    file_path = input();

    file_ptr = fopen(file_path, "rb");

    free(file_path);

    if (file_ptr)
    {
        project_load(file_ptr, out);
        puts("Project loaded successfully");
        fclose(file_ptr);
    }
    else
    {
        puts("Error! - can't open file, creating a new project");
        loading_menu_new_project(out);
    }
}

void menu_exit(Project *project)
{
    puts("Bye!");
    project_cleanup(project);
    exit(EXIT_SUCCESS);
}

void menu_add_frame(Project *project)
{
    frame_list_append_stdin(&project->frames);
}

void menu_remove_frame(Project *project)
{
    unsigned int index = 0;
    char *frame_name = NULL;
    bool removal_success = 0;

    printf("Enter the name of the frame you wish to erase: ");
    frame_name = input();

    removal_success =
        (frame_list_find_by_name(project->frames, frame_name, &index) &&
         frame_list_remove(&project->frames, index));

    free(frame_name);

    if (!removal_success)
    {
        puts("The frame was not found");
    }
}

void menu_move_frame(Project *project)
{
    unsigned int frame_index = 0, target_index = 0;
    char *frame_name = NULL;
    bool index_valid = 0;
    bool frame_exists = 0;
    unsigned int length = frame_list_length(project->frames);

    puts("Enter the name of the frame");
    frame_name = input();

    frame_exists =
        frame_list_find_by_name(project->frames, frame_name, &frame_index);

    free(frame_name);

    if (!frame_exists)
    {
        puts("this frame does not exist");
        return; // Again, you said that's ok to use early returns for error handling.
    }

    do
    {
        puts("Enter the new index in the movie you wish to place the frame");
        scanf("%u", &target_index);
        flush_input();

        index_valid = (target_index >= 1 && target_index <= length);

        if (!index_valid)
        {
            printf("The movie contains only %d frames!\n", length);
        }
    } while (!index_valid);

    target_index--; // To fix indexes starting from 1.

    if (!frame_list_move_frame(&project->frames, frame_index, target_index))
    {
        puts("ERROR: Move failed");
    }
}

void menu_change_frame_duration(Project *project)
{
    FrameNode *node = NULL;
    char *frame_name = NULL;
    bool frame_exists = 0;
    unsigned int frame_index = 0;

    puts("Enter the name of the frame");
    frame_name = input();

    frame_exists =
        frame_list_find_by_name(project->frames, frame_name, &frame_index);

    free(frame_name);

    if (!frame_exists || !frame_list_get(project->frames, frame_index, &node))
    {
        puts("this frame does not exist");
        return;
    }

    frame_change_duration_stdin(node->frame);
}

void menu_change_frame_duration_all(Project *project)
{
    unsigned int duration = 0;

    puts("Enter the duration:");
    scanf("%u", &duration);
    flush_input();

    frame_list_set_duration(project->frames, duration);
}

void menu_display_frames(Project *project)
{
    frame_list_display(project->frames);
}

void menu_set_filter(Project *project)
{
    project->filter_index = filters_menu_input_index();
    enum FilterConfigType filter_config_type =
        filter_types[project->filter_index];

    filters_input_config(filter_config_type, project->filter_config);

    printf("Filter set to %s!\n", filter_names[project->filter_index]);
}

void menu_play_project(Project *project)
{
    puts("Playing!");
    puts("Press any key while focused on the GIF window to stop.");
    view_play(project);
}

void menu_save_project(Project *project)
{
    FILE *save_file = NULL;
    char *file_path = NULL;
    int write_allowed = true;

    puts("Enter the path to save the project");
    file_path = input();

    if (file_exists(file_path))
    {
        puts(
            "Do you want to overwrite the file? 1 for yes, any other for no: ");
        scanf("%u", &write_allowed);
        flush_input();
    }

    if (write_allowed)
    {
        save_file = fopen(file_path, "wb");

        if (save_file == NULL)
        {
            puts("Could not open file");
            return;
        }

        project_save(project, save_file);

        fclose(save_file);
    }
    else
    {
        puts("Cancelled");
    }

    free(file_path);
}

void menu_print()
{
    for (unsigned long i = 0; i < MENU_SIZE; i++)
    {
        printf(" [%lu] %s\n", i, menu_items_names[i]);
    }
}

void menu_reverse_frame_order(Project *project)
{
    frame_list_reverse(&project->frames);
}

MenuFunction menu_input()
{
    char on_error_message[MENU_INPUT_ERROR_MESSAGE_BUFFER_SIZE] = {0};

    // 0 and MENU_SIZE -1 because we start from 0, and maximum is the size of
    // menu array, but we want to print inclusive range, so -1.
    snprintf(on_error_message, MENU_INPUT_ERROR_MESSAGE_BUFFER_SIZE,
             "You should type one of the options - %d-%lu!\n", 0,
             (MENU_SIZE - 1));
    unsigned long choice =
        input_choice_max(MENU_SIZE, menu_print,
                         "\nWhat would you like to do?\n", on_error_message);

    return menu_functions[choice];
}
