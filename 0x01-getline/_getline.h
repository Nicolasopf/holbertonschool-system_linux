#ifndef _GET_LINE_H
#define _GET_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define READ_SIZE 40960

/**
 * struct file_n - file linked list.
 * @fd: file descriptor.
 * @next_line: pointer to the next line.
 * @buff: buffer of all lines.
 * @next: pointer to next node.
 */
typedef struct file_n
{
	int fd;
	char *next_line;
	char buff[READ_SIZE];
	struct file_n *next;
} file_t;

char *_getline(const int fd);
void free_all(file_t *head);
file_t *new_node(file_t **head, const int fd);
file_t *search_node(file_t *head, const int fd);


#endif /* _GET_LINE_H */
