/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:26:46 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define PLAYER_ANIMATION_SPEED 15
#define ENEMY_ANIMATION_SPEED 90
#define ENEMY_MOVE_SPEED 60

static void	move_enemies(t_game *game)
{
	int	i;
	int	next_x;

	i = 0;
	while (i < game->enemy_count)
	{
		next_x = game->enemies[i].x + game->enemies[i].dir;
		if (game->map[game->enemies[i].y][next_x] == WALL)
			game->enemies[i].dir *= -1;
		else
			game->enemies[i].x = next_x;
		if (game->enemies[i].x == game->player_x
			&& game->enemies[i].y == game->player_y)
		{
			ft_printf("You lose! Ambushed by an enemy.\n");
			exit_game(game, 0);
		}
		i++;
	}
}

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
		game->enemy_anim_frame = (game->enemy_anim_frame + 1) % 2;
		game->enemy_anim_delay = 0;
	}
	game->enemy_move_delay++;
	if (game->enemy_move_delay > ENEMY_MOVE_SPEED)
	{
		move_enemies(game);
		game->enemy_move_delay = 0;
	}
	render_map(game);
	return (0);
}
