#include "shell.h"

/**
 * get_history - Gets the path to the history file.
 * @info: A pointer to the info_t structure.
 *
 * Return: A pointer to the allocated string
 * containing the history file path.
 */

char *get_history(info_t *info)
{
        char *buffer, *dir;

        dir = _getenv(info, "HOME=");
        if (!dir)
                return (NULL);
        buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
        if (!buffer)
                return (NULL);
        buffer[0] = 0;
        _strcpy(buffer, dir);
        _strcat(buffer, "/");
        _strcat(buffer, HIST_FILE);
        return (buffer);
}

/**
 * write_history - Writes the command history to a file.
 * @info: A pointer to the info_t structure.
 *
 * Return: 1 on success, -1 on failure.
 */

int write_history(info_t *info)
{
        ssize_t d;
        char *filename = get_history(info);
        list_t *node = NULL;

        if (!filename)
                return (-1);

        d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
        free(filename);
        if (d == -1)
                return (-1);
        for (node = info->history; node; node = node->next)
        {
                _putsd(node->str, d);
                _putd('\n', d);
        }
        _putd(BUF_FLUSH, d);
        close(d);
        return (1);
}

/**
 * read_history - Reads the command history from a file.
 * @info: A pointer to the info_t structure.
 *
 * Return: The number of lines read, or 0 on failure.
 */

int read_history(info_t *info)
{
        int k, last = 0, linecount = 0;
        ssize_t d, rdlen, fsize = 0;
        struct stat st;
        char *buf = NULL, *filename = get_history(info);

        if (!filename)
                return (0);

        d = open(filename, O_RDONLY);
        free(filename);
        if (d == -1)
                return (0);
        if (!fstat(d, &st))
                fsize = st.st_size;
        if (fsize < 2)
                return (0);
        buf = malloc(sizeof(char) * (fsize + 1));
        if (!buf)
                return (0);
        rdlen = read(d, buf, fsize);
        buf[fsize] = 0;
        if (rdlen <= 0)
                return (free(buf), 0);
        close(d);
        for (k = 0; k < fsize; k++)
                if (buf[k] == '\n')
                {
                        buf[k] = 0;
                        build_history_list(info, buf + last, linecount++);
                        last = k + 1;
                }
        if (last != k)
                build_history_list(info, buf + last, linecount++);
        free(buf);
        info->histcount = linecount;
        while (info->histcount-- >= HIST_MAX)
                delete_node_at_index(&(info->history), 0);
        renumber_history(info);
        return (info->histcount);
}

/**
 * build_history_list - Adds entry to a command history linked list.
 * @info: A pointer to the info_t structure.
 * @buf: The command string to add.
 * @linecount: The line number of the command.
 *
 * Return: 0.
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
        list_t *node = NULL;

        if (info->history)
                node = info->history;
        add_node_end(&node, buf, linecount);

        if (!info->history)
                info->history = node;
        return (0);
}

/**
 * updnum_hist - Renumbers the command history linked list.
 * @info: A pointer to the info_t structure.
 *
 * Return: The new history count.
 */
int updnum_hist(info_t *info)
{
        list_t *node = info->history;
        int k = 0;

        while (node)
        {
                node->num = k++;
                node = node->next;
        }
        return (info->histcount = k);
}

