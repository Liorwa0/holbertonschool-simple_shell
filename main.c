#include "shell.h"

/**
 * execute_cmd - Forks and executes a command with arguments
 * @args: Null-terminated array of arguments
 * @prog_name: Name of the shell executable (for errors)
 *
 * Return: 0 on success, or 1 on error
 */
int execute_cmd(char **args, char *prog_name)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (0);

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(prog_name);
			exit(127);
		}
	}
	else if (pid < 0)
	{
		perror(prog_name);
	}
	else
	{
		wait(&status);
	}

	return (0);
}

/**
 * main - Entry point for the simple UNIX command interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line;
	char **args;
	int interactive;
	(void)argc;

	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		line = read_line();
		if (line == NULL)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = split_line(line);
		if (args && args[0])
			execute_cmd(args, argv[0]);

		free_args(args);
		free(line);
	}

	return (0);
}
