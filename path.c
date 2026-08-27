#include "shell.h"

/**
 * _getenv - Gets the value of an enviornment variable
 * @name: Name of the variable, for example "PATH"
 *
 * Return: Pointer to the value inside environ, or NULL if not found
 */
char *_getenv(const char *name)
{
	int i;
	size_t len;

	len = strlen(name);
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
	}

	return (NULL);
}

/**
 * find_path - Builds the full path of a command by searching PATH
 * @command: The command typed by the user, for example "ls"
 *
 * Return: Malloc'd full path to an executable, or NULL if not found
 */
char *find_path(char *command)
{
	char *path, *copy, *dir, *full;

	if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}

	path = _getenv("PATH");
	if (path == NULL || path[0] == '\0')
		return (NULL);

	copy = strdup(path);
	if (copy == NULL)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir != NULL)
	{
		full = malloc(strlen(dir) + strlen(command) + 2);
		if (full != NULL)
			break;
		sprintf(full, "%s/%s", dir, command);
		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}
		free(full);
			dir = strtok(NULL, ":");
	}
	free(copy);

	return (NULL);
}

