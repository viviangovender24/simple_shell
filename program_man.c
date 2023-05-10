#include "shell_head.h"

/**
 *parser - parses builtin programs
 *@tok:split tokens from standard input
 *Return:0 - success,1 otherwise
 */
int parser(char **tok)
{
/*cd handling*/
	if (_strcomp(*tok, "cd") == 0)
	{
		return (_cd(tok));
	}
/*user invokes env*/
	else if (_strcomp(*tok, "env") == 0)
	{
		return (shell_environment());
	}
/*user invokes setenv*/
	else if (_strcomp(*tok, "sete") == 0)
	{
/*check if user inputs it in the form: setenv var_name var_value*/
		if (tok[1] && tok[2])
		{
			_sete(tok[1], tok[2]);
			return (0);
		}
/*else print a ERR message*/
		printf("Usage: sete name value\n");
		return (0);
	}
	else if (_strcomp(*tok, "unsete") == 0)
	{
/*check for var_name to change*/
		if (tok[1])
		{
			_unsete(tok[1]);
			return (0);
		}
/*else an error msg*/
		printf("Usage: unsete NAME\n");
		return (0);
	}
	else if (_strcomp(*tok, "history") == 0)
	{
		return (display_history());
	}
/*return 1 if no instance was handled*/
	return (1);
}
