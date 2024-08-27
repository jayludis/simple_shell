#include "shell.h"

/**
 *_errputs - Prints a string to standard error.
 * @str: The string to be printed.
 */

void _errputs(char *str)
{
	int k;

	if (!str)
		return;
	for (k = 0; str[k] ; k++)
		_eputchar(str[k]);
}

/**
 * _errputchar - Writes the character c to standard error.
 * @c: The character to print.
 *
 * Return: 1 on success, -1 on error.
 */

int _errputchar(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 * _putfd - Writes the character c to specified file descriptor.
 * @c: The character to print.
 * @fd: The filedescriptor to write to.
 *
 * Return: 1 on success, -1 on error.
 */
int _putfd(char c, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 *_putsfdes - Writes a string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The filedescriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfdes(char *str, int fd)
{
	int k = 0;

	if (!str)
		return (0);
	while (*str)
		k += _putfd(*str++, fd);
	return (k);
}
