#include "shell.h"
/*
 * Simple shell implementation
 *
 * This code provides a basic framework for a simple shell program.
 * It includes error handling, memory management, and placeholders for
 * essential functionalities like user input handling and command execution.
 *
 * Author: Bard (AI Assistant)
 */

int main() {
    char *input = NULL;
    size_t input_size = 0;
    char **args;
    char *command;
    /* Main loop for shell interaction */
    while (1) {
        /* Prompt the user for input */
        prompt_user();

        /* Allocate memory for input before getline */
        input = realloc(input, input_size);
        if (input == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        /* Read user input using getline */
        if (getline(&input, &input_size, stdin) == -1) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        /* Process user input (assuming `get_command` or similar function) */
      /* Process user input */
       args = tokenize_input(input);
        command = args[0];

        if (strcmp(command, "cd") == 0) {
            builtin_cd(args);
        } else if (strcmp(command, "exit") == 0) {
            exit(EXIT_SUCCESS);
        } else {
            exec_external_command(args);
        }

        /* Free memory after using input */
        free(input);
        input = NULL;
        input_size = 0;

	free(args);
    }

    

    return 0;
}

