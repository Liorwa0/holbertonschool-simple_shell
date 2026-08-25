#include "shell.h"

/**
 * read_line - Reads a line of input from standard input
 *
 * Return: Pointer to the read line, or NULL on EOF/error
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}

/**
 * split_line - Splits a line into tokens (arguments)
 * @line: The input string to split
 *
 * Return: Null-terminated array of tokens, or NULL on failure
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Allocation error");
		return (NULL);
	}

	token = strtok(line, DELIM);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("Allocation error");
				return (NULL);
			}
		}
		token = strtok(NULL, DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * free_args - Frees the memory allocated for arguments array
 * @args: Array of strings
 */
void free_args(char **args)
{
	if (args)
		free(args);
}
