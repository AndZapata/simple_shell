#include "shell.h"
/**
 * _path - Check for the path
 * @_args: Path arguments to check
 * @path_str: Structure to keep the PATH
 *
 * Return: Nothing
 */
char *_path(char **_args, paths_t *path_str)
{
	char *ccat_slash = NULL, *ccat_args = NULL, *dup_path = NULL;
	char *keep;
	char sl[] = "/";
	struct stat buf;

	keep = _args[0];
	ccat_slash = str_concat(sl, keep);
	if (path_str == NULL)
		return (NULL);
	while (path_str != NULL)
	{
		if (path_str->path)
		{

			dup_path = _strdup(path_str->path);
			ccat_args = (str_concat(dup_path, ccat_slash));
			if (stat(ccat_args, &buf) == 0)
			{
				free(dup_path);
				free(ccat_slash);
				return (ccat_args);
			}
			path_str = path_str->next;
		}
		free(ccat_args);
		free(dup_path);
	}
	free(ccat_slash);
	return (_args[0]);
}
/**
 * _args_tokenized - Check for the path
 * @str: Path arguments to check
 * @_args: arguments obteined on stdin
 *
 * Return: Nothing
 */
void _args_tokenized(char *str, char **_args)
{
	const char delim[] = "=:;";
	char *keeper = NULL;
	int iter;

	keeper = strtok(str, delim);
	iter = 0;
	while (keeper)
	{
		_args[iter] = keeper;
		keeper = strtok(NULL, delim);
		iter++;
	}
	_args[iter] = NULL;
	free(keeper);
}
/**
 * _struct - Create an structure to keep the path
 * @head: Head of the linked list
 * @str: string received
 *
 * Return: a new node for the linked list
 */
paths_t *_struct(paths_t **head, char *str)
{
	paths_t *newnod = (paths_t *)malloc(sizeof(paths_t));

	if (!newnod)
		return (NULL);
	newnod->path = _strdup(str);
	if (!newnod->path)
	{
		free(newnod);
		return (NULL);
	}
	newnod->next = *head;
	*head = newnod;

	return (newnod);
}
/**
 * keeped_path - Check for the path keeped
 * @env: environment
 *
 * Return: Head
 */
paths_t *keeped_path(char **env)
{
	int i, j = 0, find_p, counter;
	char **dup_env, **strc = NULL;
	char *dup, *comp = "PATH";
	paths_t *head;

	dup_env = env;
	for (i = 0; dup_env[i] != NULL; i++)
	{
		counter = 0;
		for (j = 0; dup_env[i][j]; j++)
		{
			if (dup_env[i][j] == comp[j] && j < 4)
			{
				counter++;
				if (counter == 4 && j == 3)
					find_p = i;
			}
			else
				counter = 0;
		}
	}
	dup = dup_env[find_p];
	strc = malloc(sizeof(char *) * 1024);
	_args_tokenized(dup, strc);
	head = NULL;

	for (i = 0; strc[i]; i++)
		_struct(&head, strc[i]);
	i = 0;

	free(strc);
	return (head);
}
