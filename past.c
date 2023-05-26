#include "shell_head.h"

/**
 * get_pastfile - gets the history file
 * @read: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_pastfile(info_t *read)
{
	char *buf, *dir;

	dir = _getenv(read, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
return (buf);
}

/**
 * write_past - creates a file, or appends to an existing file
 * @read: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_past(info_t *read)
{
	ssize_t fd;
	char *filename = get_pastfile(read);
	list_ *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = read->past; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_past - reads history from file
 * @read: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_past(info_t *read)
{
	int b, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_pastfile(read);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (b = 0; b < fsize; b++)
		if (buf[b] == '\n')
		{
			buf[b] = 0;
			build_pastlist(read, buf + last, linecount++);
			last = b + 1;
		}
	if (last != b)
		build_pastlist(read, buf + last, linecount++);
	free(buf);
	read->histcount = linecount;
	while (read->histcount-- >= HIST_MAX)
		remove_node(&(read->history), 0);
	renum_past(read);
	return (read->histcount);
}

/**
 * build_pastlist - adds entry to a history linked list
 * @read: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_pastlist(info_t *read, char *buf, int linecount)
{
	list_ *node = NULL;

	if (read->history)
		node = read->history;
	node_end(&node, buf, linecount);

	if (!read->history)
		read->history = node;
	return (0);
}

/**
 * renum_past - renumbers the history linked list after changes
 * @read: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renum_past(info_t *read)
{
	list_ *node = read->history;
	int b = 0;

	while (node)
	{
		node->num = b++;
		node = node->next;
	}
	return (read->histcount = b);
}
