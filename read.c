#include "main.h"

/**
 * read_command - reads command
 * @n: counter
 * Retrun: pointer to array of command
 */
char *read_command(size_t *n)
{
	ssize_t ncommand_read;
	char *command = NULL;

	ncommand_read = getline(&command, n, stdin);

	/** failure check */
	if (ncommand_read == -1)
	{
		if (feof(stdin))
		{
			free(command);
			return (NULL);
		}
		perror("getline error");
		free(command);
		exit(EXIT_FAILURE);
	}

	if (ncommand_read > 0 && command[ncommand_read - 1] == '\n')
	{
		command[ncommand_read - 1] = '\0';
	}

	if (ncommand_read == 1 && command[0] == '\0')
	{
		free(command);
		return (NULL);
	}

	return (command);
}
