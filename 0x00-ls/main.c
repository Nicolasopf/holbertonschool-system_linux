#include "ls.h"

/**
 * main - entry point.
 * @argc: argument counter.
 * @argv: argument vectors.
 * Return: 0 if ok, otherwise 2.
*/

int main(int argc, char *argv[])
{
	char options[1024];
	/* char *file_arguments[1024]; */

	options[0] = '\0';
	check_arguments(argc, argv, options);

	if (argc == 1 || !options[0])
		return (simple_ls(argc, argv));

	return (0);
}

/**
 * check_arguments - Check the arguments passed in argv to get the options.
 * @argc: argument counter.
 * @argv: argument vector.
 * @options: pointer where to save the options to use.
 * Return: 0.
 */

int check_arguments(int argc, char *argv[], char *options)
{
	int counter = 1, char_counter = 0, delim = 1;

	for (; counter < argc; counter++)
		if (*argv[counter] == '-')
		{
			for (; argv[counter][delim] && argv[counter][delim] != ' '; delim++)
			{
				if (strchar(options, argv[counter][delim]) == 1)
				{
					options[char_counter] = argv[counter][delim];
					char_counter++;
				}
				(*argv[counter])++;
			}
			delim = 1;
		}

	options[char_counter] = '\0';
	return (0);
}

/**
 * simple_ls - Print files as usually, no options.
 * @argc: Argument counter.
 * @argv: Argument vectors.
 * Return: 0 if not errors, otherwise 2.
 */

int simple_ls(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *read;
	int counter = 1, r_value = 0;

	if (argc == 1)
		argv[1] = ".", argc++;

	for (; counter < argc; counter++)
	{
		dir = opendir(argv[counter]);

		if (!dir)
		{
			r_value = display_error(argv[0], argv[counter]);
			continue;
		}
		if (argc > 2)
			printf("%s:\n", argv[counter]);

		while ((read = readdir(dir)) != NULL)
		{
			if (*read->d_name == '.')
				continue;
			printf("%s  ", read->d_name);
		}

		if (argc > 2 && counter != argc - 1)
			printf("\n");

		printf("\n");
		closedir(dir);
	}
	return (r_value);
}

/**
 * display_error - Display an error.
 * @name: Program name.
 * @dir_name: Name of directory.
 * Return: 2.
 */

int display_error(char *name, char *dir_name)
{
	char str[1024];

	sprintf(str, "%s: cannot access %s", name, dir_name);
	perror(str);
	return (2);
}
