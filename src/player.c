#include <shared.h>

bool	find_player(t_single_map *map_list)
{
	int	i;
	int	j;

	i = 0;
	while (map_list->map[i])
	{
		j = 0;
		while (map_list->map[i][j])
		{
			if (map_list->map[i][j] == 'N' || map_list->map[i][j] == 'E' || \
			map_list->map[i][j] == 'W' || map_list->map[i][j] == 'S')
			{
				map_list->spawn[X] = j;
				map_list->spawn[Y] = i;
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}