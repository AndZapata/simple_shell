#include "shell.h"

/**
 * fun_call - This functions is the medium betwen the prompt and ex_args
 * @buf: Buffer
 * @av: arguments recieved
 * @_args: arguments to tokenize
 * @env: Environment
 * @pat_str: structure with the path
 *
 * Return: Nothing
 */

void fun_call(char *buf, char **av, char **_args, char **env, paths_t *pat_str)
{
	if (!_strcmp(_args[0], "exit"))
		exit_func(buf, _args, pat_str);
	else
	{
		ex_arg(buf, av, _args, env, pat_str);
	}
}
