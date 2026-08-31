cat << 'EOF' > free_args.c
#include "shell.h"

/**
 * free_args - Frees an array of strings
 * @args: Null-terminated array of strings to free
 */
void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
EOF
