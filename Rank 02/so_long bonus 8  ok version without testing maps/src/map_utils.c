/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 07:01:02 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:38:47 by juwang           ###   ########.fr       */
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

static void	process_tile_for_count(t_game *game, t_tile_data *data)
{
	if (data->c == 'P')
	{
		game->player_x = data->x;
		game->player_y = data->y;
		(*data->players)++;
	}
	else if (data->c == 'C')
		game->collectibles++;
	else if (data->c == 'E')
		(*data->exits)++;
	else if (data->c == 'X')
		game->enemy_count++;
	else if (data->c != '0' && data->c != '1' && data->c != 'X')
		exit_game(game, 1);
}

void	count_elements(t_game *game, int *exits, int *players)
{
	t_tile_data	data;
	int			i;
	int			j;

	data.exits = exits;
	data.players = players;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			data.c = game->map[i][j];
			data.x = j;
			data.y = i;
			process_tile_for_count(game, &data);
			j++;
		}
		i++;
	}
}

static void	find_and_init_enemies(t_game *game)
{
	int	i;
	int	j;
	int	k;

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

void	locate_enemies(t_game *game)
{
	game->enemies = malloc(sizeof(t_enemy) * game->enemy_count);
	if (!game->enemies)
		exit_game(game, 1);
	find_and_init_enemies(game);
}
