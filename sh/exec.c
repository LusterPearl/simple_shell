#include "main.h"

/**
 * execute_final_command - completes exec command
 * @argv: command
 * @directories: directory of commands
 * Returns: always 0
 */
int execute_final_command(char **argv, char **directories)
{
	char *real_command = fetch_path(argv[0], directories);
	pid_t pid;
	int status, exit_status;
	int signal_number;

	if (real_command == NULL)
		return (127);
	
	/** moving in */
	pid = fork();

	if (pid < 0)
	{
		/** error with forking */
		perror("Fork wrror");
		exit(2);
	}
	else if (pid == 0)
	{
		/** child process - exec command */
		execvp(real_command, argv);
		/** execve returnung means error occured */
		perror("execve error");
		/** avoid at exit handlers by using _exit */
		exit(2);
	}

	else
	{
		/** parent waits for child ri complete */
		wait(&status);

		/** check for abnormal termination of child pricess */
		if (WIFSIGNALED(status))
		{
			signal_number = WTERMSIG(status);
			printf("command terminated by signal: %d\n", signal_number);
		}

		exit_status = WEXITSTATUS(status);
		if (exit_status != 0)
			exit(exit_status);
	}
	free(real_command);
	return (exit_status);
}

/**
 * exeucute_command - executes command passed by argv
 * @argv: argument calue
 * @directories: directory of commands
 * Return: 0 if successful
 */
int execute_command(char **argv, char **directories)
{
	char *real_command = fetch_path(argv[0], directories);
	int is_exit, is_env, cmd_exit_status;
	char *exit_string = "exit", *env_string = "env";

	/** check if command is NULL */
	if (argv == NULL || argv[0] == NULL)
	{
		printf("Nullll");
		return (0);
	}

	/** chec if command is exit */
	is_exit = my_strcmp(argv[0], exit_string);
	if (is_exit == 0)
	{
		free(real_command);
		cmd_exit_status = handle_exit(argv[1]);
		return (cmd_exit_status);
	}
	is_env = my_strcmp(argv[0], env_string);
	if (is_env == 0)
	{
		/** print the currenr wnviron */
		print_env();
		free(real_command);
		return (0);
	}

	/** check of command does not exits */
	if (real_command == NULL)
	{
		dprintf(STDERR_FILENO, "./hsh: 1: %s: command not found\n", argv[0]);
		free(real_command);
		return (1);
	}

	cmd_exit_status = execute_final_command(argv, directories);
	free(real_command);
	return (cmd_exit_status);
}
