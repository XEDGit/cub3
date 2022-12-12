#include <parsing.h>

bool	parse_textures(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (false);
	if (*line == '\n')
		;
	else if 
		
	free(line);
	return (false);
}

bool	parse_args(t_map *map, int argc, char **argv)
{
	int	fd;

	if (argc < 2)
		return (error("Not enough arguments\nUsage: ./cub3 path_to_map", false));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error("File open failed", true);
	if (parse_textures(map, fd) ||	parse_map(map, fd))
		return (true);
	if (close(fd))
		return (error("Failed closing file descriptor", true));
	return (false);
}
