/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:27:13 by juwang            #+#    #+#             */
/*   Updated: 2025/07/21 18:05:58 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define MAX_READ_LINES 2000

void	validate_map_file(char *map_file)
{
	int		fd;
	char	*ext;
	char	*basename;

	basename = ft_strrchr(map_file, '/');
	if (basename == NULL)
		basename = map_file;
	else
		basename++;
	if (ft_strncmp(basename, ".ber", 5) == 0)
		handle_error("Invalid filename: \".ber\" is not allowed.");
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		handle_error("Cannot open map file.");
	ext = ft_strrchr(map_file, '.');
	if (!ext || ft_strncmp(ext, ".ber", 5) != 0)
	{
		close(fd);
		handle_error("Map file must have a .ber extension.");
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
			free(line);
			free(map_str);
			handle_error("Map file is too large.");
		}
		map_str = append_line(map_str, line, game);
	}
	return (map_str);
}

void	load_map(t_game *game, char *map_file)
{
	int		fd;
	char	*map_str;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		exit_game(game, 1);
	map_str = read_map_to_string(fd, game);
	close(fd);
	if (map_str[0] == '\0' || ft_strnstr(map_str, "\n\n", ft_strlen(map_str)))
	{
		free(map_str);
		handle_error("Invalid map format (empty or blank line).");
	}
	game->map = ft_split(map_str, '\n');
	free(map_str);
	if (!game->map)
		exit_game(game, 1);
}
