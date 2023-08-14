#include "main.h"

/**
 * print_env - prints environment
 * Return: void
 */
void print_env(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
