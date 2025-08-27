/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:27:13 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 14:43:47 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define MAX_READ_LINES 2000

static void	check_basename(char *map_file)
{
	char	*basename;

	basename = ft_strrchr(map_file, '/');
	if (basename == NULL)
		basename = map_file;
	else
		basename++;
	if (ft_strncmp(basename, ".ber", 5) == 0)
	{
		ft_printf("Error: Invalid filename: \".ber\" is not allowed.\n");
		exit(1);
	}
}

static void	check_map_file(char *map_file)
{
	int		fd;
	char	*ext;

	check_basename(map_file);
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Cannot open map file.\n");
		exit(1);
	}
	ext = ft_strrchr(map_file, '.');
	if (!ext || ft_strncmp(ext, ".ber", 5) != 0)
	{
		ft_printf("Error: Map file must have a .ber extension.\n");
		close(fd);
		exit(1);
	}
	close(fd);
}

static char	*append_line(char *map_str, char *line, t_game *game)
{
	char	*tmp;

	tmp = map_str;
	map_str = ft_strjoin(tmp, line);
	free(tmp);
	free(line);
	if (!map_str)
		exit_game(game, 1);
	return (map_str);
}

static char	*read_map_to_string(int fd, t_game *game)
{
	char	*line;
	char	*map_str;
	int		lines_read;

	map_str = ft_strdup("");
	if (!map_str)
		exit_game(game, 1);
	lines_read = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (lines_read++ > MAX_READ_LINES)
		{
			ft_printf("Error: Map file is too large.\n");
			free(line);
			free(map_str);
			exit_game(game, 1);
		}
		map_str = append_line(map_str, line, game);
	}
	return (map_str);
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
	if (!game->map)
		exit_game(game, 1);
}
