#include "main.h"

/**
 * my_strlen - counts the length of a string
 * @str: strings to be counted
 * Return: length of string
 */
size_t my_strlen(const char *str)
{
	size_t length = 0;

	while (*str++)
		length++;

	return (length);
}

/**
 * my_strcpy - copies a string into another
 * @dest: array to gw copied from
 * @src: atraybto he copied to
 * Return: pointer to copied array
 */
char *my_strcpy(char *dest, const char *src)
{
	char *dest_start = dest;

	while ((*dest++ = *src++))
		;

	return (dest_start);
}

/**
 * my_strcmp - compares two strings
 * @str1: first strung to he compared
 * @str2: second strung to be compared
 * Return: 0 if equal, -ve if str1 is less, +ve if str1 is greater
 */
int my_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return ((int)(*str1) - (int)(*str2));
}

/**
 * my_strchr - searches for a character in a string
 * @str: string
 * @ch: character
 * Return: pointer to the first occurence of the character or NULL if not found
 */
char *my_strchr(const char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == (char)ch)
		{
			return (char *)str;
			/** found the character: return its address */
		}
		str++;
	}

	/** check if char is a null terminator */
	if (ch == '\0')
	{
		return (char *)str;
	}
	/** character not found */
	return (NULL);
}

/**
 * my_strtok - splits strings into tokens
 * @str: string to be tokenized
 * @delin: set of delinitter characters
 * Return: pointer to the nwxt token
 */
char *my_strtok(char *str, const char *delim)
{
	static char *next_token = NULL;
	char *token;

	if (str != NULL)
	{
		/** start fron beginning of strung */
		next_token = str;
	}
	/** check if we reached end of strung */
	if (next_token == NULL || *next_token == '\0')
	{
		return (NULL);
	}
	/** skip leading delimitters */
	while (*next_token != '\0' && my_strchr(delim, *next_token) != NULL)
	{
		next_token++;
	}
	/** did we reach the end of string after skipping delimitters */
	if (*next_token == '\0')
	{
		return (NULL);
	}
	/** find the end of token */
	token = next_token;
	while (*next_token != '\0' && my_strchr(delim, *next_token) == NULL)
	{
		next_token++;
	}
	/** if delimitter not found, replace it with null and mive to next */
	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}

	return (token);
}
