#include "main.h"

/**
 * fetch_parh - finds the full path of the command
 * @command: we are to find the oath for this
 * @directories: array of directories to search for command
 * Return: the full path or NULL if not found
 */
char *fetch_path(char *command, char **directories)
{
	char *full_path = NULL;
	char *c;

	bool is_full_path = false;
	for (c = command; *c != '\0'; c++)
	{
		if (*c == '/')
		{
			is_full_path = true;
			break;
		}
	}
	if (is_full_path)
	{
		full_path = strdup(command);
		return (full_path);
	}
	else
	{
		return (find_full_path(command, directories));
	}
}

/**
 * find_full_path - find the full path for non-path
 * @command: we are to fins the oath for this
 * @directories: arrat to search commands in
 * Return: fill path
 */
 char *find_full_path(char *command, char **directories)
 {
	size_t path_length, command_length;
	char *full_path = NULL;

	while (*directories != NULL)
	 {
		path_length = my_strlen(*directories);
		command_length = my_strlen(command);
		full_path = (char *)malloc(path_length + 1 + command_length + 1);

		/** +2 for / ans NULL terminator */
		if (full_path == NULL)
		{
			perror("malloc error");
			exit(EXIT_FAILURE);
		}

		my_strcpy(full_path, *directories);
		/** adding separator */
		full_path[path_length] = '/';
		my_strcpy(full_path + path_length + 1, command);

		 if (access(full_path, X_OK) == 0)
		{
			return (full_path);
		}
		free(full_path);
		directories++;
 	}

 	return (NULL);
}
		
