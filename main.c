#include "shell.h"

/**
 * execute_cmd - Forks a child process and executes a command with arguments
 * @args: Null-terminated array of arguments
 * @prog_name: Name of the shell executable
 * @count: Execution count for error messages
 *
 * Return: Status code of executed command
 */
int execute_cmd(char **args, char *prog_name, int count)
{
	pid_t pid;
	int status;
	char *cmd_path;

	if (args[0] == NULL)
		return (0);

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
		perror(prog_name);
		free(cmd_path);
	}
	else
	{
		wait(&status);
		free(cmd_path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (1);
}

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Exit status of the last executed command
 */
int main(int ac, char **av)
{
	char *line;
	char **args;
	int count = 0, last = 0;

	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		line = read_line();
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		count++;

		args = split_line(line);
		if (args && args[0] && handle_builtin(args, line, last) == 0)
			last = execute_cmd(args, av[0], count);

		free_args(args);
		free(line);
	}

	return (last);
}
