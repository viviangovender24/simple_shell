#include "shell.h"

/**
 * edit_info - initializes info_t struct
 * @read: struct address
 */
void edit_info(info_t *read)
{
	read->arg = NULL;
	read->argv = NULL;
	read->path = NULL;
	read->argc = 0;
}

/**
 * get_info - initializes info_t struct
 * @read: struct address
 * @avt: argument vector
 */
void get_info(info_t *read, char **avt)
{
	int b = 0;

	read->fname = avt[0];
	if (read->arg)
	{
		read->argv = strtow(info->arg, " \t");
		if (!read->argv)
		{
			read->argv = malloc(sizeof(char *) * 2);
			if (read->argv)
			{
				read->argv[0] = _strdup(read->arg);
				read->argv[1] = NULL; }
		}
		for (b = 0; read->argv && read->argv[b]; b++)
			;
		read->argc = b;

		replace_alias(read);
		replace_vars(read);
	}
}

/**
 * push_info - frees info_t struct fields
 * @read: struct address
 * @all: true if freeing all fields
 */
void push_info(info_t *read, int all)
{
	ffree(read->argv);
	read->argv = NULL;
	read->path = NULL;
	if (all)
	{
		if (!read->cmd_buf)
			free(read->arg);
		if (read->env)
			free_list(&(read->env));
		if (read->past)
			free_list(&(read->past));
		if (read->alias)
			free_list(&(read->alias));
		ffree(read->environ);
			read->environ = NULL;
		bfree((void **)read->cmd_buf);
		if (read->readfd > 2)
			close(read->readfd);
		_putchar(BUF_FLUSH);
	}
}
