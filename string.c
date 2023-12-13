#include "shell.h"

/**
 * _putchar - Write a character to the standard output.
 *
 * @c: The character to be written.
 *
 * This function writes a character to the standard output. If the character
 * is BUF_FLUSH or the buffer is full, it flushes the buffer by writing its
 * content to the standard output using the write function.
 *
 * Return: Always returns 1.
 */
int _putchar(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    /* Flush the buffer if the character is BUF_FLUSH or buffer is full */
    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buf, i);
        i = 0;
    }

    /* If the character is not BUF_FLUSH, add it to the buffer */
    if (c != BUF_FLUSH)
        buf[i++] = c;

    return (1);
}

/**
 * _strcmp - Compare two strings.
 *
 * @s1: The first input string.
 * @s2: The second input string.
 *
 * This function compares two strings lexicographically and returns an integer
 * representing their relationship: 0 if equal, a negative value if s1 is less
 * than s2, or a positive value if s1 is greater than s2.
 *
 * Return: The result of the comparison.
 */
int _strcmp(char *s1, char *s2)
{
    /* Iterate through both strings until a difference is found */
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }

    /* Check for equality at the end of both strings */
    if (*s1 == *s2)
        return (0);
    else
        return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Check if a string starts with another string.
 *
 * @haystack: The string to be checked.
 * @needle: The prefix string to check for.
 *
 * This function checks if the string @haystack starts with the prefix
 * @needle. If it does, it returns a pointer to the character in @haystack
 * immediately after the prefix; otherwise, it returns NULL.
 *
 * Return: A pointer to the character after the prefix or NULL if not found.
 */
char *starts_with(const char *haystack, const char *needle)
{
    /* Iterate through both strings until a difference is found */
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);

    /* Return a pointer to the character after the prefix in haystack */
    return ((char *)haystack);
}

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strcat - Concatenate two strings.
 *
 * @dest: The destination string.
 * @src: The source string to be concatenated.
 *
 * This function concatenates the source string @src to the destination
 * string @dest. It returns a pointer to the beginning of the resulting
 * string in @dest.
 *
 * Return: A pointer to the beginning of the concatenated string.
 */
char *_strcat(char *dest, char *src)
{
    /* Save the starting address of dest for the return value */
    char *ret = dest;

    /* Move to the end of dest */
    while (*dest)
        dest++;

    /* Copy characters from src to dest */
    while (*src)
        *dest++ = *src++;

    /* Null-terminate the resulting string in dest */
    *dest = *src;

    return (ret);
}