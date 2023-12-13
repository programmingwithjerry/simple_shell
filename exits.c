#include "shell.h"

/**
 * _strncpy - Copies up to 'n' characters from the source
 * string to the destination string.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: Maximum number of characters to copy.
 * Return: Returns a pointer to the destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0, k;
	char *s = dest;

	/**
	* Use a while loop to copy characters from src
	*to dest up to the specified limit
	*/
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	/* If there is space remaining in dest, fill it with null characters */
	if (i < n)
	{
		k = i;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}

	/* Return a pointer to the beginning of the destination string */
	return (s);
}



/**
 * _strncat - Concatenates up to 'n' characters from the source
 *string to the destination string.
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 * @n: Maximum number of characters to concatenate.
 * Return: Returns a pointer to the destination string.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, k = 0;
	char *s = dest;

	/* Find the end of the destination string */
	while (dest[i] != '\0')
		i++;

	/**
	* Use a while loop to concatenate characters from src
	*to dest up to the specified limit
	*/
	while (src[k] != '\0' && k < n)
	{
		dest[i] = src[k];
		i++;
		k++;
	}

	/* If there is space remaining in dest, add a null terminator */
	if (k < n)
		dest[i] = '\0';
	/* Return a pointer to the beginning of the destination string */
	return (s);
}


/**
 * _strchr - Locates the first occurrence of a character in a string
 * @s: Pointer to the string to be searched.
 * @c: The character to be located.
 * Return: Returns a pointer to the first occurrence of the character 'c'
 * in the string 's',
 *  or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	/* Use a do-while loop to iterate through the characters of the string */
	do	{
	/* Check if the current character matches the target character */
	if (*s == c)
		return (s);

	/* Move to the next character in the string */
	} while (*s++ != '\0');

	/* Return NULL if the character is not found in the string */
	return (NULL);
}
