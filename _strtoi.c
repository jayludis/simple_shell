#include "shell.h"

/**
 * is_interactive - Determines if the shell is running in interactive mode.
 * @info: A pointer to the info_t structure.
 *
 * Return: 1 if the shell is interactive, 0 otherwise.
 */

int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if character is a delimeter
 * @c: The character to check.
 * @delim: The delimeter string.
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Checks if a character is an alphabetic letter.
 * @c: The character to check.
 * Return: 1 if the character is an alphabetic letter, 0 otherwise.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_strtoi - Converts a string to an integer.
 *@s: The string to be converted.
 *Return: The converted integer value, or 0 if no numbers are found.
 */

int _strtoi(char *s)
{
	int k, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (k = 0;  s[k] != '\0' && flag != 2; k++)
	{
		if (s[k] == '-')
			sign *= -1;

		if (s[k] >= '0' && s[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[k] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
