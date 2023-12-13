#include "shell.h"

/**
 * _memset - Fills the first @n bytes of the memory area pointed to by @s
 * with the constant byte @b.
 *
 * @s: Pointer to the memory area.
 * @b: The constant byte to fill the memory with.
 * @n: Number of bytes to fill.
 *
 * Return: A pointer to the memory area @s.
 */
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = b;

    return (s);
}

/**
 * ffree - Frees a double pointer and its allocated memory.
 *
 * @pp: The double pointer to be freed.
 *
 * This function frees the memory pointed to by the double pointer @pp
 * and then frees the memory of the double pointer itself.
 */
void ffree(char **pp)
{
    char **a = pp;

    /* Check if the double pointer is NULL */
    if (!pp)
        return;

    /* Free the memory pointed to by each element of the double pointer */
    while (*pp)
        free(*pp++);

    /* Free the memory of the double pointer itself */
    free(a);
}

/**
 * _realloc - Reallocates a memory block with a new size.
 *
 * @ptr: Pointer to the previously allocated memory block.
 * @old_size: The size, in bytes, of the allocated space for @ptr.
 * @new_size: The new size, in bytes, for the reallocated memory block.
 *
 * Return: Pointer to the reallocated memory block, or NULL on failure.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    /* If pointer is NULL, equivalent to malloc */
    if (!ptr)
        return (malloc(new_size));

    /* If new size is 0, equivalent to free and return NULL */
    if (!new_size)
        return (free(ptr), NULL);

    /* If new size is equal to old size, no need to reallocate */
    if (new_size == old_size)
        return (ptr);

    /* Allocate memory for the new size */
    p = malloc(new_size);
    if (!p)
        return (NULL);

    /* Copy the old data to the new memory block */
    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];

    /* Free the old memory block */
    free(ptr);

    /* Return the pointer to the new memory block */
    return (p);
}