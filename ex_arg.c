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
	int execute, status = 0;
	pid_t tpid;
	char *token_text;
	/**
	 * Forkin a child
	 */
	token_text = _path(_args, path_str);
	tpid = fork();

	if (tpid == -1)
	{
		perror("Fork failed");
		free_list(path_str);
		free(buf);
		_exit(1);
	}
	else if (tpid == 0)
	{
		execute = execve(token_text, _args, env);
		if (execute < 0)
		{
			write(STDERR_FILENO, av[0], _strlen(av[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "1", 1);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, _args[0], _strlen(_args[0]));
			write(STDERR_FILENO, ": not found\n", 13);
			_exit(127);
		}
	}
	else
	{
		wait(&status);
		free(token_text);
	}
}
