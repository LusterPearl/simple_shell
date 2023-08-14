#include "main.h"

/**
 * parae_command - splits commandkine into individual words
 * @command: command line
 * @argv: argument value
 * @argc: argument count
 */
 void parse_command(char *command, char ***argv, int *argc)
 {
	 const char *delim = " \n";
	 int t_count = 0, i = 0, j;
	 char *token, *command_copy = NULL;

	 /** alloxate soace for command copy */
	 command_copy = malloc(my_strlen(command) + 1);
	 if (command_copy == NULL)
	 {
		 perror("tsh: malloc error");
		 free(command_copy);
		 exit(-1);
	 }
	 my_strcpy(command_copy, command);
	 /** parsing **/
	 token = my_strtok(command, delim);
	 while (token != NULL)
	 {
		 t_count++;
		 token = my_strtok(NULL, delim);
	 }
	 t_count++;

	 *argv = malloc(sizeof(char *) * t_count);
	 token = my_strtok(command_copy, delim);
	 for (i = 0; token != NULL; i++)
	 {
		 (*argv)[i] = malloc(my_strlen(token) + 1);
		 if ((*argv)[i] == NULL)
		 {
			 perror("tsh: malloc error");
			 for (j = 0; j < i; j++)
			 {
				 free((*argv)[j]);
			 }
			 free(*argv);
			 free(command_copy);
			 exit(-1);
		 }
		 my_strcpy((*argv)[i], token);
		 token = my_strtok(NULL, delim);
	 }
/**	 for (j = 0; j < i; j++)
	 {
		 free((*argv)[j]);
	 }*/
	 /** (*argv)[i] = NULL; */
	 *argc = i;
	 free(command_copy);
	 command_copy = NULL;
}
