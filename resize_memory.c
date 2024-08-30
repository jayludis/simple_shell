#include "shell.h"

/**
 **_memoryset - Fills a memory area with a constant byte.
 *
 *@s: A pointer to the memory area to be filled.
 *@b: The constant byte to fill the memory with.
 *@n: The number of bytes to be filled.
 *
 *Return: A pointer to the memory area s.
 */

char *_memoryset(char *s, char b, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		s[k] = b;
	return (s);
}

/**
 * sfree - Frees a string of strings.
 *
 * @pp: A double pointer to the string of strings.
 */

void sfree(char **pp)
{
	char **p = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(p);
}

/**
 * _resize_memory - Reallocates a block of memory.
 *
 * @ptr: A pointer to the previous allocated block.
 * @old_size: The size of the previous block in bytes.
 * @new_size: The new size of the block in bytes.
 *
 * Return: A pointer to the reallocated block.
 */

void *_resize_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
