#include "input.h"

char *read_line(FILE *stream, const size_t starting_size, const char eol_char)
{
    size_t len = 0;
    size_t size = starting_size;
    char ch = 0;
    char *str = (char *)malloc(sizeof(char) * starting_size);
    char *tmp = NULL;

    while ((ch = fgetc(stream)) != EOF && ch != eol_char)
    {
        str[len] = ch;

        len++;

        if (len == size)
        {
            if (!(tmp = (char *)realloc(str,
                                        size *= INPUT_BUFFER_SCALING_FACTOR)))
            {
                puts("ERROR: Out of memory.");
                free(str);
                return NULL; // You said it's ok to early return for error stuff.
            }

            str = tmp;
        }
    }

    str[len] = '\0';

    return (char *)realloc(str, sizeof(char) * (len + 1));
}

char *input()
{
    return read_line(stdin, INPUT_STDIN_STARTING_SIZE,
                     INPUT_STDIN_NEW_LINE_CHAR);
}

unsigned long input_choice_max(const unsigned long max,
                               PrintFunction print_function, const char *prompt,
                               const char *on_error_message)
{
    unsigned long choice = 0;
    bool input_valid = 0;

    do
    {
        printf("%s", prompt);

        print_function();

        scanf("%lu", &choice);
        flush_input();

        input_valid = choice < max;

        if (!input_valid)
        {
            printf("%s", on_error_message);
        }
    } while (!input_valid);

    return choice;
}

void flush_input()
{
    char ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
        /* discard */;
}
