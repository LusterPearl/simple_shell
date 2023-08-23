#include "shell.h"

/**
 * process_input - prepares input for exeecutuon
 * @input: the input
 * Return: void
 */
void process_input(char *input)
{
	input[strcspn(input, "/n")] = '\0';
}

/**
 * read_input - reads input 
 */
char *read_input()
{
	char *input;

	input = (char *)malloc(MAX_INPUT_LENGTH * sizeof(char));
	if (!input)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}

	if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
	{
		free(input);
		return (NULL);
	}

	return (input);
}
