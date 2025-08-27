/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:35:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 13:14:10 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define MAX_READ_LINES 5000

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

static char	*read_map_to_string(int fd, t_game *game)
{
	char	*line;
	char	*map_str;
	char	*tmp;
	int		lines_read;

	map_str = ft_strdup("");
	lines_read = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (lines_read++ > 2000)
		{
			ft_printf("Error: Map file is too large to read.\n");
			free(line);
			free(map_str);
			exit_game(game, 1);
		}
		tmp = map_str;
		map_str = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	return (map_str);
}

static void	check_dimensions(t_game *game)
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

void	load_map(t_game *game, char *map_file)
{
	int		fd;
	char	*map_str;

	check_map_file(map_file);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(game, 1);
	map_str = read_map_to_string(fd, game);
	close(fd);
	if (map_str[0] == '\0' || ft_strnstr(map_str, "\n\n", ft_strlen(map_str)))
	{
		ft_printf("Error: Invalid map format (empty or blank line).\n");
		free(map_str);
		exit_game(game, 1);
	}
	game->map = ft_split(map_str, '\n');
	free(map_str);
}

void	check_chars(t_game *game)
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
