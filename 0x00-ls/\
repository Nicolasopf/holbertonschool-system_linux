#include "ls.h"

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *read;
	int counter = 1;

	if (argc == 1)
		{
			argv[1] = ".";
			argc++;
		}

	for (; counter < argc; counter++)
	{
		dir = opendir(argv[counter]);
		if (!dir)
		{
			return (display_error(argv[0], argv[counter]));
		}
		while ((read = readdir(dir)) != NULL)
		{
			if ((strcmp(read->d_name, ".") == 0) || (strcmp(read->d_name, "..") == 0))
				continue;
			printf("%s  ", read->d_name);
		}
		printf("\n");
		closedir(dir);
	}
	return (0);
}

int display_error(char *name, char *dir_name)
{
	char str[1024];

	switch (errno)
	{
		case EACCES:
			sprintf(str, "%s: cannot access %s", name, dir_name);
			perror(str);
			break;
		case EBADF:
			sprintf(str, "%s: cannot access %s", name, dir_name);
			perror(str);
			break;
		case ENOENT:
			sprintf(str, "%s: No such file or directory%s", name, dir_name);
			perror(str);
	}
	return (2);
}
