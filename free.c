#include "main.h"

/**
 * free_argv - frees memory
 * @argv: argument value
 * @argc: argument count
 * Return: always 0
 */
void free_argv(char **argv, int argc)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		free(argv[i]);
	}
	free(argv);
}
