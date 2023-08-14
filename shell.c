#include "main.h"

/**
 * main - main entry point
 * @argc: argument count
 * @argv: argument vector
*/
int main(int argc, char **argv)
{
	size_t n = 0;
	char *command = NULL, *directories[] = {
		"/home/use/bin", "use/local/bin", "usr/bin", "/bin", NULL};
	int exit_status;

	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
			printf(PROMPT);
		command = read_command(&n);
		if (command == NULL)
		{
			if (feof(stdin))
			{
				free(command);
				break;
			}
			free(command);
			continue;
		}
		if (strlen(command) == 1)
		{
			free(command);
			continue;
		}
		parse_command(command, &argv, &argc);
		exit_status = execute_command(argv, directories);
		if (my_strcmp(argv[0], "exit") == 0)
		{
			free_argv(argv, argc);
			free(command);
			exit(exit_status);
		}
		free_argv(argv, argc);
		free(command);
		(void)exit_status;
	}
	free(command);
	return (0);
}
