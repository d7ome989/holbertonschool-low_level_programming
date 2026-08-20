#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * copy_file - copies content from one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @from: source file name
 * @to: destination file name
 *
 * Return: 0 on success, 98 on read error, 99 on write error
 */
int copy_file(int fd_from, int fd_to, char *from, char *to)
{
	char buffer[1024];
	int r, w, total;

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
					"Error: Can't write to %s\n", to);
				return (99);
			}
			total += w;
		}
		r = read(fd_from, buffer, 1024);
	}
	if (r == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", from);
		return (98);
	}
	return (0);
}

/**
 * close_file - closes a file descriptor
 * @fd: file descriptor
 *
 * Return: 0 on success, 100 on failure
 */
int close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd);
		return (100);
	}
	return (0);
}

/**
 * main - copies the content of a file to another file
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to, result;

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
		close_file(fd_from);
		return (99);
	}
	result = copy_file(fd_from, fd_to, argv[1], argv[2]);
	if (result != 0)
	{
		close_file(fd_from);
		close_file(fd_to);
		return (result);
	}
	result = close_file(fd_from);
	if (result != 0)
	{
		close_file(fd_to);
		return (result);
	}
	return (close_file(fd_to));
}
