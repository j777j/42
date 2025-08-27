/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 14:23:43 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 14:26:01 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_all_images(t_game *game, int *w, int *h)
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
	game->enemy[0].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy_1.xpm", w, h);
	game->enemy[1].ptr = mlx_xpm_file_to_image(game->mlx,
			"textures/enemy_2.xpm", w, h);
}

void	get_map_and_player_addrs(t_game *game)
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

void	get_enemy_addrs(t_game *game)
{
	game->enemy[0].addr = mlx_get_data_addr(game->enemy[0].ptr,
			&game->enemy[0].bpp, &game->enemy[0].line_len,
			&game->enemy[0].endian);
	game->enemy[1].addr = mlx_get_data_addr(game->enemy[1].ptr,
			&game->enemy[1].bpp, &game->enemy[1].line_len,
			&game->enemy[1].endian);
}
