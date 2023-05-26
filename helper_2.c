#include "monty.h"

/**
* pop - removes the top element of the stack.
* @stack: Top of the stack.
* @line_number: number of lines.
*
* Return: void.
*/
void pop(stack_t **stack, unsigned int line_number)
{
	if (!(*stack))
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->next)
	{
		(*stack)->next->prev = NULL;
	}
	(*stack) = (*stack)->next;
}

/**
* swap - swaps the top two elements of the stack.
* @stack: top of the stack.
* @line_number: number of lines.
*
* Return: void.
*/
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (!(*stack)  || (!(*stack)->next))
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	(*stack)->prev = temp;
	(*stack)->next = temp->next;
	if (temp->next)
		temp->next->prev = *stack;
	temp->prev = NULL;
	temp->next = *stack;
	*stack = temp;
}

/**
* add - adds the top two elements of the stack.
* @stack: top of the stack.
* @line_number: number of lines.
*
* Return:void.
*/
void add(stack_t **stack, unsigned int line_number)
{
	if (!(*stack) || (!(*stack)->next))
	{
		fprintf(stderr, "L%u: can't add an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->next->n += (*stack)->n;
	pop(stack, line_number);
}

/**
 * pint - prints the value at the top of the stack
 * @stack: top of the stack
 * @line_number: line number of the current operation
 *
 * Return: void
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!(*stack))
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * nop - doesn’t do anything
 * @stack: top of the stack
 * @line_number: line number of the current operation
 *
 * Return: void
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
