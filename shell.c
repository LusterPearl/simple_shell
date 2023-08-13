#include "main.h"

/**
 * main - main entry point
 * @argc: argument count
 * @argv: argument vector
*/
int main(int argc, char argv)
{
	char *command = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILNO) && argc == 1)
			printf(PROMPT);
		command = read_command(&n);
		if (command == NULL)
		{
			free(command);
			continue;
		}
		if (strlen(command) == 1)
		{
			free(command);
			continue;
		}
		parse_command(command, &argv, &argc);
		free_argv(argv);
		free(command);
	}
	return (0);
}
