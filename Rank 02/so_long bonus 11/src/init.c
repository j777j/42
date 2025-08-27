/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 14:43:44 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_sprites(t_game *game)
{
	int	w;
	int	h;

	load_all_images(game, &w, &h);
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

void	init_window(t_game *game)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game->mlx, &screen_width, &screen_height);
	if (game->width * TILE_SIZE > screen_width || game->height
		* TILE_SIZE > screen_height)
	{
		ft_printf("Error: Map is too large to fit on the screen.\n");
		exit_game(game, 1);
	}
	game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, game->height
			* TILE_SIZE, "so_long");
	if (!game->win)
		exit_game(game, 1);
	game->buffer.ptr = mlx_new_image(game->mlx, game->width * TILE_SIZE,
			game->height * TILE_SIZE);
	if (!game->buffer.ptr)
		exit_game(game, 1);
	game->buffer.addr = mlx_get_data_addr(game->buffer.ptr, &game->buffer.bpp,
			&game->buffer.line_len, &game->buffer.endian);
}

void	init_game(t_game *game, char *map_file)
{
	load_map(game, map_file);
	check_map(game);
}
