#include "shell.h"

/**
 * addnode_linkedlist - Adds a new node to the beginning
 * of a linked list.
 * @head: Address of pointer to head node
 * @str: The string to be stored in the new node.
 * @num: The index of the new node.
 *
 * Return: A pointer to the newly created node.
 */

list_t *addnode_linkedlist(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * addnode_end_linkedlist - Adds a new node to the end
 * of a linked list.
 * @head: Address of pointer to head node.
 * @str: The string to be stored in the new node.
 * @num: The index of the new node.
 *
 * Return: A pointer to the newly created node.
 */

list_t *addnode_end_linkedlist(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_linkedlist_str - Prints the string elements of a linked list
 * @h: A pointer to the first node of the linked list.
 *
 * Return: The number of elements printed.
 */

size_t print_linkedlist_str(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * del_node_index - Deletes the node at the specified
 * index in a linked list.
 * @head: Address of pointer to first node.
 * @index: The index of node to delete.
 *
 * Return: 1 on success, 0 on failure
 */

int del_node_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int k = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (k == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		k++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_linkedlist - Frees all nodes of a linked list.
 *
 * @head_ptr: Address of pointer to head node.
 */

void free_linkedlist(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
