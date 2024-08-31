#include "shell.h"

/**
 * _strcpy - Copies a specified number of characters
 * from one string to another.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: A pointer to the destination string.
 */

char *_strcpy(char *dest, char *src, int n)
{
	int k, j;
	char *s = dest;

	k = 0;
	while (src[k] && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		j = k;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strcat - Concatenates two strings
 * @dest: The destination string.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 * Return: A pointer to the destination string.
 */

char *_strcat(char *dest, char *src, int n)
{
	int k = 0, j = 0;
	char *s = dest;

	while (dest[k])
		k++;
	for (; src[j] && j < n; k++, j++)
		dest[k] = src[j];
	if (j < n)
		dest[k] = '\0';
	return (s);
}

/**
 * _strchar - Locates the first occurrence of a character in a string.
 * @s: The string to search.
 * @c: The character to search for.
 * Return: A pointer to the first occurrence of
 * the character in the string.
 */

char *_strchar(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++);

	return (NULL);
}
