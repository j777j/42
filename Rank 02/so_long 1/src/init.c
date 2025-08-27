/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 07:00:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game, char *map_file)
{
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->collectibles = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->moves = 0;
	load_map(game, map_file);
	check_map(game);
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("Error: mlx_init failed\n");
		exit_game(game, 1);
	}
	game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, game->height
			* TILE_SIZE, "so_long");
	if (!game->win)
	{
		ft_printf("Error: mlx_new_window failed\n");
		exit_game(game, 1);
	}
}

void	load_sprites(t_game *game)
{
	int	w;
	int	h;

	game->wall.ptr = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &w,
			&h);
	if (!game->wall.ptr)
	{
		ft_printf("Error: Failed to load wall texture\n");
		exit_game(game, 1);
	}
	game->floor.ptr = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&w, &h);
	if (!game->floor.ptr)
	{
		ft_printf("Error: Failed to load floor texture\n");
		exit_game(game, 1);
	}
	game->collectible.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &w, &h);
	if (!game->collectible.ptr)
	{
		ft_printf("Error: Failed to load collectible texture\n");
		exit_game(game, 1);
	}
	game->exit.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_closed.xpm", &w, &h);
	if (!game->exit.ptr)
	{
		ft_printf("Error: Failed to load exit_closed texture\n");
		exit_game(game, 1);
	}
	game->exit_open.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_open.xpm", &w, &h);
	if (!game->exit_open.ptr)
	{
		ft_printf("Error: Failed to load exit_open texture\n");
		exit_game(game, 1);
	}
	game->player.ptr = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&w, &h);
	if (!game->player.ptr)
	{
		ft_printf("Error: Failed to load player texture\n");
		exit_game(game, 1);
	}
}
