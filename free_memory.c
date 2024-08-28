#include "shell.h"

/**
 * mfree - Frees a pointer and NULLs the address.
 * @ptr: Address of the memory to free.
 *
 * Return: 1 if the memory was freed, otherwise 0.
 */

int mfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

