#include "ls.h"

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
	int counter = 0, r_value = 0, any = 0;
	char *files[1024];
	char *not_files[1024];

	if (argc == 1)
		argv[1] = ".", argc++;

	r_value = get_files(argc, argv, files, not_files);

	for (; files[counter]; counter++)
		if (files[counter + 1])
			printf("%s  ", files[counter]);
		else
			printf("%s\n", files[counter]);

	for (counter = 0; not_files[counter]; counter++)
	{
		dir = opendir(not_files[counter]);

		if ((not_files[1] || files[0]) && counter != 0)
			printf("\n%s:\n", not_files[counter]);
		else if (argc != 2)
			printf("%s:\n", not_files[counter]);

		while ((read = readdir(dir)) != NULL)
		{
			if (*read->d_name == '.')
				continue;
			printf("%s  ", read->d_name);
			any = 1;
		}
		if (any == 1)
			printf("\n");
		any = 0;
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

	for (; counter < argc; counter++)
	{
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

	files[file_counter] = '\0';
	not_files[not_file_counter] = '\0';
	return (r_value);
}
