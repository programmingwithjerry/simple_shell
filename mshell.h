#ifndef MSHELL_H
#define MSHELL_H
/*
 *Custom Header files for C fnctions
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stddef.h>

#define MAX_ARGS 64
#define MAX_INPUT_SIZE 1024

void print_prompt(void);
void m_print(const char *string_prompt);
void read_cmd(char *prompt_command, size_t prompt_size);
void exec_command(const char *prompt_command, char *arguments[]);
void tokenize_input(char *prompt_command, char *arguments[]);

#endif /* MSHELL_H */
