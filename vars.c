#include "shell.h"

/**
 * is_chain - Check for chaining operators in the command buffer and update the command buffer type.
 * @info: Pointer to the info structure containing command information.
 * @buf: Pointer to the command buffer.
 * @p: Pointer to the current position in the command buffer.
 *
 * This function examines the character at the current position in the command buffer
 * and identifies chaining operators such as '||', '&&', and ';'. It updates the buffer
 * accordingly and sets the command buffer type in the info structure.
 *
 * Return: 1 if a chaining operator is found, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0; /* Replace '|' with null terminator to separate commands */
        j++;
        info->cmd_buf_type = CMD_OR; /* Set command buffer type to CMD_OR */
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0; /* Replace '&' with null terminator to separate commands */
        j++;
        info->cmd_buf_type = CMD_AND; /* Set command buffer type to CMD_AND */
    }
    else if (buf[j] == ';')
    {
        buf[j] = 0;                     /* Replace semicolon with null terminator to separate commands */
        info->cmd_buf_type = CMD_CHAIN; /* Set command buffer type to CMD_CHAIN */
    }
    else
    {
        return 0; /* No chaining operator found, return 0 */
    }

    *p = j; /* Update the pointer position */

    return 1; /* Indicate successful identification of a chaining operator */
}

/**
 * check_chain - Update the command buffer based on the command buffer type and status.
 *
 * @info: Pointer to the info structure containing command information.
 * @buf: Pointer to the command buffer.
 * @p: Pointer to the current position in the command buffer.
 * @i: Index to identify the current character in the buffer.
 * @len: Length of the command buffer.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    /* Check if the command buffer type is CMD_AND */
    if (info->cmd_buf_type == CMD_AND)
    {
        /* Check if the status is true (non-zero) */
        if (info->status)
        {
            buf[i] = 0; /* Replace the current character with null terminator */
            j = len;    /* Set the pointer to the end of the buffer */
        }
    }

    /* Check if the command buffer type is CMD_OR */
    if (info->cmd_buf_type == CMD_OR)
    {
        /* Check if the status is false (zero) */
        if (!info->status)
        {
            buf[i] = 0; /* Replace the current character with null terminator */
            j = len;    /* Set the pointer to the end of the buffer */
        }
    }

    *p = j; /* Update the pointer position */
}

/**
 * replace_alias - Replace the command if it matches an alias.
 *
 * @info: Pointer to the info structure containing command information.
 *
 * This function replaces the command in the info structure's argv[0]
 * if it matches an alias in the provided alias list.
 *
 * Return: 1 if the command is successfully replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    /* Iterate up to 10 times to search for alias matches */
    for (i = 0; i < 10; i++)
    {
        /* Find a node in the alias list that starts with the command */
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);

        /* Free the existing command in argv[0] */
        free(info->argv[0]);

        /* Find the position of '=' in the alias string */
        p = _strchr(node->str, '=');
        if (!p)
            return (0);

        /* Duplicate the part of the alias string after '=' */
        p = _strdup(p + 1);
        if (!p)
            return (0);

        /* Set the new command in argv[0] */
        info->argv[0] = p;
    }

    return (1);
}

/**
 * replace_vars - Replace variables in the command arguments.
 *
 * @info: Pointer to the info structure containing command information.
 *
 * This function iterates through the command arguments and replaces
 * variables such as "$?", "$$", and environment variables with their values.
 *
 * Return: Always returns 0.
 */
int replace_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    /* Iterate through each command argument */
    for (i = 0; info->argv[i]; i++)
    {
        /* Skip non-variable arguments */
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        /* Replace variable with exit status if it is "$?" */
        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]),
                           _strdup(convert_number(info->status, 10, 0)));
            continue;
        }

        /* Replace variable with process ID if it is "$$" */
        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }

        /* Find environment variable in the env list and replace */
        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]),
                           _strdup(_strchr(node->str, '=') + 1));
            continue;
        }

        /* Replace unknown variable with an empty string */
        replace_string(&info->argv[i], _strdup(""));
    }

    return (0);
}

/**
 * replace_string - Replace a string with a new one.
 *
 * @old: Pointer to the old string (to be replaced).
 * @new: Pointer to the new string.
 *
 * This function frees the memory of the old string and replaces it
 * with the new string.
 *
 * Return: Always returns 1.
 */
int replace_string(char **old, char *new)
{
    free(*old); /* Free the memory of the old string */
    *old = new; /* Replace the old string with the new one */
    return (1); /* Return 1 indicating successful replacement */
}