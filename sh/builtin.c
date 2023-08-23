#include "main.h"

/**
 * handle_exit - habdles wxit
 * @arg: number to exit wirh
 * Return: void
 */
int handle_exit(char *arg)
{
	int exit_status;
	char *error_msg = "./hsh: 1: exit: Illegal number: ";

	if (arg == NULL)
	{
		exit(0);
	}
	else if ((my_atoi(arg)) < 0)
	{
		dprintf(STDERR_FILENO, "%s%s\n", error_msg, arg);
		exit_status = 2;
	}
	else if ((arg != NULL) && my_is_num(arg))
	{
		exit_status = my_atoi(arg);
	}
	else
	{
		dprintf(STDERR_FILENO, "%s%s\n", error_msg, arg);

		exit_status = 2;
	}
	return (exit_status);
}
