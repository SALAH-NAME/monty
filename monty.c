#include "monty.h"

/**
 * main - the main function for monty script reader
 * @argc: nums of args
 * @argv: array of args
 * Return: exit 1 || 0
 */
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	handle_file(argv[1]);

	exit(EXIT_SUCCESS);
}
