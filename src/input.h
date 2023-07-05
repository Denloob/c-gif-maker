#ifndef INPUTH
#define INPUTH

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_STDIN_STARTING_SIZE 16
#define INPUT_STDIN_NEW_LINE_CHAR '\n'
#define INPUT_BUFFER_SCALING_FACTOR 2

/**
 * @brief Reads a line from the stream and returns it.
 *
 * @param stream The stream to read from.
 * @param starting_size The size of the buffer before reading.
 * @param eol_char The character with which the line ends. (Doesn't read it).
 * @return A pointer to the read line.
 */
char *read_line(FILE *stream, const size_t starting_size, const char eol_char);

/**
 * @brief Wrapper for read_line, which reads from stdin until INPUT_STDIN_NEW_LINE_CHAR
 *
 * @return A pointer to the read line.
 */
char *input();

/**
 * @brief Flushes (clears) the input buffer.
 *
 * @see https://c-faq.com/stdio/stdinflush2.html
 */
void flush_input();

typedef void (*PrintFunction)(void);

/**
 * @brief Prompts the user for input.
 *
 * @param max The maximum value the user is allowed to input. (Exclusive).
 * @param print_function The function to print the possible choices.
 * @param prompt The prompt to print. (before print_function call).
 * @param on_error_message The message to print if the user inputs an invalid choice.
 */
unsigned long input_choice_max(const unsigned long max,
                               PrintFunction print_function, const char *prompt,
                               const char *on_error_message);

#endif /* INPUTH */
