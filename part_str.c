#include "shell.h"

/**
 * f_command - Determines if a file is an executable command.
 * @info: A pointer to the info_t structure.
 * @path: The path to the file.
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */

int f_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * dup_chars - Duplicates characters from a string.
 * @pathstr: The source string.
 * @start: The starting index.
 * @stop: The stopping index.
 *
 * Return: A pointer to the newly allocated buffer
 * containing the duplicated characters.
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int d = 0, k = 0;

	for (k = 0, d = start; d < stop; d++)
		if (pathstr[d] != ':')
			buf[k++] = pathstr[d];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path_cmd - Finds the full path of a command in the PATH string.
 * @info: A pointer to the info_t structure.
 * @pathstr: The PATH string.
 * @cmd: The commad to find.
 *
 * Return: full path of cmd if found or NULL
 */

char *find_path_cmd(info_t *info, char *pathstr, char *cmd)
{
	int d = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
		if (is_cmd(info, cmd))
			return (cmd);
	while (1)
	{
		if (!pathstr[d] || pathstr[d] == ':')
		{
			path = dup_chars(pathstr, curr_pos, d);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[d])
				break;
			curr_pos = d;
		}
		d++;
	}
	return (NULL);
}
