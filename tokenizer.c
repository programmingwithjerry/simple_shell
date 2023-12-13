#include "shell.h"

/**
 * strtow - Split a string into words based on delimiters.
 *
 * @str: The input string to be split.
 * @d: Delimiters used for splitting the string.
 *
 * This function splits the input string into words based on the specified
 * delimiters and returns an array of strings.
 *
 * Return: An array of strings if successful, or NULL if allocation fails.
 */
char **strtow(char *str, char *d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    /* Check if the input string is NULL or empty */
    if (str == NULL || str[0] == 0)
        return (NULL);

    /* Set default delimiters to space if not provided */
    if (!d)
        d = " ";

    /* Count the number of words in the input string */
    for (i = 0; str[i] != '\0'; i++)
        if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
            numwords++;

    /* If no words found, return NULL */
    if (numwords == 0)
        return (NULL);

    /* Allocate memory for the array of strings */
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);

    /* Loop to extract words from the input string */
    for (i = 0, j = 0; j < numwords; j++)
    {
        /* Skip delimiters */
        while (is_delim(str[i], d))
            i++;

        /* Count characters in the current word */
        k = 0;
        while (!is_delim(str[i + k], d) && str[i + k])
            k++;

        /* Allocate memory for the current word */
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            /* Free allocated memory if allocation fails */
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }

        /* Copy characters of the current word */
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];

        /* Null-terminate the current word */
        s[j][m] = 0;
    }

    /* Null-terminate the array of strings */
    s[j] = NULL;

    return (s);
}

/**
 * strtow2 - Split a string into words based on a single character delimiter.
 *
 * @str: The input string to be split.
 * @d: The single character delimiter used for splitting the string.
 *
 * This function splits the input string into words based on the specified
 * single character delimiter and returns an array of strings.
 *
 * Return: An array of strings if successful, or NULL if allocation fails.
 */
char **strtow2(char *str, char d)
{
    int i, j, k, m, numwords = 0;
    char **s;

    /* Check if the input string is NULL or empty */
    if (str == NULL || str[0] == 0)
        return (NULL);

    /* Count the number of words in the input string */
    for (i = 0; str[i] != '\0'; i++)
        if ((str[i] != d && str[i + 1] == d) ||
            (str[i] != d && !str[i + 1]) || str[i + 1] == d)
            numwords++;

    /* If no words found, return NULL */
    if (numwords == 0)
        return (NULL);

    /* Allocate memory for the array of strings */
    s = malloc((1 + numwords) * sizeof(char *));
    if (!s)
        return (NULL);

    /* Loop to extract words from the input string */
    for (i = 0, j = 0; j < numwords; j++)
    {
        /* Skip leading delimiters */
        while (str[i] == d && str[i] != d)
            i++;

        /* Count characters in the current word */
        k = 0;
        while (str[i + k] != d && str[i + k] && str[i + k] != d)
            k++;

        /* Allocate memory for the current word */
        s[j] = malloc((k + 1) * sizeof(char));
        if (!s[j])
        {
            /* Free allocated memory if allocation fails */
            for (k = 0; k < j; k++)
                free(s[k]);
            free(s);
            return (NULL);
        }

        /* Copy characters of the current word */
        for (m = 0; m < k; m++)
            s[j][m] = str[i++];

        /* Null-terminate the current word */
        s[j][m] = 0;
    }

    /* Null-terminate the array of strings */
    s[j] = NULL;

    return (s);
}