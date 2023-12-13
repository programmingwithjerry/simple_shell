#include "shell.h"

/**
 * _strcpy - Copy a string from source to destination.
 *
 * @dest: Destination buffer for the copied string.
 * @src: Source string to be copied.
 *
 * This function copies the characters from the source string to the
 * destination buffer and null-terminates the resulting string.
 *
 * Return: A pointer to the destination buffer.
 */
char *_strcpy(char *dest, char *src)
{
    int i = 0;

    /* Check for invalid pointers or if source is NULL */
    if (dest == src || src == NULL)
        return (dest);

    /* Copy characters from source to destination */
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }

    /* Null-terminate the destination string */
    dest[i] = 0;

    return (dest);
}

/**
 * _strdup - Duplicate a string.
 *
 * @str: The input string to be duplicated.
 *
 * This function duplicates the input string and returns a pointer to the
 * newly allocated memory containing the duplicated string.
 *
 * Return: A pointer to the duplicated string if successful, or NULL if
 * allocation fails or if the input string is NULL.
 */
char *_strdup(const char *str)
{
    int length = 0;
    char *ret;

    /* Check if the input string is NULL */
    if (str == NULL)
        return (NULL);

    /* Calculate the length of the input string */
    while (*str++)
        length++;

    /* Allocate memory for the duplicated string */
    ret = malloc(sizeof(char) * (length + 1));
    if (!ret)
        return (NULL);

    /* Copy characters from the input string to the duplicated string */
    for (length++; length--;)
        ret[length] = *--str;

    return (ret);
}

/**
 * _puts - Print a string to the standard output.
 *
 * @str: The input string to be printed.
 *
 * This function prints the characters of the input string to the standard
 * output using the _putchar function until the null terminator is reached.
 *
 * Return: None.
 */
void _puts(char *str)
{
    int i = 0;

    /* Check if the input string is NULL */
    if (!str)
        return;

    /* Iterate through the string and print each character */
    while (str[i] != '\0')
    {
        _putchar(str[i]);
        i++;
    }
}

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