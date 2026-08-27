#include "shell.h"

/**
 * execute_cmd - Forks and executes a command with arguments
 * @args: Null-terminated array of arguments
 * @prog_name: Name of the shell executable (for errors)
 *
 * Return: 0 on success, or 1 on error
 */
int execute_cmd(char **args, char *prog_name, int count)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL)
		return (0);
	
/* Find path */
	cmd_path = find_path(args[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", prog_name, count, args[0]);
		return (127);
	}

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_path, args, environ);
		perror(prog_name);
		free(cmd_path);
		_exit(127);
	}
	else if (pid < 0)
	{
		perror(prog_name); free(cmd_path);
	}
	else
	{
		wait(&status); free(cmd_path);
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
	int interactive, count = 0, last = 0;
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
		count++;

		args = split_line(line);
		if (args && args[0])
			last = execute_cmd(args, argv[0], count);

		free_args(args);
		free(line);
	}

	return (last);
}
