#include "_getline.h"

#define READ_SIZE 409600

/**
 * _getline - return each line of the file descriptor.
 * @fd: file descriptor.
 * Return: one line for each call of _getline.
 */

char *_getline(const int fd)
{
	int counter = 0;
	static char *next_line, buff[READ_SIZE] = {'\0'};
	char *last_buffer;

	if (!*buff)
		read(fd, buff, READ_SIZE), next_line = buff;

	for (; next_line[counter] && next_line[counter] != '\n'; counter++)
	{}

	if (!*next_line)
		return (NULL);

	last_buffer = strndup(next_line, counter);
	last_buffer[counter] = '\0';
	next_line += counter + 1;
	return (last_buffer);
}
