/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/19 00:00:00 by juwang           ###   ########.fr       */
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
	game->enemies = NULL;
	game->enemy_count = 0;
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

	game->wall.ptr = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&w, &h);
	game->floor.ptr = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
			&w, &h);
	game->collectible.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &w, &h);
	game->exit.ptr = mlx_xpm_file_to_image(game->mlx, "textures/exit_closed.xpm",
			&w, &h);
	game->exit_open.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_open.xpm", &w, &h);
	game->player[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &w, &h);
	game->player[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player2.xpm", &w, &h);
	game->player[2].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player3.xpm", &w, &h);
	game->patrol[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/patrol.xpm", &w, &h);
	game->patrol[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/patrol2.xpm", &w, &h);
	if (!game->wall.ptr || !game->floor.ptr || !game->collectible.ptr
		|| !game->exit.ptr || !game->exit_open.ptr || !game->player[0].ptr
		|| !game->player[1].ptr || !game->player[2].ptr || !game->patrol[0].ptr
		|| !game->patrol[1].ptr)
	{
		ft_printf("Error: Failed to load one or more textures\n");
		exit_game(game, 1);
	}
	game->player_anim_frame = 0;
	game->player_anim_delay = 0;
	game->patrol_anim_frame = 0;
	game->patrol_anim_delay = 0;
}