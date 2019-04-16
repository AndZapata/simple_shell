#include "shell.h"
/**
 * ex_arg - Function to execute process to child process
 * @buf: buffer
 * @av: Arguments received on prompt.
 * @_args: Arguments tokenized.
 * @env: Environment.
 * @path_str:
 *
 * Return: No returns in this function
 */
void ex_arg(char *buf, char **av, char **_args, char **env, paths_t *path_str)
{
	int status = 0;
	pid_t tpid, pid;
	char *token_text;

	(void)argv;
	tpid = fork();
	if (tpid == 0)
	{
		token_text = _path(_args, path_str);
		if (execve(token_text, _args, env) == -1)
		{
			write(STDERR_FILENO, av[0], _strlen(av[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "1", 1);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, token_text, _strlen(token_text));
			write(STDERR_FILENO, ": not found\n", 13);
			free(buffer);
			free_list(path_str);
		}
		exit(0);
	}
	else
	{
		do {
			tpid = wait(&status);
		} while (tpid != pid);
	}
	free(buffer);
}
