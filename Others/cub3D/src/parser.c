#include "parser.h"

int	parse_map(char *file, t_map *map)
{
	(void)map;
	int	fd;
	char	*line;

	printf("Parsing map file: %s\n", file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Failed to open map file\n");
		return (1);
	}
	printf("Map file opened successfully (fd: %d)\n", fd);
	while (get_next_line(fd, &line) > 0)
	{
		printf("Read line: %s\n", line);
		free(line);
	}
	printf("Finished reading map file\n");
	close(fd);
	return (0);
}