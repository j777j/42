#include "minilibx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	void *mlx;
	void *img;
	int w;
	int h;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("mlx_init() failed\n");
		return (1);
	}
	printf("mlx_init() succeeded\n");

	img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &w, &h);
	if (!img)
	{
		printf("mlx_xpm_file_to_image() failed\n");
		return (1);
	}
	printf("mlx_xpm_file_to_image() succeeded\n");

	return (0);
}
