#include "main.h"
#include <ctype.h>

int my_space(const char *str)
{
	while (*str)
	{
		if (!isspace((unsigned char)*str))
			return (0);

		str++;
	}
	return (1);
}
