	#include <unistd.h>

/**
 * main - prints the message i will not give up
 * Return: Always 0
 */
int main(void)
{
	const char *message = "I will not give up";

	write(STDOUT_FILENO, message, sizeof(message));
	return (0);
}
