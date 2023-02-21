/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:47 by lmuzio            #+#    #+#             */
/*   Updated: 2023/01/31 16:54:51 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/checking.h"

t_cell	*cell_last(t_cell *cell)
{
	while (cell->next)
		cell = cell->next;
	return (cell);
}

int	cell_add_to_back(t_cell **node, int newX, int newY)
{
	t_cell	*last;

	if (!*node)
	{
		*node = malloc(sizeof(t_cell));
		if (!node)
			return (error("Malloc fail", 0, false));
		(*node)->cellx = newX;
		(*node)->celly = newY;
		(*node)->next = 0;
		return (false);
	}
	last = cell_last(*node);
	last->next = malloc(sizeof(t_cell));
	if (!last->next)
		return (error("Malloc fail", 0, false));
	last->next->cellx = newX;
	last->next->celly = newY;
	last->next->next = 0;
	return (false);
}

void	free_cell(t_cell *node)
{
	t_cell	*next;

	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
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

// DEBUG
#include <unistd.h>
#include <stdio.h>

bool	check_neighbors(t_cell *to_check, t_cell **new, \
char **map, t_vec borders)
{
	static int	nborsy[8] = {1, 1, 1, 0, 0, -1, -1, -1};
	static int	nborsx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int			i;
	t_vec		target;

	while (to_check)
	{
		if (is_valid_map(to_check, borders, map))
			return (true);
		i = 0;
		while (i < 8)
		{
			target[X] = to_check->cellx - nborsx[i];
			target[Y] = to_check->celly - nborsy[i];
			if (map[target[Y]][target[X]] == '0' || \
			map[target[Y]][target[X]] == ' ')
			{
				cell_add_to_back(new, target[X], target[Y]);
				map[target[Y]][target[X]] = '1';
				// DEBUG
				// map[to_check->celly][to_check->cellx] = '#';
				// int c = 0;
				// system("clear");
				// printf("Seed floodfill:\n");
				// while (map[c])
				//    printf("%s\n", map[c++]);
				// map[to_check->celly][to_check->cellx] = '1';
				// usleep(35000);
			}
			i++;
		}
		to_check = to_check->next;
	}
	return (false);
}

void	check_map_loop(t_cell_list *cells, bool *end)
{
	t_vec	borders;

	cells->map_copy = copy_2d(cells->map_list_copy->map);
	if (!cells->map_copy)
		*end = error("Malloc error", 0, true);
	borders[X] = ft_strlen(cells->map_copy[0]) - 1;
	borders[Y] = len_2d(cells->map_copy) - 1;
	while (!*end && cells->to_check)
	{
		cells->check_copy = cells->to_check;
		*end = check_neighbors(cells->to_check, &cells->neighbors, \
			cells->map_copy, borders);
		free_cell(cells->check_copy);
		cells->to_check = cells->neighbors;
		cells->neighbors = 0;
	}
	free_2d(cells->map_copy);
}

bool	check_map(t_data *data)
{
	t_cell_list	cells;
	bool		end;

	cells = (t_cell_list){0};
	cells.map_list_copy = data->map.maps;
	end = false;
	while (!end && cells.map_list_copy)
	{
		end = cell_add_to_back(&cells.to_check, \
		cells.map_list_copy->spawn[X], cells.map_list_copy->spawn[Y]);
		if (end)
			break ;
		check_map_loop(&cells, &end);
		cells.map_list_copy = cells.map_list_copy->next;
	}
	free_cell(cells.to_check);
	free_cell(cells.neighbors);
	return (end);
}
