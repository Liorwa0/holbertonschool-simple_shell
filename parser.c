#include "shell.h"

/**
 * split_line - Splits a line into tokens using DELIM
 * @line: The input line to parse
 *
 * Return: Array of string pointers (tokens), or NULL on failure
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
		return (NULL);

	token = strtok(line, DELIM);
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
		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}
