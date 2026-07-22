#include "main.h"

/**
* alloc_grid - allocates a 2D array of integers, initialized to 0
* @width: the number of columns in the grid
* @height: the number of rows in the grid
*
* Return: a pointer to the newly allocated 2D array, or NULL if
*         width or height is 0 or negative, or if malloc fails
*/
int **alloc_grid(int width, int height)
{
	int **grid;

	int i;

	int j;

	if (width <= 0 || height <= 0)
	{
		return (NULL);
	}
	grid = malloc(height * sizeof(int *));
	if (grid == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < height; i++)
	{
		grid[i] = malloc(width * sizeof(int));
		if (grid[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(grid[j]);
			}
			free(grid);
			return (NULL);
		}
	}
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			grid[i][j] = 0;
		}
	}
	return (grid);
}
