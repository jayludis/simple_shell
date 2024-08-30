#include "shell.h"

/**
 * _str_c - Copies a string to another.
 * @dest: The destination string.
 * @src: the source string.
 *
 * Return: A pointer to destination string.
 */

char *_str_c(char *dest, char *src)
{
	int k;

	if (dest == src || !src)
		return (dest);
	for (k = 0; src[k] ; k++)
		dest[i] = src[k];
	dest[k] = 0;
	return (dest);
}

/**
 * _str_dup - Duplicates a string.
 *
 * @str: The string to duplicate.
 *
 * Return: A pointer to the duplicated string.
 */

char *_str_dup(const char *str)
{
	int l = 0;
	char *ret;

	if (!str)
		return (NULL);
	while (*str++)
		l++;
	ret = malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (NULL);
	for (l++; l--;)
		ret[l] = *--str;
	return (ret);
}

/**
 *_puts - Prints a string to standard output.
 *@str: The string to be printed.
 */

void _puts(char *str)
{
	int k;

	if (!str)
		return;
	for (k = 0; str[k] ; k++)
		_putchar(str[k]);
}

/**
 * _putchar - Writes the character c to standard output.
 *
 * @c: The character to print.
 *
 * Return: 1 on success, -1 on error.
 */

int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
