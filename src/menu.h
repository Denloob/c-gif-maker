#ifndef MENUH
#define MENUH

#include "file.h"
#include "linkedList.h"
#include "project.h"
#include "view.h"
#include <stdlib.h>

#define MENU_INPUT_ERROR_MESSAGE_BUFFER_SIZE 100

typedef void (*MenuFunction)(Project *);
typedef void (*LoadingMenuFunction)(Project **);

// @see https://stackoverflow.com/a/1856642/16586000
extern const MenuFunction menu_functions[];

extern const char *menu_items_names[];

#define MENU_SIZE (sizeof(menu_functions) / sizeof(menu_functions[0]))

extern const LoadingMenuFunction loading_menu_functions[];

extern const char *loading_menu_items_names[];

#define LOADING_MENU_SIZE                                                      \
    (sizeof(loading_menu_functions) / sizeof(loading_menu_functions[0]))

/**
 * @brief Prints the loading menu.
 */
void loading_menu_print();

/**
 * @brief Prompts the user to choose an option from the loading menu after
 *  displaying it.
 *
 * @return Function representing user's choice.
 */
LoadingMenuFunction loading_menu_input();

/**
 * @brief Creates a new project.
 *
 * @param out The new project.
 */
void loading_menu_new_project(Project **out);

/**
 * @brief Loads a project from a file. (Read from stdin)
 *
 * @param out The project to load.
 */
void loading_menu_load_project(Project **out);

/**
 * @brief Exits from the program. Cleans everything up.
 *
 * @param project The project to exit.
 */
void menu_exit(Project *project);

/**
 * @brief Adds a frame to the project.
 *
 * @param project The project to add the frame to.
 */
void menu_add_frame(Project *project);

/**
 * @brief Removes a frame from the project.
 *
 * @param project The project to remove the frame from.
 */
void menu_remove_frame(Project *project);

/**
 * @brief Moves a frame in the project.
 *
 * @param project The project to move the frame in.
 */
void menu_move_frame(Project *project);

/**
 * @brief Changes the duration of a frame.
 *
 * @param project The project in which to change the frame's duration.
 */
void menu_change_frame_duration(Project *project);

/**
 * @brief Changes the duration of all frames.
 *
 * @param project The project in which to change the frames' duration.
 */
void menu_change_frame_duration_all(Project *project);

/**
 * @brief Displays all frames in the project.
 *
 * @param project The project frames of which to display.
 */
void menu_display_frames(Project *project);

/**
 * @brief Plays the project.
 *
 * @param project The project to play.
 */
void menu_play_project(Project *project);

/**
 * @brief Sets a filter for the project.
 *
 * @param project The project in which to set the filter.
 */
void menu_set_filter(Project *project);

/**
 * @brief Saves the project.
 *
 * @param project The project to save.
 */
void menu_save_project(Project *project);

/**
 * @brief Prints the menu.
 */
void menu_print();

/**
 * @brief Reverses the order of the frames in the project.
 *
 * @param project The project to reverse.
 */
void menu_reverse_frame_order(Project *project);

/**
 * @brief Prompts the user to choose an option from the menu after displaying it.
 *
 * @return Function representing user's choice.
 */
MenuFunction menu_input();

#endif /* ifndef MENUH */
