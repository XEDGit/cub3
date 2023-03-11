/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/17 14:54:51 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/03/11 19:00:04 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	parsing_map_loop(char **map, int fd, int *lines_count)
{
	char	*line;
	char	*content;

	line = get_next_line(fd);
	if (!line)
		return (-2);
	content = skip_spaces(line);
	if (*lines_count && *content == '\n')
	{
		free(line);
		return (-1);
	}
	if (*content != '\n' && *content)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		map[(*lines_count)++] = line;
	}
	else
		free(line);
	return (false);
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
		map[i++][len] = 0;
	}
	return (map);
}

int	parse_one_map(t_map *maps, int fd)
{
	int		lines_count;
	int		size;
	int		end;
	char	**map;

	lines_count = 0;
	size = 10;
	map = malloc(sizeof(char *) * size);
	while (map)
	{
		end = parsing_map_loop(map, fd, &lines_count);
		if (end)
			break ;
		if (lines_count == size)
		{
			map = ft_realloc(map, 8 * size, 8 * (size + 10));
			size += 10;
		}
	}
	if (!map)
		return (error("Map allocation failed", 0, true));
	map[lines_count] = 0;
	if (map_add_to_back(&maps->maps, map))
		return (error("Adding map to list failed", 0, true));
	return (end);
}

bool	parse_maps(t_map *map, int fd)
{
	int				end;
	t_single_map	*last_node;

	while (true)
	{
		end = parse_one_map(map, fd);
		if (end == true)
			return (true);
		last_node = map_last(map->maps);
		last_node->map = square_map(last_node->map);
		if (!last_node->map)
			return (error("Map squaring failed", 0, true));
		if (find_player(last_node))
			return (error("Player not found in map", 0, false));
		if (end == -2)
			break ;
	}
	return (false);
}

bool	parse_rgb(t_map *map, char *line)
{
	char				*content;
	unsigned int		atoi_buff;
	long				rgb;

	content = skip_spaces(line + 2);
	rgb = 0;
	atoi_buff = ft_atoi(content);
	if (atoi_buff > 255)
		return (error("Red value negative or bigger than 255", 0, false));
	rgb += atoi_buff << 6;
	content = ft_strchr(content, ',') + 1;
	atoi_buff = ft_atoi(content);
	if (atoi_buff > 255)
		return (error("Green value negative or bigger than 255", 0, false));
	rgb += atoi_buff << 3;
	content = ft_strchr(content, ',') + 1;
	atoi_buff = ft_atoi(content);
	if (atoi_buff > 255)
		return (error("Blue value negative or bigger than 255", 0, false));
	rgb += atoi_buff;
	if (*line == 'F' && *(line + 1) == ' ')
		map->floor = rgb;
	if (*line == 'C' && *(line + 1) == ' ')
		map->ceiling = rgb;
	return (false);
}

bool	parse_textures(t_map *map, char *line)
{
	char	*content;

	content = skip_spaces(line + 2);
	content = ft_strdup(content);
	if (!content)
		return (error("Malloc error", 0, true));
	content[ft_strlen(content) - 1] = 0;
	if (*line == 'N' && *(line + 1) == 'O' && *(line + 2) == ' ')
		map->textures[NO] = content;
	else if (*line == 'W' && *(line + 1) == 'E' && *(line + 2) == ' ')
		map->textures[WE] = content;
	else if (*line == 'S' && *(line + 1) == 'O' && *(line + 2) == ' ')
		map->textures[SO] = content;
	else if (*line == 'E' && *(line + 1) == 'A' && *(line + 2) == ' ')
		map->textures[EA] = content;
	return (false);
}

bool	parse_lines(t_map *map, int fd)
{
	char	*line;
	char	*cur;
	bool	err;

	err = false;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			return (false);
		cur = skip_spaces(line);
		if (!*cur)
			err = true;
		else if (*cur == 'C' || *cur == 'F')
			err = parse_rgb(map, cur);
		else if (*cur == 'N' || *cur == 'W' || *cur == 'S' || *cur == 'E')
			err = parse_textures(map, cur);
		free(line);
		if (err)
			return (error("Error parsing the map", 0, false));
		if (map->ceiling && map->floor && map->textures[0] && \
		map->textures[1] && map->textures[2] && map->textures[3])
			break ;
	}
	return (false);
}

bool	parse_args(t_map *map, int argc, char **argv)
{
	int		fd;

	if (argc < 2)
		return (error("Not enough arguments\nUsage: ./cub3 path_to_map", \
		0, false));
	fd = open(argv[1], O_RDONLY);
	if (read(fd, 0, 0))
		return (error("File open failed", 0, true));
	if (parse_lines(map, fd) || parse_maps(map, fd))
		return (free_fd_gnl(fd));
	if (close(fd))
		return (error("Failed closing file descriptor", 0, true));
	return (false);
}
