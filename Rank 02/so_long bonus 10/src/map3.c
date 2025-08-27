/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:59:17 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 13:14:04 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	check_walls(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if (i == 0 || i == game->height - 1)
			check_horizontal_walls(game->map[i], game);
		else
			check_vertical_walls(game->map[i], game);
		i++;
	}
}

static void	check_horizontal_walls(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
		{
			ft_printf("Error: Map is not surrounded by walls.\n");
			exit_game(game, 1);
		}
		i++;
	}
}

static void	check_vertical_walls(char *line, t_game *game)
{
	if (line[0] != '1' || line[game->width - 1] != '1')
	{
		ft_printf("Error: Map is not surrounded by walls.\n");
		exit_game(game, 1);
	}
}

void	check_map(t_game *game)
{
	if (!game->map || !game->map[0])
	{
		ft_printf("Error: Map is empty or invalid.\n");
		exit_game(game, 1);
	}
	check_dimensions(game);
	check_walls(game);
	check_chars(game);
	check_player_spawn(game);
	validate_path(game);
}
