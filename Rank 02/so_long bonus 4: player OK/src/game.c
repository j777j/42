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

#define PLAYER_ANIMATION_SPEED 15

int	game_loop(t_game *game)
{
	game->player_anim_delay++;
	if (game->player_anim_delay > PLAYER_ANIMATION_SPEED)
	{
		game->player_anim_frame++;
		if (game->player_anim_frame > 2)
			game->player_anim_frame = 0;
		game->player_anim_delay = 0;
	}
	render_map(game);
	return (0);
}
