#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to;
	int r, w;
	int close_from, close_to;
	int total;
	char buffer[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		return (97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		return (98);
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", argv[2]);
		if (close(fd_from) == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't close fd %d\n", fd_from);
			return (100);
		}
		return (99);
	}

	r = read(fd_from, buffer, 1024);

	while (r > 0)
	{
		total = 0;

		while (total < r)
		{
			w = write(fd_to, buffer + total, r - total);

			if (w == -1)
			{
				dprintf(STDERR_FILENO,
					"Error: Can't write to %s\n", argv[2]);
				close(fd_from);
				close(fd_to);
				return (99);
			}

			total += w;
		}

		r = read(fd_from, buffer, 1024);
	}

	if (r == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		close(fd_from);
		close(fd_to);
		return (98);
	}

	close_from = close(fd_from);
	if (close_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_from);
		return (100);
	}

	close_to = close(fd_to);
	if (close_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_to);
		return (100);
	}

	return (0);
}
