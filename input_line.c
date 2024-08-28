#include "shell.h"

/**
 * input_buffer - Reads input from the user,
 * handling buffering and comments.
 * @info: A pointer to the info_t structure.
 * @buf: A pointer to the buffer to store the input.
 * @len: A pointer to the length of the buffer.
 *
 * Return: The number of bytes read.
 */

ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		s = getline(buf, &len_p, stdin);
#else
		s = _getline(info, buf, &len_p);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0';
				s--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * get_line_input - Gets a line of input from the user,
 * handling command chaining.
 * @info: A pointer to the info_t structure.
 *
 * Return: The number of bytes read.
 */

ssize_t get_line_input(info_t *info)
{
	static char *buf;
	static size_t l, j, len;
	ssize_t s = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	s = input_buf(info, &buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = l;
		p = buf + l; /* get pointer for return */

		check_chain(info, buf, &j, l, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		l = j + 1;
		if (l >= len)
		{
			l = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (s);
}

/**
 * read_buffer - Reads a buffer
 * @info: A pointer to the info_t structure.
 * @buf: The buffer to store the read data.
 * @i: A pointer to the current position in the buffer.
 *
 * Return: The number of bytes read.
 */

ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = r;
	return (s);
}

/**
 * _inputline - Reads a line of input from STDIN.
 * @info: A pointer to the info_t structure.
 * @ptr: Address of pointer to buffer.
 * @length: A pointer to the length of the buffer.
 *
 * Return: The number of bytes read
 */

int _inputline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t l, len;
	size_t e;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (l == len)
		l = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + l, '\n');
	e = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + e : e + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + l, e - l);
	else
		_strncpy(new_p, buf + l, e - l + 1);

	s += e - l;
	l = e;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * signal_handler_ctrl_c - Handles the SIGINT signal (Ctrl-C).
 *
 * @sig_num: The signal number.
 */

void signal_handler_ctrl_c(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
