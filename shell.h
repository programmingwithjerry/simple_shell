#ifndef SHELL_H
#define SHELL_H


#include <stdarg.h>
#include <errno.h> /*for perror*/

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
/* for read/write buffers (MACROS) */
#define MAX_PATH_LENGTH 1024
#define MAX_COMMAND_LENGTH 256
#define MAX_ALIASES 100
#define BUFFER_SIZE 1024

struct Alias
{
	char *name;
	char *value;
};

struct Alias aliases[MAX_ALIASES];

/*int main(int argc, char *argv[]);*/
<<<<<<< HEAD
=======
/* Function prototypes */
char **tokenize_input(char *input);
void builtin_cd(char **args);
int exec_external_command(char **args);


>>>>>>> 977cd08ab3b7630d70a83080539943413d1a1194
void prompt_user(void);
void our_get_command(char *command, size_t size);
/*void getAndPrintCommand();*/
int isjerry_print(const char *format, ...);
/*void execute_command(const char *command);*/
void execute_command(const char *command);
void isjerry_get_command(char *command, size_t size);
void handleCommandLine(int argc, char *argv[]);
/*void handle_path(const char *command);*/
/*void exit_shell();*/
/*void handle_exit_cmd(const char *input);*/
void isjerry_print_env_built_in(void);
void execute_exit_command(void);
/*void isjerry_execute_exit_command(void);*/
void execute_path_command(const char *command);
void isjerry_semicolon_handler(char *input);
void isjerry_ampersound_handler(char *input);
void isjerry_or_handler(char *input);
void isjerry_print_all_aliases(void);
void isjerry_print_specific_aliases(char *names[], int count);
void isjerry_define_alias(char *name, char *value);
void isjerry_alias_builtin(int argc, char *argv[]);
int our_unsetenv_builtin(const char *variable);
int isjerry_setenv_builtin(const char *variable, const char *value);
int our_cd_builtin(char *directory);

/*aliases*/
void our_print_all_aliases(void);
void our_print_specific_aliases(char *names[], int count);
void our_define_alias(char *name, char *value);
void our_alias_builtin(int argc, char *argv[]);


#endif
