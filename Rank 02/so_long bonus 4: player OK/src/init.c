/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/18 15:38:12 by juwang           ###   ########.fr       */
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
		game->buffer.ptr = mlx_new_image(game->mlx, game->width * TILE_SIZE,
			game->height * TILE_SIZE);
	if (!game->buffer.ptr)
		exit_game(game, 1);
	game->buffer.addr = mlx_get_data_addr(game->buffer.ptr, &game->buffer.bpp,
			&game->buffer.line_len, &game->buffer.endian);
}

void	load_sprites(t_game *game)
{
	int	w;
	int	h;

	game->wall.ptr = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &w, &h);
	game->floor.ptr = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", &w, &h);
	game->collectible.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &w, &h);
	game->exit.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_closed.xpm", &w, &h);
	game->exit_open.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_open.xpm", &w, &h);

	game->player[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &w, &h);
	game->player[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player_1.xpm", &w, &h);
	game->player[2].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player_2.xpm", &w, &h);

	if (!game->wall.ptr || !game->floor.ptr || !game->collectible.ptr
		|| !game->exit.ptr || !game->exit_open.ptr || !game->player[0].ptr
		|| !game->player[1].ptr || !game->player[2].ptr)
	{
		ft_printf("Error: Failed to load one or more textures\n");
		exit_game(game, 1);
	}

	game->wall.addr = mlx_get_data_addr(game->wall.ptr, &game->wall.bpp,
			&game->wall.line_len, &game->wall.endian);
	game->floor.addr = mlx_get_data_addr(game->floor.ptr, &game->floor.bpp,
			&game->floor.line_len, &game->floor.endian);
	game->collectible.addr = mlx_get_data_addr(game->collectible.ptr,
			&game->collectible.bpp, &game->collectible.line_len,
			&game->collectible.endian);
	game->exit.addr = mlx_get_data_addr(game->exit.ptr, &game->exit.bpp,
			&game->exit.line_len, &game->exit.endian);
	game->exit_open.addr = mlx_get_data_addr(game->exit_open.ptr,
			&game->exit_open.bpp, &game->exit_open.line_len,
			&game->exit_open.endian);
	game->player[0].addr = mlx_get_data_addr(game->player[0].ptr,
			&game->player[0].bpp, &game->player[0].line_len,
			&game->player[0].endian);
	game->player[1].addr = mlx_get_data_addr(game->player[1].ptr,
			&game->player[1].bpp, &game->player[1].line_len,
			&game->player[1].endian);
	game->player[2].addr = mlx_get_data_addr(game->player[2].ptr,
			&game->player[2].bpp, &game->player[2].line_len,
			&game->player[2].endian);

	game->player_anim_frame = 0;
	game->player_anim_delay = 0;
}
