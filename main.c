#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * main - check the code
 *
 * Return: Success
 */
int main()
{
	char shell_prompt[] = "simple_shell$ ";

	char user_command[MAX_COMMAND_LENGTH];

	while (1)
	{
	int prompt_length = sizeof(shell_prompt) - 1;

	write(STDOUT_FILENO, shell_prompt, prompt_length);

	ssize_t bytes_read = read(STDIN_FILENO, user_command, sizeof(user_command));

	if (bytes_read <= 0)
	{
		/* end of file or error */
		break;
	}

	/* remove the newline character from the command */
	if (user_command[bytes_read - 1] == '\n')
	{
		user_command[bytes_read - 1] = '\0';
	}

	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		char fork_error[] = "Error: Fork failed\n";

		write(STDERR_FILENO, fork_error, sizeof(fork_error) - 1)
	}
	else if (child_pid == 0)
	{
		/* child process */
		char *args[] = { user_command, NULL };

		if (execve(user_command, args, NULL) == -1)
		{
			char exec_error[] = "Error: Executable not found\n";

			write(STDERR_FILENO, exec_error, sizeof(exec_error) - 1);
			_exit(EXIT_FAILURE);
		}
	} else
	{
		/* parent process */
		int status;

		waitpid(child_pid, &status, 0);
	}
	}
	return (0);
}

/**
 * append_text_to_file - specified text to end of file
 * @filename:pointer to the target file
 * text_content: sting to be added to end of file
 *
 * Return:
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int file_descriptor, write_result, text_length = 0;

	/*check if the filename is NULL */
	if (filename == NULL)
		return (-1);

	/* calculate the length */
	if (text_content != NULL)
	{
		while (text_content[text_length])
			text_length++;
	}

	/* open the file for writing in append mode */
	file_descriptor = open(filename, O_WRONLY | O_APPEND);

	write_result = write(file_descriptor, text_content, text_length)

		/* check for error during opening or writing */
		if (file_descriptor == -1 || write_result == -1)
			return (-1);

	close(file_descriptor);
	return (1);
}
