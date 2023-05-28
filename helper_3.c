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
		if (str[i] < '0' || str[i] > '9')
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/**
 * sub - subs the top two elements of the stack.
 * @stack: top of the stack.
 * @line_number: number of lines.
 *
 * Return:void.
 */
void sub(stack_t **stack, unsigned int line_number)
{
	if (!(*stack) || !((*stack)->next))
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n -= (*stack)->n;
	pop(stack, line_number);
}
