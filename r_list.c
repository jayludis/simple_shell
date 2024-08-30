#include "shell.h"

/**
 * list_length - Calculates the length of a linked list.
 *
 * @h: A pointer to the first node of the linked list.
 *
 * Return: he length of the linked list.
 */

size_t list_length(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * list_to_strings - Converts a linked list
 * into an array of strings.
 *
 * @head: A pointer to the first node of the linked list.
 *
 * Return: An array of strings, or NULL on failure.
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t l = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !l)
		return (NULL);
	strs = malloc(sizeof(char *) * (l + 1));
	if (!strs)
		return (NULL);
	for (l = 0; node; node = node->next, l++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < l; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[l] = str;
	}
	strs[l] = NULL;
	return (strs);
}


/**
 * print_list - Prints all elements of a list_t linked list.
 * @h: A pointer to the first node of the linked list.
 *
 * Return: The number of elements printed.
 */

size_t print_list(const list_t *h)
{
	size_t l = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		l++;
	}
	return (l);
}

/**
 * start_node - Finds the first node in a linked list
 * whose string starts with the given prefix.
 *
 * @node: A pointer to the head of the linked list.
 * @prefix: The prefix string to match.
 * @c: The next character after the prefix to match.
 *
 * Return: match node or null
 */

list_t *start_node(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - Gets the index of a node in a linked list.
 *
 * @head: A pointer to the head of the linked list.
 * @node: A pointer to the node to find.
 *
 * Return: The index of the node, or -1 if not found.
 */

ssize_t node_index(list_t *head, list_t *node)
{
	size_t l = 0;

	while (head)
	{
		if (head == node)
			return (l);
		head = head->next;
		l++;
	}
	return (-1);
}
