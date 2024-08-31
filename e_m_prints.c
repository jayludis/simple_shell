#include "shell.h"

/**
 * _errstr - Converts a string to an integer,
 * handling potential errors.
 * @s: The string to be converted.
 * Return: The converted integer value, or -1 on error.
 */

int _errstr(char *s)
{
	int k = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (k = 0;  s[k]; k++)
	{
		if (s[k] >= '0' && s[k] <= '9')
		{
			result *= 10;
			result += (s[k] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Prints an error message.
 * @info: A pointer to the info_t structure.
 * @estr: String containing specified error type.
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error.
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_decim - Prints a decimal (integer) number
 * to the specified file descriptor.
 * @input: The integer to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: number of characters printed
 */

int print_decim(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int k, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (_abs_ / k)
		{
			__putchar('0' + current / k);
			count++;
		}
		current %= k;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_num - Converts a number to a string representation.
 * @num: The number to be converted.
 * @base: The base for the conversion.
 * @flags: Optional flags to control the conversion
 * (e.g., CONVERT_UNSIGNED, CONVERT_LOWERCASE).
 *
 * Return: A pointer to the converted string.
 */

char *convert_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - Removes the first occurrence of a '#'
 * comment from a string with '\0'.
 * @buf: The string to modify.
 *
 * Return: Always 0;
 */

void rm_comments(char *buf)
{
	int k;

	for (k = 0; buf[k]; k++)
		if (buf[k] == '#' && (!k || buf[k - 1] == ' '))
		{
			buf[k] = '\0';
			break;
		}
}
