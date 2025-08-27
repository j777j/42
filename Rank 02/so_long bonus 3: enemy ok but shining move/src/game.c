/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 07:00:37 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define PATROL_ANIMATION_SPEED 20

int	game_loop(t_game *game)
{
	game->patrol_anim_delay++;
	if (game->patrol_anim_delay > PATROL_ANIMATION_SPEED)
	{
		game->patrol_anim_frame++;
		if (game->patrol_anim_frame > 1)
			game->patrol_anim_frame = 0;
		game->patrol_anim_delay = 0;
		render_map(game);
	}
	return (0);
}
