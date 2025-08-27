#include "cub3d.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct s_vars {
	void	*mlx;
	void	*win;
}t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_map	map;

	if (argc != 2)
	{


		printf("Error: Invalid number of arguments\n");
		return (1);
	}
	if (parse_map(argv[1], &map))
	{
		printf("Error: Failed to parse map\n");
		return (1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}