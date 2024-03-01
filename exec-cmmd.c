#include "mshell.h"

void exec_command(const char *prompt_command, char *arguments[]) {
  pid_t c_pid = fork(); /* Create child process */
  char *envp[] = {"PATH=/usr/bin", NULL}; /* Default environment */
  char *dir;
  char *path;
  char *path_copy = NULL; /* Initialize to NULL for safety */
  extern char **environ;

  if (c_pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (c_pid == 0) { /* Child process */
    if (strcmp(prompt_command, "env") == 0) { /* Check if the command is 'env' */
      /* Print the current environment */
      char **env;
      for (env = environ; *env != NULL; env++) {
        write(STDOUT_FILENO, *env, strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
      }
      exit(EXIT_SUCCESS); /* Exit successfully after printing environment */
    }

    if (strcmp(prompt_command, "/bin/ls") == 0) { /* Check for "/bin/ls" specifically */
      /* Directly execute "/bin/ls" for efficiency */
      execve(prompt_command, arguments, environ);
      exit(EXIT_FAILURE); /* Only reached if execve fails */
    }

    path = getenv("PATH"); /* Get the PATH environment variable */
    if (path == NULL) {
      perror("getenv");
      exit(EXIT_FAILURE);
    }

    path_copy = strdup(path); /* Make a copy of PATH */
    if (path_copy == NULL) {
      perror("strdup");
      exit(EXIT_FAILURE);
    }

    dir = strtok(path_copy, ":"); /* Tokenize PATH by colon */
    while (dir != NULL) {
      char command_path[1024];
      snprintf(command_path, sizeof(command_path), "%s/%s", dir, prompt_command);

      /* Check if the command exists in this directory */
      if (access(command_path, X_OK) == 0) {
        /* Execute command */
        if (execve(command_path, arguments, envp) == -1) {
          perror("execve");
          exit(EXIT_FAILURE);
        }
      }

      dir = strtok(NULL, ":");
    }

    /* If the command was not found in any directory */
    fprintf(stderr, "%s: command not found\n", prompt_command);
    exit(EXIT_FAILURE);
  } else { /* Parent process */
    wait(NULL); /* Wait for child to finish */
  }

  /* Free memory allocated by strdup (if successful) */
  if (path_copy != NULL) {
    free(path_copy);
  }
}

