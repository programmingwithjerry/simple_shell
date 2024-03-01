#include "mshell.h"
/* Assuming my_getline is defined in a separate file (mshell_functions.c)*/ 
ssize_t my_getline(char *line, size_t line_size) {
    size_t chars_read = 0; /*No characters read yet */ 
    int c;

    /* Read characters one by one until newline or buffer full*/
    while ((c = getchar()) != EOF && chars_read < line_size - 1) {
        /* Check for newline and handle accordingly*/ 
        if (c == '\n') {
            break;
        }

        /*tore the character in the line */ 
        line[chars_read++] = c;
    }

    /* Handle errors or EOF*/ 
    if (c == EOF && chars_read == 0) {
        return -1;
    }

    /* Terminate the line with null character*/ 
    line[chars_read] = '\0';

    /* Return the number of characters read (excluding newline)*/ 
    return chars_read;
}

