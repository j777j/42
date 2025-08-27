/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:28:57 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	handle_move(t_game *game, int new_x, int new_y)
{
	int	i;

	i = 0;
	while (i < game->enemy_count)
	{
		if (new_x == game->enemies[i].x && new_y == game->enemies[i].y)
		{
			ft_printf("You lose! Touched an enemy.\n");
			exit_game(game, 0);
		}
		i++;
	}
	if (game->map[new_y][new_x] == COLLECTIBLE)
	{
		game->map[new_y][new_x] = FLOOR;
		game->collectibles--;
	}
	if (game->map[new_y][new_x] == EXIT)
	{
		if (game->collectibles == 0)
		{
			ft_printf("Congratulations! You win!\n");
			exit_game(game, 0);
		}
		else
		{
			ft_printf("Info: Collect all items before exiting!\n");
			return ;
		}
	}
	game->map[game->player_y][game->player_x] = FLOOR;
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = PLAYER;
	game->moves++;
	render_map(game);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
	{
		ft_printf("Error: Player move out of map bounds\n");
		return ;
	}
	if (game->map[new_y][new_x] == WALL)
	{
		ft_printf("Info: Hit a wall, can't move\n");
		return ;
	}
	handle_move(game, new_x, new_y);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game, 0);
	else if (keycode == KEY_W)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == KEY_A)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == KEY_S)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == KEY_D)
		move_player(game, game->player_x + 1, game->player_y);
	return (0);
}
