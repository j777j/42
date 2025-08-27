/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:53:49 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 13:28:45 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_pixel_to_buffer(t_img *buffer, int x, int y, int color)
{
	char	*dst;

	dst = buffer->addr + (y * buffer->line_len + x * (buffer->bpp / 8));
	*(unsigned int *)dst = color;
}

void	display_move_count(t_game *game)
{
	char	*moves_str;
	char	*display_str;

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
