#ifndef __MAIN__
#define __MAIN__

#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define PROMPT "($) "
#define BUFFER_SIZE 1024

extern char **environ;

/** strings.c */
size_t my_strlen(const char *str);
char *my_strcpy(char *dest, const char *src);
char *my_strchr(const char *str, int ch);
int my_strcmp(const char *str1, const char *str2);
char *my_strtok(char *str, const char *delim);

/** strings2.c */
int my_space(const char *str);

/** strint.c */
int my_atoi(const char *str);
bool my_is_num(const char *str);

/** read.c */
char *read_command(size_t *n);

/** parse.c */
void parse_command(char *command, char ***argv, int *argc);

/** exec.c */
int execute_command(char **argv, char **directories);
int execute_final_commaand(char **argv, char **directories);

/** path.c */
char *fetch_path(char *command, char **directories);
char *find_full_path(char *command, char **directories);

/** free.c */
void free_argv(char **argv, int argc);

/** env.c */
void print_env(void);

/** builtin.c */
int handle_exit(char *arg);

#endif
