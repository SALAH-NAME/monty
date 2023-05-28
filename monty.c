#include "monty.h"

/**
 * main - the main function for monty script reader
 * @argc: nums of args
 * @argv: array of args
 * Return: exit 1 || 0
 */
int main(int argc, char **argv)
{
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	handle_file(argv[1], &stack);
	free_stack(&stack);
	exit(EXIT_SUCCESS);
}
