#include "_getline.h"

/**
 * _getline - return each line of the file descriptor.
 * @fd: file descriptor.
 * Return: one line for each call of _getline.
 */

char *_getline(const int fd)
{
	int counter = 0;
	static file_t *head;
	file_t *file_;
	char *last_buffer;

	if (fd == -1)
	{
		free_all(head);
		return (NULL);
	}

	file_ = search_node(head, fd);

	if (!file_)
		file_ = new_node(&head, fd);

	for (; file_->next_line[counter]; counter++)
		if (file_->next_line[counter] != '\n')
			break;

	if (!file_->next_line[0])
	{
		if (file_->next)
			head = file_->next;
		free(file_);
		return (NULL);
	}

	last_buffer = strndup(file_->next_line, counter);
	file_->next_line += counter + 1;
	return (last_buffer);
}

/**
 * search_node - search a node in the linked list.
 * @head: pointer to first node.
 * @fd: file descriptor num to search.
 * Return: the node found.
 */

file_t *search_node(file_t *head, const int fd)
{
	while (head && head->fd != fd)
		head = head->next;
	return (head);
}

/**
 * new_node - Adds a new node to the linked list.
 * @head: pointer to first node.
 * @fd: file descriptor num to search.
 * Return: the new node.
 */

file_t *new_node(file_t **head, const int fd)
{
	file_t *node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);

	memset(node->buff, '\0', READ_SIZE);
	node->fd = fd;
	read(fd, node->buff, READ_SIZE);
	node->next_line = node->buff;

	node->next = *head;
	*head = node;
	return (node);
}

/**
 * free_all - free the linked list
 * @head: pointer to the first node.
 */

void free_all(file_t *head)
{
	file_t *tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
