/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:28:33 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* render.c 的最終版本 */
#include "so_long.h"

// 工具函式1：將一個像素畫到 buffer 上
static void	put_pixel_to_buffer(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	dst = buffer->addr + (y * buffer->line_len + x * (buffer->bpp / 8));
	*(unsigned int *)dst = color;
}

// 工具函式2：將一個不透明的 sprite 完全複製到 buffer 上
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

// 全新的主渲染函式
void	render_map(t_game *game)
{
	int		x;
	int		y;
	int		i;
	char	*moves_str;
	char	*display_str;

	y = -1;
	while (++y < game->height)
	{
		x = -1;
		while (++x < game->width)
		{
			if (game->map[y][x] == WALL)
				draw_sprite(game, &game->wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map[y][x] == COLLECTIBLE)
				draw_sprite(game, &game->collectible, x * TILE_SIZE, y
					* TILE_SIZE);
			else if (game->map[y][x] == EXIT)
			{
				if (game->collectibles == 0)
					draw_sprite(game, &game->exit_open, x * TILE_SIZE, y
						* TILE_SIZE);
				else
					draw_sprite(game, &game->exit, x * TILE_SIZE, y
						* TILE_SIZE);
			}
			else
				draw_sprite(game, &game->floor, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
	i = 0;
	while (i < game->enemy_count)
	{
		draw_sprite(game, &game->enemy[game->enemy_anim_frame],
			game->enemies[i].x * TILE_SIZE, game->enemies[i].y * TILE_SIZE);
		i++;
	}
	draw_sprite(game, &game->player[game->player_anim_frame], game->player_x
		* TILE_SIZE, game->player_y * TILE_SIZE);
	mlx_put_image_to_window(game->mlx, game->win, game->buffer.ptr, 0, 0);
	moves_str = ft_itoa(game->moves);
	if (!moves_str)
		return ;
	display_str = ft_strjoin("Moves: ", moves_str);
	if (!display_str)
	{
		free(moves_str);
		return ;
	}
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, display_str);
	free(moves_str);
	free(display_str);
}
