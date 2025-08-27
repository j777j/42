/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:45:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 07:01:12 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	i = 0;
	map_copy = malloc(sizeof(char *) * (game->height + 1));
	if (!map_copy)
	{
		ft_printf("Error: malloc failed in copy_map\n");
		exit_game(game, 1);
	}
	while (i < game->height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy[i])
		{
			ft_printf("Error: malloc failed in copy_map\n");
			while (i > 0)
				free(map_copy[--i]);
			free(map_copy);
			exit_game(game, 1);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (x < 0 || x >= game->width || y < 0 || y >= game->height
		|| map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

static int	check_path(char **map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == 'C' || map_copy[i][j] == 'E')
			{
				ft_printf("Error: Invalid path\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	validate_path(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = copy_map(game);
	flood_fill(map_copy, game->player_x, game->player_y, game);
	if (check_path(map_copy))
	{
		i = 0;
		while (map_copy[i])
		{
			free(map_copy[i]);
			i++;
		}
		free(map_copy);
		exit_game(game, 1);
	}
	i = 0;
	while (map_copy[i])
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
