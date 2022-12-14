#include <cub3.h>

bool	error(char *msg, bool perr)
{
	printf("Error\n");
	if (perr && msg)
		perror(msg);
	else if (msg)
		printf("%s\n", msg);
	return (true);
}

void	free_map(t_map *map)
{
	char	**map_copy;
	int		c;

	c = 0;
	free(map->textures[0]);
	free(map->textures[1]);
	free(map->textures[2]);
	free(map->textures[3]);
	if (!map->map)
		return ;
	map_copy = map->map;
	while (map_copy[c])
		free(map_copy[c++]);
	free(map->map);
}

int main(int argc, char **argv)
{
	t_map	map;

	map = (t_map){0};
	// parse map and content
	if (parse_args(&map, argc, argv))
		(void)map;
	// checking map
	else if (check_map(&map))
		(void)map;
	// execute
	printf("tx1: %s\ntx2: %s\ntx3: %s\ntx4: %s\n", map.textures[NO], map.textures[SO], map.textures[WE], map.textures[EA]);
	int i = 0;
	while (map.map && map.map[i])
		printf("%s", map.map[i++]);
	// free all
	free_map(&map);
	return (0);
}
