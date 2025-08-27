/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:52:19 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_map_and_player_images(t_game *game, int *w, int *h)
{
	game->wall.ptr = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", w,
			h);
	game->floor.ptr = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", w,
			h);
	game->collectible.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", w, h);
	game->exit.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_closed.xpm", w, h);
	game->exit_open.ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/exit_open.xpm", w, h);
	game->player[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", w, h);
	game->player[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player_1.xpm", w, h);
	game->player[2].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/player_2.xpm", w, h);
}

static void	load_enemy_images(t_game *game, int *w, int *h)
{
	game->enemy[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy_1.xpm", w, h);
	game->enemy[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy_2.xpm", w, h);
}

static void	get_map_and_player_addrs(t_game *game)
{
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
}

static void	get_enemy_addrs(t_game *game)
{
	game->enemy[0].addr = mlx_get_data_addr(game->enemy[0].ptr,
			&game->enemy[0].bpp, &game->enemy[0].line_len,
			&game->enemy[0].endian);
	game->enemy[1].addr = mlx_get_data_addr(game->enemy[1].ptr,
			&game->enemy[1].bpp, &game->enemy[1].line_len,
			&game->enemy[1].endian);
}

void	load_sprites(t_game *game)
{
	int	w;
	int	h;

	load_map_and_player_images(game, &w, &h);
	load_enemy_images(game, &w, &h);
	if (!game->wall.ptr || !game->floor.ptr || !game->collectible.ptr
		|| !game->exit.ptr || !game->exit_open.ptr || !game->player[0].ptr
		|| !game->player[1].ptr || !game->player[2].ptr || !game->enemy[0].ptr
		|| !game->enemy[1].ptr)
	{
		ft_printf("Error: Failed to load one or more textures\n");
		exit_game(game, 1);
	}
	get_map_and_player_addrs(game);
	get_enemy_addrs(game);
	game->player_anim_frame = 0;
	game->player_anim_delay = 0;
	game->enemy_anim_frame = 0;
	game->enemy_anim_delay = 0;
	game->enemy_move_delay = 0;
}
