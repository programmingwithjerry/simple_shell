#include "mshell.h"
/*
 * Function to handle the exit command
 *
 * This function implements the behavior of the `exit` command in the `mshell`.
 * It allows users to exit the shell with a specified exit code, providing informative
 * error messages and ensuring proper exit behaviors.
 *
 * Arguments:
 *   - arguments: An array of strings representing the command and its arguments
 *                 (e.g., ["exit", "123"]).
 */
void exit_command(char *arguments[]) {
    int exit_status;
    char *endptr;

    /* Check for no argument */
    if (arguments[1] == NULL) {
        /* Exit with default status 0 (success) */
        exit(EXIT_SUCCESS);
    } else {
        /* Check for second argument */
        if (arguments[2] == NULL) {
            /* Invalid format message to stderr*/
            write(STDERR_FILENO, "exit: invalid format. Usage: exit status\n", 41);
            exit(EXIT_FAILURE);
        }

        /* Convert and handle invalid status */
        exit_status = strtol(arguments[2], &endptr, 10);
        if (*endptr != '\0') {
            /* Invalid status message to stderr*/
            write(STDERR_FILENO, "exit: invalid status '", 22);
            write(STDERR_FILENO, arguments[2], strlen(arguments[2]));
            write(STDERR_FILENO, "'\n", 2);
            exit(EXIT_FAILURE);
        }

        exit(exit_status);
    }
}
