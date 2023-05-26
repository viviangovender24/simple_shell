#include "shell_head.h"

/**
 * fill_buff - buffers chained commands
 * @read: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t fill_buff(info_t *read, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)read->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(read, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--; }
			read->linecount_flag = 1;
			delete_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				read->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * _myinput - gets a line minus the newline
 * @read: parameter struct
 *
 * Return: bytes read
 */
ssize_t _myinput(info_t *read)
{
	static char *buf; /* the ';' command chain buffer */
static size_t b, j, len;
	ssize_t r = 0;
	char **buf_p = &(read->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(read, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = b; /* init new iterator to current buf position */
		p = buf + b; /* get pointer for return */

		check_chain(read, buf, &j, b, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(read, buf, &j))
				break;
			j++;
		}

		b = j + 1; /* increment past nulled ';'' */
		if (b >= len) /* reached end of buffer? */
		{
			b = len = 0; /* reset position and length */
			read->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * check_buf - reads a buffer
 * @read: parameter struct
 * @buf: buffer
 * @b: size
 *
 * Return: r
 */
ssize_t check_buf(info_t *read, char *buf, size_t *b)
{
	ssize_t r = 0;

	if (*b)
		return (0);
	r = rd(read->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*b = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @read: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *read, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t b, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (b == len)
		b = len = 0;

	r = read_buf(read, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + b, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + b, k - i);
	else
		_strncpy(new_p, buf + b, k - i + 1);

	s += k - b;
	b = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sig_Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sig_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
