#include "shell.h"

/**
 * execute_command - executes command
 * @args: array of commands
 * Return: Always 0
 */
void execute_command(char **args)
{
	int status;

	if (args)
	{
		pid_t child_pid = fork();

		if (child_pid == -1)
			perror("fork");
		else if (child_pid == 0)
		{
			/** child process */
			if (execvp(args[0], args) == -1)
			{
				char error_message[100];
				snprintf(error_message, sizeof(error_message), "./hsh: %d: %s: not found\n", 1, args[0]);
				write(STDERR_FILENO, error_message, strlen(error_message));
				exit(127);
			}
		}
		else
			waitpid(child_pid, &status, 0);
	}
}
