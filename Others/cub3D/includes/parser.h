#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"
# include <fcntl.h>

typedef struct s_map
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
}				t_map;

int	parse_map(char *file, t_map *map);
int		get_next_line(int fd, char **line);

#endif