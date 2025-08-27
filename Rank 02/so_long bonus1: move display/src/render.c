/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 07:01:15 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_sprite(t_game *game, void *sprite, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, sprite, x * TILE_SIZE, y
		* TILE_SIZE);
}

void	render_map(t_game *game)
{
	int		x;
	int		y;
	char	*moves_str;
	char	*display_str;

	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			put_sprite(game, game->floor.ptr, x, y);
			if (game->map[y][x] == WALL)
				put_sprite(game, game->wall.ptr, x, y);
			else if (game->map[y][x] == COLLECTIBLE)
				put_sprite(game, game->collectible.ptr, x, y);
			else if (game->map[y][x] == EXIT)
			{
				if (game->collectibles == 0)
					put_sprite(game, game->exit_open.ptr, x, y);
				else
					put_sprite(game, game->exit.ptr, x, y);
			}
			else if (game->map[y][x] == PLAYER)
				put_sprite(game, game->player.ptr, x, y);
		}
	}
	moves_str = ft_itoa(game->moves);
	display_str = ft_strjoin("Moves: ", moves_str);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, display_str);
	free(moves_str);
	free(display_str);
}
