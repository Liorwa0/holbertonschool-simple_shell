#include "shell.h"

/**
 * execute_cmd - Forks a child process and executes a command
 * @args: Null-terminated array of arguments
 * @prog_name: Name of the shell executable
 *
 * Return: 1 to continue loop
 */
int execute_cmd(char **args, char *prog_name)
{
	pid_t pid;
	int status;

	if (!args || !args[0])
		return (1);

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(prog_name);
			exit(1);
		}
	}
	else if (pid < 0)
	{
		perror(prog_name);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	return (1);
}

/**
 * main - Entry point for the simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Always 0
 */
int main(int ac, char **av)
{
	char *line;
	char **args;
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

		args = split_line(line);
		if (args && args[0])
			execute_cmd(args, av[0]);

		free(args);
		free(line);
	}
	return (0);
}
