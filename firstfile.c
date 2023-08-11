#include <unistd.h>

/**
 * main - prints the message i will not give up
 * Return: Always 0
 */
int main(void)
{
	const char *message = ("I will not give up\n");

	write(STDOUT_FILENO, message, izeof(message) - 1);
	return (0);
}
