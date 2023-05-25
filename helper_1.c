#include "main.h"

/**
 * push - Pushes an element to the stack.
 * @stack: top of the stack.
 * @line_number: Line number of the instruction.
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new = malloc(sizeof(stack_t));

	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new->n = line_number;
	new->prev = NULL;
	new->next = *stack;
	if (*stack)
		(*stack)->prev = new;
	*stack = new;
}

/**
 * pall - Prints all the values on the stack.
 * @stack: Pointer to the top of the stack.
 * @line_number: Line number of the instruction.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	(void)line_number;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * match_opcode - matches an opcode with its corresponding function
 * @opcode: opcode to match
 * @stack: top of the stack
 * @line_number: line number of the current operation
 *
 * Return: void
 */
void match_opcode(char *opcode, stack_t **stack, unsigned int line_number)
{
	int i;
	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{"pint", pint},
		{NULL, NULL}
	};

	for (i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			break;
		}
	}
}

/**
 * handle_file - handles reading a file and calling match_opcode
 * @file_name: name of file to read from
 *
 * Return: void
 */
void handle_file(char *file_name)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	size_t read;
	char *opcode;
	stack_t *stack = NULL;
	unsigned int line_number = 0;

	fp = fopen(file_name, "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", file_name);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, fp)) != (size_t)-1)
	{
		line_number++;
		opcode = strtok(line, " \n\t\r");
		if (!opcode || strncmp(opcode, "#", 1) == 0)
			continue;

		match_opcode(opcode, &stack, line_number);
	}

	free(line);
	fclose(fp);
}
