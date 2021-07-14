#include "ls.h"

/**
 * strcmp: Compare two strings to check if are equal.
 * @x: first string.
 * @y: second string.
 * Return: 0 if are equal, otherwise 1.
*/

int strcmp(const char *x, const char *y)
{
	while (*x)
	{
		if (*x != *y)
			return (1);
		x++;
		y++;
	}
	return (0);
}

/*
 * strchar: Check if the char is in the str.
 * @str: string.
 * @a: char to check.
 * Return: 0 if is there, 1 if not.
 */

int strchar(char *str, char a)
{
	while (*str)
	{
		if (*str == a)
			return (0);
		str++;
	}
	return (1);
}
