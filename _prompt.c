#include "shell.h"

/**
 * _sigint - Function to anulate the ^C
 * @do_not: An integer that do nothing
 *
 * Return: No returns in this function
 */

void _sigint(int do_not)
{
	(void)do_not;
	write(STDOUT_FILENO, "$ ", _strlen("$ "));
	/*clean the standard out*/
	fflush(stdout);
}

/**
 * _prompt - Function to open a prompt for shell
 * @av: Received arguments
 * @env: Find the environment
 *
 * Return: No returns in this function
 */

void _prompt(char **av, char *env[])
{
	char *_args[1024], *buf;
	size_t num_bs = 32;
	paths_t *path_str;

	path_str = keeped_path(env);
	signal(SIGINT, _sigint);
	while (1)
	{
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", _strlen("$ "));
		buf = malloc(sizeof(char) * num_bs);
		if (getline(&buf, &num_bs, stdin) != EOF)
		{
			if (buf[0] != '\n' && buf[0])
			{
				tokenized_text(buf, _args);
				fun_call(buf, av, _args, env, path_str);
			}
			else
			{
				free(buf);
				continue;
			}
		}
		else
		{
			free_list(path_str);
			free(buf);
			break;
		}
	}
}
