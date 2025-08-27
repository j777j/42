/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:27:29 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 13:27:38 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_dimensions(t_game *game)
{
	int	i;

	game->width = ft_strlen(game->map[0]);
	if (game->width == 0)
	{
		ft_printf("Error: Map has zero width.\n");
		exit_game(game, 1);
	}
	i = 0;
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) != game->width)
		{
			ft_printf("Error: Map must be rectangular.\n");
			exit_game(game, 1);
		}
		i++;
	}
	game->height = i;
	if (game->width < 3 || game->height < 3)
	{
		ft_printf("Error: Map is too small (must be at least 3x3).\n");
		exit_game(game, 1);
	}
}

void	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->height)
	{
		j = 0;
		if (i == 0 || i == game->height - 1)
		{
			while (j < game->width)
			{
				if (game->map[i][j++] != '1')
				{
					ft_printf("Error: Map is not surrounded by walls.\n");
					exit_game(game, 1);
				}
			}
		}
		else if (game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
		{
			ft_printf("Error: Map is not surrounded by walls.\n");
			exit_game(game, 1);
		}
		i++;
	}
}

void	check_chars(t_game *game)
{
	int	exits;
	int	players;

	exits = 0;
	players = 0;
	count_elements(game, &exits, &players);
	if (players != 1 || exits != 1 || game->collectibles < 1)
	{
		ft_printf("Error: Map must have 1 P, 1 E, and >= 1 C.\n");
		exit_game(game, 1);
	}
	if (game->enemy_count > 0)
		locate_enemies(game);
}

void	check_player_spawn(t_game *game)
{
	int	x;
	int	y;

	x = game->player_x;
	y = game->player_y;
	if (game->map[y - 1][x] == '1' && game->map[y + 1][x] == '1'
		&& game->map[y][x - 1] == '1' && game->map[y][x + 1] == '1')
	{
		ft_printf("Error: Player is surrounded by walls.\n");
		exit_game(game, 1);
	}
}

void	check_map(t_game *game)
{
	if (!game->map || !game->map[0])
	{
		ft_printf("Error: Map parsing failed or map is empty.\n");
		exit_game(game, 1);
	}
	check_dimensions(game);
	check_walls(game);
	check_chars(game);
	check_player_spawn(game);
	validate_path(game);
}
