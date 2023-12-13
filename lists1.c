#include "shell.h"

/**
 * list_len - Get the number of elements in a linked list.
 *
 * @h: Pointer to the head of the linked list.
 *
 * This function traverses the linked list starting from the head @h and
 * returns the number of elements in the list.
 *
 * Return: The number of elements in the linked list.
 */
size_t list_len(const list_t *h)
{
    size_t i = 0;

    /* Iterate through the linked list and count the elements */
    while (h)
    {
        h = h->next;
        i++;
    }

    /* Return the number of elements in the linked list */
    return (i);
}

    /**
     * list_to_strings - Convert a linked list of strings to an array of strings.
     *
     * @head: Pointer to the head of the linked list.
     *
     * This function converts a linked list of strings into an array of strings.
     * It allocates memory for the array and each string. The array is terminated
     * by a NULL pointer. If memory allocation fails, it frees the allocated memory
     * and returns NULL.
     *
     * Return: An array of strings, or NULL on failure.
     */
    char *
    *list_to_strings(list_t * head)
{
    list_t *node = head;
    size_t i = list_len(head), j;
    char **strs;
    char *str;

    /* Check if the linked list is NULL or empty */
    if (!head || !i)
        return (NULL);

    /* Allocate memory for the array of strings */
    strs = malloc(sizeof(char *) * (i + 1));
    if (!strs)
        return (NULL);

    /* Iterate through the linked list and convert each string */
    for (i = 0; node; node = node->next, i++)
    {
        /* Allocate memory for the current string */
        str = malloc(_strlen(node->str) + 1);
        if (!str)
        {
            /* Free allocated memory if an allocation fails */
            for (j = 0; j < i; j++)
                free(strs[j]);
            free(strs);
            return (NULL);
        }

        /* Copy the string to the allocated memory */
        str = _strcpy(str, node->str);
        strs[i] = str;
    }

    /* Terminate the array with a NULL pointer */
    strs[i] = NULL;

    /* Return the array of strings */
    return (strs);
}

/**
 * print_list - Print elements of a linked list.
 *
 * @h: Pointer to the head of the linked list.
 *
 * This function prints the elements of a linked list, including the numeric
 * value and string content of each node. It returns the number of elements
 * in the linked list.
 *
 * Return: The number of elements in the linked list.
 */
size_t print_list(const list_t *h)
{
    size_t i = 0;

    /* Iterate through the linked list and print each node's information */
    while (h)
    {
        /* Print the numeric value of the node followed by a colon and space */
        _puts(convert_number(h->num, 10, 0));
        _putchar(':');
        _putchar(' ');

        /* Print the string content of the node or "(nil)" if NULL */
        _puts(h->str ? h->str : "(nil)");

        /* Print a newline character */
        _puts("\n");

        /* Move to the next node in the linked list */
        h = h->next;

        /* Increment the counter for the number of elements */
        i++;
    }

    /* Return the number of elements in the linked list */
    return (i);
}

/**
 * node_starts_with - Find a node in a linked list whose string starts with
 *                    a given prefix and optionally ends with a specific
 *                    character.
 *
 * @node: Pointer to the head of the linked list.
 * @prefix: The prefix to check for at the beginning of each string.
 * @c: The optional character to check for at the end of the matched strings.
 *
 * This function iterates through the linked list starting from the given @node
 * and looks for a node whose string starts with the specified @prefix. If @c
 * is not -1, it also checks whether the matched string ends with @c. It returns
 * a pointer to the first matching node or NULL if no match is found.
 *
 * Return: A pointer to the first matching node or NULL if not found.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
    char *p = NULL;

    /* Iterate through the linked list and check each node's string */
    while (node)
    {
        /* Check if the node's string starts with the specified prefix */
        p = starts_with(node->str, prefix);

        /* Check if the prefix is found and, if specified, the character matches */
        if (p && ((c == -1) || (*p == c)))
            return (node);

        /* Move to the next node in the linked list */
        node = node->next;
    }

    /* Return NULL if no matching node is found */
    return (NULL);
}

/**
 * get_node_index - Get the index of a node in a linked list.
 *
 * @head: Pointer to the head of the linked list.
 * @node: Pointer to the node whose index is to be determined.
 *
 * This function iterates through the linked list starting from the given @head
 * and returns the index of the specified @node. If the @node is not found, it
 * returns -1.
 *
 * Return: The index of the node or -1 if the node is not found.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
    size_t i = 0;

    /* Iterate through the linked list and find the index of the node */
    while (head)
    {
        /* Check if the current node is the specified node */
        if (head == node)
            return (i);

        /* Move to the next node in the linked list */
        head = head->next;

        /* Increment the index */
        i++;
    }

    /* Return -1 if the specified node is not found in the linked list */
    return (-1);
}