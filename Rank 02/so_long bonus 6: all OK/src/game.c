/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/19 22:19:11 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define PLAYER_ANIMATION_SPEED 15
#define ENEMY_ANIMATION_SPEED 90

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
	game->enemy_anim_delay++;
	if (game->enemy_anim_delay > ENEMY_ANIMATION_SPEED)
	{
		game->enemy_anim_frame = (game->enemy_anim_frame + 1) % 2; // 因為只有兩張圖
		game->enemy_anim_delay = 0;
	}
	render_map(game);
	return (0);
}
