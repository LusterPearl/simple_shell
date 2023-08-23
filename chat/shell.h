#ifndef __SHELL__
#define __SHELL__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/** Macros */
#define PROMPT "$ "
#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 10

/** Shell */
void start_shell(int argc);
void process_input(char *input);
char *read_input();
void tokenize_input(char *input, char **args);
void execute_command(char **args);

/** Strings */

#endif 
