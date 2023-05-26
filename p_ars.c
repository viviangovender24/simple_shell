#include "shell_head.h"

/**
 *  cm_d - determines if a file is an executable command
 * @read: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int cm_d(info_t *read, char *path)
{
	struct stat st;

	(void)read;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * same_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *same_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int b = 0, k = 0;

	for (k = 0, b = start; b < stop; b++)
		if (pathstr[b] != ':')
			buf[k++] = pathstr[b];
	buf[k] = 0;
	return (buf);
}

/**
 * get_path - finds this cmd in the PATH string
 * @read: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *get_path(info_t *read, char *pathstr, char *cmd)
{
	int b = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (cm_d(read, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[b] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, b);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (cm_d(read, path))
				return (path);
			if (!pathstr[b])
				break;
			curr_pos = b;
}
		b++;
	}
	return (NULL);
}
