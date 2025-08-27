/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:35:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 06:46:18 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_map_file(char *map_file)
{
	int		fd;
	char	*ext;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Cannot open map file: %s\n", map_file);
		exit(1);
	}
	ext = ft_strrchr(map_file, '.');
	if (!ext || ft_strncmp(ext, ".ber", 5) != 0)
	{
		ft_printf("Error: Map file must have a .ber extension\n");
		exit(1);
	}
	close(fd);
}

void	load_map(t_game *game, char *map_file)
{
	int		fd;
	char	*line;
	char	*map_str;
	char	*tmp;

	check_map_file(map_file);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(game, 1);
	map_str = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = map_str;
		map_str = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	close(fd);
	game->map = ft_split(map_str, '\n');
	free(map_str);
}

static void	check_chars(t_game *game)
{
	int	exits;
	int	players;

	exits = 0;
	players = 0;
	game->collectibles = 0;
	game->enemy_count = 0;
	count_elements(game, &exits, &players);
	if (players != 1 || exits != 1 || game->collectibles < 1)
	{
		ft_printf("Error: Map must have 1 P, 1 E, and >= 1 C\n");
		exit_game(game, 1);
	}
	if (game->enemy_count > 0)
		locate_enemies(game);
}

void	check_map(t_game *game)
{
	int	i;

	i = 0;
	if (!game->map || !game->map[0])
	{
		ft_printf("Error: Map is empty or invalid\n");
		exit_game(game, 1);
	}
	game->width = ft_strlen(game->map[0]);
	if (game->width > MAX_MAP_WIDTH || game->height > MAX_MAP_HEIGHT)
	{
		write(2, "Error: map too large\n", 22);
		free_map(game);
		exit(1);
	}
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) != game->width)
			exit_game(game, 1);
		i++;
	}
	game->height = i;
	check_walls(game);
	check_chars(game);
	validate_path(game);
}
