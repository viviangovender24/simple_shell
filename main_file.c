#include "shell_head.h"

/**
 * main_file - entry point
 * @arc: arg count
 * @arv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main_file(int arc, char **arv)
{
	info_t read[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (arc == 2)
	{
		fd = open(arv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(arv[0]);
				_eputs(": 0: Can't open ");
				_eputs(arv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		read->readfd = fd;
	}
	fill_list(read);
	check_past(read);
	hsh(read, arv);
	return (EXIT_SUCCESS);
}
