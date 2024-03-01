#include "mshell.h"

/* Function to change directory*/
int cd_command(char *arguments[]) {
    if (arguments[1] == NULL) {
        /*Change to home directory*/
        if (chdir(getenv("HOME")) != 0) {
            perror("cd");
            return 1; /* Indicate failure*/
        }
    } else {
        /* Change to specified directory*/
        if (chdir(arguments[1]) != 0) {
            perror("cd");
            return 1; /* Indicate failure*/
        }
    }
    return 0; /* Indicate success*/
}

/* Function to clear the screen (cross-platform compatible)*/
void clear_command() {
    /* Use system-specific commands based on the operating system*/
    write(STDOUT_FILENO, "\033[2J\033[1;1H", 12); /* ANSI escape codes for clearing screen*/
}

