/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:57:26 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_sprite(t_game *game, t_img *sprite, int start_x, int start_y)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			color = *(int *)(sprite->addr + (y * sprite->line_len + x
						* (sprite->bpp / 8)));
			put_pixel_to_buffer(&game->buffer, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_tile(t_game *game, int x, int y)
{
	if (game->map[y][x] == WALL)
		draw_sprite(game, &game->wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == COLLECTIBLE)
		draw_sprite(game, &game->collectible, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == EXIT)
	{
		if (game->collectibles == 0)
			draw_sprite(game, &game->exit_open, x * TILE_SIZE, y * TILE_SIZE);
		else
			draw_sprite(game, &game->exit, x * TILE_SIZE, y * TILE_SIZE);
	}
	else
		draw_sprite(game, &game->floor, x * TILE_SIZE, y * TILE_SIZE);
}

static void	draw_base_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
			draw_tile(game, x, y);
	}
}

static void	draw_characters(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		draw_sprite(game, &game->enemy[game->enemy_anim_frame],
			game->enemies[i].x * TILE_SIZE, game->enemies[i].y * TILE_SIZE);
		i++;
	}
	draw_sprite(game, &game->player[game->player_anim_frame], game->player_x
		* TILE_SIZE, game->player_y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	draw_base_map(game);
	draw_characters(game);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.ptr, 0, 0);
	display_move_count(game);
}
