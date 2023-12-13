#include "shell.h"

/**
 * clear_info - Clear fields in the info_t structure.
 *
 * @info: Pointer to the info_t structure to be cleared.
 *
 * This function clears specific fields in the @info structure, setting them
 * to NULL or zero as appropriate. The fields cleared include 'arg', 'argv',
 * 'path', and 'argc'.
 */
void clear_info(info_t *info)
{
    /* Set 'arg' to NULL */
    info->arg = NULL;

    /* Set 'argv' to NULL */
    info->argv = NULL;

    /* Set 'path' to NULL */
    info->path = NULL;

    /* Set 'argc' to 0 */
    info->argc = 0;
}

/**
 * set_info - Set fields in the info_t structure based on command-line arguments.
 *
 * @info: Pointer to the info_t structure to be updated.
 * @av: Array of command-line arguments.
 *
 * This function sets fields in the @info structure based on the command-line
 * arguments provided in the 'av' array. It updates 'fname', 'arg', 'argv', and
 * 'argc' fields in the @info structure. If 'arg' is not NULL, it tokenizes it
 * into an 'argv' array using the strtow function. The function also replaces
 * aliases and variables in the 'argv' array using replace_alias and replace_vars.
 */
void set_info(info_t *info, char **av)
{
    int i = 0;

    /* Set 'fname' to the program name from the command-line arguments */
    info->fname = av[0];

    /* Check if 'arg' is not NULL */
    if (info->arg)
    {
        /* Tokenize 'arg' into an 'argv' array using the strtow function */
        info->argv = strtow(info->arg, " \t");

        /* Check if 'argv' is NULL (error during tokenization) */
        if (!info->argv)
        {
            /* Allocate memory for a minimal 'argv' array and copy 'arg' into it */
            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = _strdup(info->arg);
                info->argv[1] = NULL;
            }
        }

        /* Count the number of elements in the 'argv' array and update 'argc' */
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        /* Replace aliases in the 'argv' array */
        replace_alias(info);

        /* Replace variables in the 'argv' array */
        replace_vars(info);
    }
}

/**
 * free_info - Free allocated memory in the info_t structure.
 *
 * @info: Pointer to the info_t structure containing information to be freed.
 * @all: Flag indicating whether to free all memory or just specific fields.
 *
 * This function frees the allocated memory in the @info structure. If 'all'
 * is non-zero, it frees memory associated with 'arg', 'env', 'history', 'alias',
 * 'environ', 'cmd_buf', and closes the file descriptor 'readfd'. It also flushes
 * the buffer using the _putchar function. The 'argv' and 'path' fields are set
 * to NULL. If 'all' is zero, only 'argv' is freed and set to NULL.
 */
void free_info(info_t *info, int all)
{
    /* Free the 'argv' array and set it to NULL */
    ffree(info->argv);
    info->argv = NULL;

    /* Set 'path' to NULL */
    info->path = NULL;

    /* Check if 'all' is non-zero (free all memory) */
    if (all)
    {
        /* Check if 'arg' is not part of 'cmd_buf' (not freed with cmd_buf) */
        if (!info->cmd_buf)
            free(info->arg);

        /* Free the 'env' linked list */
        if (info->env)
            free_list(&(info->env));

        /* Free the 'history' linked list */
        if (info->history)
            free_list(&(info->history));

        /* Free the 'alias' linked list */
        if (info->alias)
            free_list(&(info->alias));

        /* Free the 'environ' array and set it to NULL */
        ffree(info->environ);
        info->environ = NULL;

        /* Free the 'cmd_buf' array and set it to NULL */
        bfree((void **)info->cmd_buf);

        /* Close the file descriptor 'readfd' */
        if (info->readfd > 2)
            close(info->readfd);

        /* Flush the buffer using _putchar */
        _putchar(BUF_FLUSH);
    }
}