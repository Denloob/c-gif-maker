#include "main.h"

int main(void)
{
    Project *project = NULL;
    MenuFunction menu_function = NULL;

    puts("Welcome! What would you like to do?");

    loading_menu_input()(&project);

    while (true)
    {
        menu_function = menu_input();

        menu_function(project);
    }

    // Will never be reached, these lines will be optimized anyway, so I will
    // leave them here, because they don't hurt anybody :)
    project_cleanup(project);
    return EXIT_SUCCESS;
}
