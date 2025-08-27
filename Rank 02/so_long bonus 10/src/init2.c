/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:51:54 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 13:03:01 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game, char *map_file)
{
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

void	check_player_spawn(t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if ((game->map[y - 1][x] == '1' || game->map[y - 1][x] == 'E')
		&& (game->map[y + 1][x] == '1' || game->map[y + 1][x] == 'E')
		&& (game->map[y][x - 1] == '1' || game->map[y][x - 1] == 'E')
		&& (game->map[y][x + 1] == '1' || game->map[y][x + 1] == 'E'))
	{
		ft_printf("Error: Player is surrounded by walls or exits.\n");
		exit_game(game, 1);
	}
}
