#include "shell.h"

/**
 * _hislist - Displays the history list, one command by line, preceded
 * with line numbers.
 * @info: A pointer to the info_t structure.
 *  Return: 0
 */

int _hislist(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * rm_alias - Removes an alias from the alias list.
 * @info: A pointer to the info_t structure.
 * @str: The name of the alias to remove.
 *
 * Return: 1 if the alias was removed, 0 otherwise.
 */

int rm_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * s_alias - Sets alias to string.
 * @info: A pointer to the info_t structure.
 * @str: The alias string.
 *
 * Return: 0 on success, 1 on failure.
 */

int s_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * p_alias - Prints an alias string.
 * @node: A pointer to the alias node.
 *
 * Return: 0 on success, 1 on failure.
 */

int p_alias(list_t *node)
{
	char *p = NULL, *s = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (s = node->str; s <= p; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _xalias - Manages aliases.
 * @info: A pointer to the info_t structure.
 *  Return: 0
 */

int _xalias(info_t *info)
{
	int k = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		p = _strchr(info->argv[k], '=');
		if (p)
			set_alias(info, info->argv[k]);
		else
			print_alias(node_starts_with(info->alias, info->argv[k], '='));
	}

	return (0);
}
