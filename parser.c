#include "shell.h"

/**
 * is_cmd - Checks if a given path is a regular file.
 *
 * @info: Pointer to the info structure.
 * @path: The path to be checked.
 *
 * This function checks if the given @path corresponds to a regular file.
 *
 * Return: 1 if the path is a regular file, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    /* Ignore the info parameter */
    (void)info;

    /* Check if the path is NULL or stat fails (file doesn't exist) */
    if (!path || stat(path, &st))
        return (0);

    /* Check if the file is a regular file */
    if (st.st_mode & S_IFREG)
    {
        return (1);
    }

    /* Return 0 if the file is not a regular file */
    return (0);
}

/**
 * dup_chars - Duplicate characters from a string within a specified range.
 *
 * @pathstr: The input string containing characters to be duplicated.
 * @start: The starting index of the range (inclusive).
 * @stop: The ending index of the range (exclusive).
 *
 * This function duplicates characters from the @pathstr within the specified
 * range [@start, @stop) and returns a pointer to the duplicated characters.
 * The result is stored in a static buffer, and the buffer is overwritten with
 * each subsequent call to this function.
 *
 * Return: A pointer to the duplicated characters.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
    static char buf[1024];
    int i = 0, k = 0;

    /* Iterate through the specified range and copy non-colon characters */
    for (k = 0, i = start; i < stop; i++)
        if (pathstr[i] != ':')
            buf[k++] = pathstr[i];

    /* Null-terminate the duplicated characters */
    buf[k] = 0;

    /* Return a pointer to the duplicated characters */
    return (buf);
}

/**
 * find_path - Find the full path of a command in the given path string.
 *
 * @info: Pointer to the info structure.
 * @pathstr: The string containing directories separated by colons.
 * @cmd: The command to find in the path.
 *
 * This function searches for the full path of the specified @cmd within
 * the directories listed in the @pathstr. It returns a pointer to the
 * full path if found, or NULL otherwise.
 *
 * Return: A pointer to the full path of the command, or NULL if not found.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    int i = 0, curr_pos = 0;
    char *path;

    /* Check if the path string is NULL */
    if (!pathstr)
        return (NULL);

    /* Check if the command is a local file (starts with "./") */
    if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
    {
        /* Return the command if it is a valid file */
        if (is_cmd(info, cmd))
            return (cmd);
    }

    /* Iterate through the path string and search for the command */
    while (1)
    {
        if (!pathstr[i] || pathstr[i] == ':')
        {
            /* Duplicate characters within the current directory */
            path = dup_chars(pathstr, curr_pos, i);

            /* Append the command to the directory path */
            if (!*path)
                _strcat(path, cmd);
            else
            {
                _strcat(path, "/");
                _strcat(path, cmd);
            }

            /* Check if the full path corresponds to a valid command */
            if (is_cmd(info, path))
                return (path);

            /* Break if the end of the path string is reached */
            if (!pathstr[i])
                break;

            /* Update the current position for the next iteration */
            curr_pos = i;
        }

        /* Move to the next character in the path string */
        i++;
    }

    /* Return NULL if the command is not found in any directory */
    return (NULL);
}