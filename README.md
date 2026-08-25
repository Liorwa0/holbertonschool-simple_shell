# Simple Shell Project (hsh)

A simple UNIX command line interpreter implemented in C as part of the Holberton School curriculum.

## Description
`hsh` is a minimalistic shell that mimics the basic behavior of `/bin/sh`. It can execute external system commands by locating them via the `PATH` environment variable or direct paths, handles interactive and non-interactive execution modes, and manages process execution using system calls like `fork`, `execve`, and `wait`.

## Features
- Interactive and Non-interactive modes
- Command execution with arguments
- Path resolution via `PATH`
- Handling `EOF` (Ctrl+D)
- Built-in commands: `exit`, `env`

## Compilation
Compile all `.c` files using `gcc`:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
