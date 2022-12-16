#include <checking.h>

bool	is_valid_map(char ch)
{
	if (ch == '0' || ch == '1' || ch == 'N' || ch == 'S' || ch == 'E' || ch == 'W')
		return (true);
	return (false);
}

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
			return (error("Malloc fail", false));
		(*node)->cellX = newX;
		(*node)->cellY = newY;
		(*node)->next = 0;
		return (false);
	}
	last = cell_last(*node);
	last->next = malloc(sizeof(t_cell));
	if (!last->next)
		return (error("Malloc fail", false));
	last->next->cellX = newX;
	last->next->cellY = newY;
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

bool	check_neighbors(t_cell *to_check, t_cell **new, char **map, vec_t borders)
{
	static int	nborsY[] = { 1, 1, 1,  0, 0, -1, -1, -1};
	static int	nborsX[] = {-1, 0, 1, -1, 1, -1,  0,  1};
	int			i;
	vec_t		target;

	while (to_check)
	{
		if (!to_check->cellX || to_check->cellX == borders[X] ||
		!to_check->cellY || to_check->cellY == borders[Y])
			return (error("Map is not surrounded by walls", false));
		i = 0;
		while (i < 8)
		{
			target[X] = to_check->cellX - nborsX[i];
			target[Y] = to_check->cellY - nborsY[i];
			// TODO	targets value set to minus
			printf("targets: %d, %d\n", target[X], target[Y]);
			if (!is_valid_map(map[target[Y]][target[X]]))
				return (error("Map contains invalid charachter", false));
			if (map[target[Y]][target[X]] == '0')
			{
				map[target[Y]][target[X]] = '2';
				cell_add_to_back(new, target[X], target[Y]);
			}
			i++;
		}
		to_check = to_check->next;
	}
	return (false);
}

void	check_map_loop(t_cell_list *cells, bool *end)
{
	vec_t	borders;

	cells->map_copy = copy_2d(cells->map_list_copy->map);
	cells->check_copy = cells->to_check;
	if (!cells->map_copy)
		*end = error("Malloc error", true);
	borders[X] = ft_strlen(cells->map_copy[0]);
	borders[Y] = len_2d(cells->map_copy);
	while (!*end && cells->to_check)
	{
		*end = check_neighbors(cells->to_check, &cells->neighbors, cells->map_copy, borders);
		cells->to_check = cells->to_check->next;
	}
	cells->to_check = cells->neighbors;
	free_cell(cells->check_copy);
	free_2d(cells->map_copy);
}

bool	check_map(t_data *data)
{
	t_cell_list	cells;
	bool		end;

	cells = (t_cell_list){0};
	cells.map_list_copy = data->map.maps;
	end = false;
	while (cells.map_list_copy)
	{
		if (cell_add_to_back(&cells.to_check, cells.map_list_copy->spawn[X], cells.map_list_copy->spawn[Y]))
			return (true);
		check_map_loop(&cells, &end);
		cells.map_list_copy = cells.map_list_copy->next;
	}
	free_cell(cells.to_check);
	free_cell(cells.neighbors);
	return (end);
}