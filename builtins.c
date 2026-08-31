#include "shell.h"

/**
 * handle_builtin - Runs a built-in if args[0] is one
 * @args: Null-terminated array of arguments
 * @line: Buffer from read_line, freed before exiting
 * @last: Exit status of the last executed command
 *
 * Return: 1 if a built-in was handled, 0 otherwise
 */
int handle_builtin(char **args, char *line, int last)
{
	int status = last;

	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
			status = atoi(args[1]);

		free_args(args);
		free(line);
		exit(status);
	}

	if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}

	return (0);
}

/**
 * print_env - Prints the environment, one per line
 */
void print_env(void)
{
	int i;

	for (i = 0; environ && environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
}
