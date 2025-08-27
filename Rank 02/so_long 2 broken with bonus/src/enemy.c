/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/18 16:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_enemies(t_game *game)
{
	static int	direction = 1;
	int			x;
	int			y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == ENEMY)
			{
				if (game->map[y][x + direction] == FLOOR)
				{
					game->map[y][x] = FLOOR;
					game->map[y][x + direction] = ENEMY;
					return ;
				}
				else
					direction *= -1;
			}
			x++;
		}
		y++;
	}
}
