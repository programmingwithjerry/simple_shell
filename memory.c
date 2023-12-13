/**
 * bfree - Free the memory block pointed to by a double pointer.
 *
 * @ptr: The double pointer to the memory block.
 *
 * This function frees the memory block pointed to by the double pointer @ptr
 * and sets the pointer to NULL. It returns 1 if the memory was freed, or 0 if
 * the double pointer is NULL or if the pointer it points to is already NULL.
 *
 * Return: 1 if the memory was freed, 0 otherwise.
 */
int bfree(void **ptr)
{
    /* Check if the double pointer and the pointer it points to are not NULL */
    if (ptr && *ptr)
    {
        /* Free the memory block and set the pointer to NULL */
        free(*ptr);
        *ptr = NULL;

        /* Return 1 to indicate success */
        return (1);
    }

    /* Return 0 if the double pointer is NULL or the pointer is already NULL */
    return (0);
}