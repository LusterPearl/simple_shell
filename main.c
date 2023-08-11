#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* signal handler function for interrupt signal */
void sig_handler(int signal);
/* execute a command within a child process */
int execute(char **args, char **front);

/**
 * signal_handler - Responds to an interrupt signal by displaying
 * a new prompt
 * sig: The signal identifier
 */
void sig_handler(int signal)
{
	char *new_prompt = "\n$ ";

	/* ignore the signal parameter to prevent complier warnings */
	(void)signal;

	/* reassign the signal handler for SIGNIT */
	signal(SIGINT, sig_handler);

	/* write the new prompt to the standard output */
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - launches a command in a child process
 * @args: an array containig the command and its arguments
 * @front: a double pointer indicating the start of an args
 * Return: if an error happens - a relevant error code
 * otherwise - the exit status of the most recently executed command
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	/* check if the command is not an absolute or relative path */
	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	/* check if the command exists ad is accessible */
	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(args, 126));
		else
			ret = (create_error(args, 127));
	}
	else
	{
		/* create a child process using fork */
		child_pid = fork();

		/* handle a fork error */
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			print_error("Error creating child process:");
			return (1);
		}

		/* if this is the child process */
		if (child_pid == 0)
		{

			/* execute a command within the child process */
		       execve(command, args, environ);

		       /* handle an access error */
		       if (errno == EACCES)
			       ret = (creat_error(args, 126));

		       /* clean up resources and exit the child process */
		       free_env();
		       free_args(args, front);
		       free_alias_list(aliases);
		       _exit(ret);
		}
		/* if this is the parent process */
		else
		{
			/* wait for the child process to complete and exit */
			wait(&status);
			ret = retrieve_exit_status(status);
		}
	}

	/* clean up resources if necessary and return the result */
	if (flag)
		free(command);
	return (ret);
}

/**
* main - initiates a basic UNIX command inerpreter
* @argc: the count of program arguments
* @argv: an array of pointers to the progtam arguments
* Return: the exit status of the last executed command
*/
int main(int argc, char *argv[])
{
		int ret = 0, retn;
		int *exe_ret = &retn;
		char *prompt = "$ ", *new_line = "\n";

		/* set the program name and initialize variable */
		name = argv[0];
		history_count = 1;
		aliases = NULL;
		signal(SIGINT, sig_handler);

		/* initialize the exit status pointer and copy the environment */
		*exe_ret = 0;
		environ = _copyenv();
		if (!environ)
			exit(-100);

		/* if program arguments are provided */
		if (argc != 1)
		{
			/* process commands from a file and set the exit status */
			ret = proc_file_commands(argv[1], exe_ret);
			free_env();
			free_alias_list(aliases);
			return (*exe_ret);
		}

		/* if the standard input is not a terminal */
		if (!isatty(STDIN_FILENO))
		{
			/* continously handle commands until end of file or exit */
			while (ret != END_OF_FILE && ret != EXIT)
				ret = handle_args(exe_ret);
			free_env();
			free_alias_list(aliases);
			return (*exe_ret);
		}
		 /* if interacting with a terminal, continuously prompt and handle cmds */
		while (1)
		{
			write(STDOUT_FILENO, prompt, 2);
			ret = handle_args(exe_ret);
			if (ret == END_OF_FILE || ret == EXIT)
			{
				if (ret == END_OF_FILE)
					write(STDOUT_FILENO, new_line, 1);
				free_env();
				free_alias_list(aliases);
				exit(*exe_ret);
			}
		}
		/* clean up resources and return the exit status */
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
}
