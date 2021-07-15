#include "ls.h"

/**
 * simple_ls - Print files as usually, no options.
 * @argc: Argument counter.
 * @argv: Argument vectors.
 * @options: Options passed.
 * Return: 0 if not errors, otherwise 2.
 */

int simple_ls(int argc, char *argv[], char *options)
{
	DIR *dir;
	int counter = 0, r_value = 0;
	char *files[1024], *not_files[1024];

	r_value = get_files(argc, argv, files, not_files);

	print_simple_files(files, options);

	for (counter = 0; not_files[counter]; counter++)
	{
		dir = opendir(not_files[counter]);

		if ((not_files[1] || files[0]) || counter != 0)
			printf("\n%s:\n", not_files[counter]);
		else if (argc != 2)
			printf("%s:\n", not_files[counter]);

		print_in(dir, options);
		closedir(dir);
	}

	return (r_value);
}

/**
 * get_files - separate the arguments in errors, files and dirs.
 * @argc: Argument counter.
 * @argv: Arguments vector.
 * @files: Where to save the files.
 * @not_files: Where to save the dirs.
 * Return: 0 if not errors, otherwise 2.
*/

int get_files(int argc, char *argv[], char **files, char **not_files)
{
	DIR *dir;
	int counter = 1, file_counter = 0, not_file_counter = 0;
	int r_value = 0;
	int passed_options = 0;

	for (; counter < argc; counter++)
	{
		if (*argv[counter] == '-')
		{
			passed_options++;
			continue;
		}

		dir = opendir(argv[counter]);
		if (!dir)
		{
			if (errno == ENOTDIR)
			{
				files[file_counter] = argv[counter];
				file_counter++;
			}
			else
				r_value = display_error(argv[0], argv[counter]);
			continue;
		}

		not_files[not_file_counter] = argv[counter];
		not_file_counter++;
		closedir(dir);
	}

	if (passed_options == argc - 1)
	{
		argv[1] = ".", argc++;
		not_files[not_file_counter] = ".";
		not_file_counter++;
	}
	files[file_counter] = '\0';
	not_files[not_file_counter] = '\0';
	return (r_value);
}

/**
 * print_in - print the folders.
 * @dir: directory.
 * @options: options passed.
*/

void print_in(DIR *dir, char *options)
{
	int any = 0;
	char separator[2] = {'\0'};
	struct dirent *read;

	if (strchar(options, '1') == 0)
	{
		separator[0] = '\n';
		separator[1] = '\0';
	}
	else
	{
		separator[0] = ' ';
		separator[1] = ' ';
		separator[2] = '\0';
	}

	while ((read = readdir(dir)) != NULL)
	{
		if (*read->d_name == '.')
			continue;
		if (any)
			printf("%s", separator);
		printf("%s", read->d_name);
		any = 1;
	}
	if (any == 1)
		printf("\n");
}

/**
 * print_simple_files - print the files by a separator.
 * @files: file names.
 * @options: options passed to print.
*/

void print_simple_files(char **files, char *options)
{
	int counter = 0;
	char separator[2] = {'\0'};

	if (strchar(options, '1') == 0)
	{
		separator[0] = '\n';
		separator[1] = '\0';
	}
	else
	{
		separator[0] = ' ';
		separator[1] = ' ';
		separator[2] = '\0';
	}

	for (; files[counter]; counter++)
		if (files[counter + 1])
			printf("%s%s", files[counter], separator);
		else
			printf("%s\n", files[counter]);
}
