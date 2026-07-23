#include "main.h"

/**
* free_grid - frees a 2D grid previously allocated by alloc_grid
* @grid: the 2D grid to free
* @height: the number of rows in the grid
*
* Return: nothing
*/
void free_grid(int **grid, int height)
{
	int i;

	for (i = 0; i < height; i++)
	{
		free(grid[i]);
	}
	free(grid);
}
