/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/19 00:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define PATROL_ANIMATION_SPEED 20

static void	update_patrol_animation(t_game *game)
{
	int	i;
	int	prev_frame;

	prev_frame = game->patrol_anim_frame;
	game->patrol_anim_delay++;
	if (game->patrol_anim_delay > PATROL_ANIMATION_SPEED)
	{
		game->patrol_anim_frame++;
		if (game->patrol_anim_frame > 1)
			game->patrol_anim_frame = 0;
		game->patrol_anim_delay = 0;
	}
	if (prev_frame != game->patrol_anim_frame)
	{
		i = 0;
		while (i < game->enemy_count)
		{
			put_sprite(game, game->floor.ptr, game->enemies[i].x,
				game->enemies[i].y);
			put_sprite(game, game->patrol[game->patrol_anim_frame].ptr,
				game->enemies[i].x, game->enemies[i].y);
			i++;
		}
	}
}

int	game_loop(t_game *game)
{
	update_patrol_animation(game);
	return (0);
}