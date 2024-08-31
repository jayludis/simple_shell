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
		dest[k] = src[k];
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
	int len = 0;
	char *ret;

	if (!str)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
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
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}
