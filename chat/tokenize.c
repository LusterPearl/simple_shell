#include "shell.h"

/**
 * tokenize_input - separates command line by spaces into words
 * @input: command line
 * @args: arguments
 */
void tokenize_input(char *input, char **args)
{
	int arg_count = 0;
	char *token = strtok(input, " ");

	while (token != NULL && arg_count < MAX_ARGS - 1)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}

	args[arg_count] = NULL;
}

