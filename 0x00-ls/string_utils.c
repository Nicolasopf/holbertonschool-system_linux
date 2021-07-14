#include "ls.h"

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
