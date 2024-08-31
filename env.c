#include "shell.h"

/**
 * _penv - Prints the current variables.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int _penv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0 on success, 1 on failure.
 */

int _setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 0 on success, 1 on failure.
 */

int _unsetenv(info_t *info)
{
	int k;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= info->argc; k++)
		_unsetenv(info, info->argv[k]);

	return (0);
}

/**
 * p_env_list - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */

int p_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t l;

	for (l = 0; environ[l]; l++)
		add_node_end(&node, environ[l], 0);
	info->env = node;
	return (0);
}
