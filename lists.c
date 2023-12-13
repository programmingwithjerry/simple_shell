#include "shell.h"

/**
 * add_node - Add a new node at the beginning of a linked list.
 *
 * @head: Pointer to the pointer to the head of the linked list.
 * @str: The string to be assigned to the new node (can be NULL).
 * @num: The numeric value to be assigned to the new node.
 *
 * This function creates a new node, initializes its values, and adds it to the
 * beginning of the linked list specified by the pointer to the head (@head).
 * It returns a pointer to the newly added node or NULL on failure.
 *
 * Return: A pointer to the newly added node, or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
    list_t *new_head;

    /* Check if the pointer to the head is NULL */
    if (!head)
        return (NULL);

    /* Allocate memory for the new node */
    new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);

    /* Initialize the new node with zeros */
    _memset((void *)new_head, 0, sizeof(list_t));

    /* Assign the numeric value to the new node */
    new_head->num = num;

    /* Assign the string to the new node (if provided) */
    if (str)
    {
        new_head->str = _strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }

    /* Set the next pointer of the new node to the current head */
    new_head->next = *head;

    /* Update the head pointer to the new node */
    *head = new_head;

    /* Return a pointer to the newly added node */
    return (new_head);
}

/**
 * add_node_end - Add a new node at the end of a linked list.
 *
 * @head: Pointer to the pointer to the head of the linked list.
 * @str: The string to be assigned to the new node (can be NULL).
 * @num: The numeric value to be assigned to the new node.
 *
 * This function creates a new node, initializes its values, and adds it to the
 * end of the linked list specified by the pointer to the head (@head). It returns
 * a pointer to the newly added node or NULL on failure.
 *
 * Return: A pointer to the newly added node, or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *node;

    /* Check if the pointer to the head is NULL */
    if (!head)
        return (NULL);

    /* Get the current head node */
    node = *head;

    /* Allocate memory for the new node */
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    /* Initialize the new node with zeros */
    _memset((void *)new_node, 0, sizeof(list_t));

    /* Assign the numeric value to the new node */
    new_node->num = num;

    /* Assign the string to the new node (if provided) */
    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    /* If the list is not empty, find the last node and append the new node */
    if (node)
    {
        while (node->next)
            node = node->next;
        node->next = new_node;
    }
    else
    {
        /* If the list is empty, set the head to the new node */
        *head = new_node;
    }

    /* Return a pointer to the newly added node */
    return (new_node);
}

/**
 * print_list_str - Print strings of elements in a linked list.
 *
 * @h: Pointer to the head of the linked list.
 *
 * This function prints the strings of the elements in a linked list. If a
 * string is NULL, it prints "(nil)". It returns the number of elements
 * in the linked list.
 *
 * Return: The number of elements in the linked list.
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    /* Iterate through the linked list and print each node's string */
    while (h)
    {
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
 * delete_node_at_index - Delete a node at a specified index in a linked list.
 *
 * @head: Pointer to the pointer to the head of the linked list.
 * @index: The index of the node to be deleted.
 *
 * This function deletes the node at the specified @index in the linked list
 * specified by the pointer to the head (@head). It returns 1 on success and 0
 * if the deletion fails (e.g., if the index is out of bounds or the list is
 * empty).
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *node, *prev_node;
    unsigned int i = 0;

    /* Check if the pointer to the head or the list is NULL */
    if (!head || !*head)
        return (0);

    /* Check if the index is 0 (delete the first node) */
    if (!index)
    {
        node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);

        /* Return 1 to indicate success */
        return (1);
    }

    /* Iterate through the linked list to find the node at the specified index */
    node = *head;
    while (node)
    {
        /* Check if the current node is the one to be deleted */
        if (i == index)
        {
            /* Update the next pointer of the previous node */
            prev_node->next = node->next;

            /* Free the memory allocated for the string and the node */
            free(node->str);
            free(node);

            /* Return 1 to indicate success */
            return (1);
        }

        /* Increment the index and move to the next node in the linked list */
        i++;
        prev_node = node;
        node = node->next;
    }

    /* Return 0 to indicate failure (index out of bounds or list is empty) */
    return (0);
}

/**
 * free_list - Free a linked list and set its head pointer to NULL.
 *
 * @head_ptr: Pointer to the pointer to the head of the linked list.
 *
 * This function frees the memory allocated for each node in the linked list
 * and sets the head pointer (@head_ptr) to NULL. It does nothing if the
 * pointer to the head or the list is NULL.
 */
void free_list(list_t **head_ptr)
{
    list_t *node, *next_node, *head;

    /* Check if the pointer to the head or the list is NULL */
    if (!head_ptr || !*head_ptr)
        return;

    /* Get the current head node */
    head = *head_ptr;

    /* Iterate through the linked list and free each node's memory */
    node = head;
    while (node)
    {
        /* Get the next node before freeing the current node */
        next_node = node->next;

        /* Free the memory allocated for the string and the node */
        free(node->str);
        free(node);

        /* Move to the next node in the linked list */
        node = next_node;
    }

    /* Set the head pointer to NULL */
    *head_ptr = NULL;
}