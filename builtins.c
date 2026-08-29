#include "shell.h"

/*
 * handle_builtin - Runs a built-in if args[0] is one
 * @args: Null-terminated array of arguments
 * @line: Buffer from read_line, freed before exiting
 *
 * Return: 1 if a built-in was handled, 0 otherwise
 */
int handle_builtin(char **args, char *line, int last)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		free(line);
		exit(last);
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

	for (i = 0; environ[i] != NULL; i++)
		printf("%s\n", environ[i]);
}

