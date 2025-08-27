/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 07:01:02 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:30:35 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		if (i == 0 || i == game->height - 1)
		{
			while (game->map[i][j])
			{
				if (game->map[i][j] != '1')
					exit_game(game, 1);
				j++;
			}
		}
		else
		{
			if (game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
				exit_game(game, 1);
		}
		i++;
	}
}

static void	count_elements(t_game *game, int *exits, int *players)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				(*players)++;
			}
			else if (game->map[i][j] == 'C')
				game->collectibles++;
			else if (game->map[i][j] == 'E')
				(*exits)++;
			else if (game->map[i][j] == 'X')
				game->enemy_count++;
			else if (game->map[i][j] != '0' && game->map[i][j] != '1'
				&& game->map[i][j] != 'X')
				exit_game(game, 1);
			j++;
		}
		i++;
	}
}

static void	locate_enemies(t_game *game)
{
	int	i;
	int	j;
	int	k;

	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		exit_game(game, 1);
	i = 0;
	k = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'X')
			{
				game->enemies[k].x = j;
				game->enemies[k].y = i;
				game->enemies[k].dir = 1;
				game->map[i][j] = FLOOR;
				k++;
			}
			j++;
		}
		i++;
	}
}
