/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:57:56 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/12 19:55:35 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checking.h>

int	len_longest_line(char **map)
{
	int	len;
	int	new_len;
	int	i;

	i = 0;
	len = 0;
	while (map[i])
	{
		new_len = ft_strlen(map[i++]);
		if (len < new_len)
			len = new_len;
	}
	return (len);
}

char	**square_map(char **map)
{
	int	i;
	int	oldlen;
	int	len;

	len = len_longest_line(map);
	i = 0;
	while (map[i])
	{
		oldlen = ft_strlen(map[i]);
		map[i] = ft_realloc(map[i], oldlen, len + 1);
		if (!map[i])
			return (0);
		while (oldlen < len)
			map[i][oldlen++] = ' ';
		map[i] = ft_reverse_str(map[i]);
		if (!map[i])
			return (0);
		map[i++][len] = 0;
	}
	return (map);
}

t_single_map	*map_last(t_single_map *map)
{
	while (map->next)
		map = map->next;
	return (map);
}

bool	map_add_to_back(t_single_map **node, char **map)
{
	t_single_map	*last;

	if (!*node)
	{
		*node = malloc(sizeof(t_single_map));
		if (!node)
			return (error("Malloc fail", 0, false));
		(*node)->map = map;
		(*node)->next = 0;
		return (false);
	}
	last = map_last(*node);
	last->next = malloc(sizeof(t_single_map));
	if (!last->next)
		return (error("Malloc fail", 0, false));
	last->next->map = map;
	last->next->next = 0;
	return (false);
}

bool	is_valid_map(t_cell *to_check, t_vec borders, char **map)
{
	char		ch;

	if (!to_check->cellx || to_check->cellx == borders[X] || \
		!to_check->celly || to_check->celly == borders[Y] || \
		map[to_check->celly][to_check->cellx] == ' ')
		return (error("Map is not surrounded by walls", 0, false));
	ch = map[to_check->celly][to_check->cellx];
	if (ch != '0' && ch != '1' && ch != 'N' && ch != 'S' \
	&& ch != 'E' && ch != 'W')
		return (error("Map contains invalid charachter at '%s'", \
		map[to_check->celly], false));
	return (false);
}
