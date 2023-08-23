#include "shell.h"

/**
 * start_shell - prints prompt and initiaytes shell functions
 * @argc: arg c
 * Retunrn : void
 */
void start_shell(int argc)
{
	char *args[MAX_ARGS], *input;

	while (1)
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
			printf(PROMPT);

		input = read_input();
		if (input == NULL) /** End of file */
			break;

		process_input(input);

		tokenize_input(input, args);
		if (args[0] != NULL)
			execute_command(args);

		free (input);
	}
}
