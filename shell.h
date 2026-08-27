#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define DELIM " \t\r\n\a"

extern char **environ;

/* Function prototypes */
char *read_line(void);
char **split_line(char *line);
int execute_cmd(char **args, char *prog_name);
void free_args(char **args);
char *_getenv(const char *name);
char *find_path(char *command);

#endif /* SHELL_H */
