#include "main.h"

/**
 * my_atoi - converts string to int
 * @str: string to be converted
 * Return: converted integer
 */
int my_atoi(const char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	/** handle keading whitespaces */
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
	{
		i++;
	}

	/** handle sign if any */
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		i++;
	}

	/** convert remaining to int */
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return (result * sign);
}

/**
 * is_num - checks if the string is a valud number
 * @str: to be checked
 * Return: True if its a validd number
 */
bool my_is_num(const char *str)
{
	if (str == NULL || *str == '\0')
	{
		return (false);
	}

	if (*str == '+' || *str == '-')
	{
		str++;
	}

	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
		{
			return (false);
		}
		str++;
	}

	return (true);
}
