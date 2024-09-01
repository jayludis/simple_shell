#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int s, j;
	char *s = dest;

	s = 0;
	while (src[s] && s < n - 1)
	{
		dest[s] = src[s];
		s++;
	}
	if (s < n)
	{
		j = s;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int s = 0, j = 0;
	char *s = dest;

	while (dest[s])
		s++;
	for (; src[j] && j < n; s++, j++)
		dest[s] = src[j];
	if (j < n)
		dest[s] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++);

	return (NULL);
}
