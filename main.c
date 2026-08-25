#include "shell.h"

/**
 * read_line - Reads a line of input from standard input
 *
 * Return: Pointer to the allocated line string, or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	characters = getline(&line, &bufsize, stdin);
	if (characters == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: The input line to parse
 *
 * Return: Null-terminated array of string tokens
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position++] = token;
		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				return (NULL);
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * execute_cmd - Forks and executes the command
 * @args: Null-terminated array of arguments
 * @prog_name: Name of the shell executable for error reporting
 *
 * Return: 1 to continue execution
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
 * main - Entry point for the Simple Shell
 * @ac: Argument count (unused)
 * @av: Argument vector (contains program name)
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
