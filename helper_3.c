#include "monty.h"

/**
 * is_valid_int - check if the push had a valide arg
 * @str: the string after push
 * Return: SUCCESS or FAILURE
 */

int is_valid_int(char *str)
{
	int i;

	if (!str)
		return (EXIT_SUCCESS);
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	else
		i = 0;

	for (; str[i]; i++)
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
