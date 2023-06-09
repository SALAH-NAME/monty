#include "monty.h"

int push_value;
/**
 * push - Pushes an element to the stack.
 * @stack: top of the stack.
 * @line_number: Line number of the instruction.
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *new = malloc(sizeof(stack_t));
	(void)line_number;

	if (!new)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	if (push_value == INT_MIN)
	{
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		free(new);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	new->n = push_value;
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
		{"sub",sub},
		{"div",_div},
		{"mul",mul},
		{"mod",mod},
		{NULL, NULL}
	};

	for (i = 0; instructions[i].opcode; i++)
	{
		if (strcmp(opcode, instructions[i].opcode) == 0)
		{
			instructions[i].f(stack, line_number);
			return;
		}
	}
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}

/**
 * handle_file - handles reading a file and calling match_opcode
 * @file_name: name of file to read from
 *
 * Return: void
 */
void handle_file(char *file_name, stack_t **stack)
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	size_t read;
	char *opcode;
	char *arg;
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

		arg = strtok(NULL, " \n\t\r");
		push_value = INT_MIN;
		if (arg != NULL && strcmp(opcode, "push") == 0)
			if (is_valid_int(arg))
				push_value = atoi(arg);

		match_opcode(opcode, stack, line_number);
	}

	free(line);
	fclose(fp);
}
/**
 * free_stack - free all stack
 * @stack: Top of the stack
 * Return: Nothing
 */
void free_stack(stack_t **stack)
{
	stack_t *temp;

	while (*stack)
	{
		temp = *stack;
		*stack = (*stack)->next;
		free(temp);
	}
}
