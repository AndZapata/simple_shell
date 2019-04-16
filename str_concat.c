#include "shell.h"

/**
 * str_concat - concatenates two strings with memory allocation
 * @s1: First string to be concatenate
 * @s2: Second string to be concatenate
 *
 * Return: number the result of two oparations
 */
char *str_concat(char *s1, char *s2)
{
	int len, len1, len2, i;
	char *string;
	char *res;

	if (!s1)
		s1 = "";

	if (!s2)
		s2 = "";

	for (i = 0, len1 = 0; *(s1 + i); i++)
		len1++;

	for (i = 0, len2 = 0; *(s2 + i); i++)
		len2++;

	len = len1 + len2;

	string = malloc(len + 1);
	res = string;

	if (string == NULL)
		return (0);

	for (; *s1;)
		*string++ = *s1++;
	for (; *s2;)
		*string++ = *s2++;
	*string = '\0';
	return (res);
}
