/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:59:57 by lmuzio            #+#    #+#             */
/*   Updated: 2023/03/18 22:52:38 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

bool	parse_rgb(t_map *map, char *line)
{
	char	*content;
	int		rgb;
	int		bytes[3];

	line = skip_spaces(line);
	content = skip_spaces(line + 1);
	rgb = 0;
	bytes[2] = -1;
	while (rgb < 3)
	{
		if (rgb != 0)
			content = ft_strchr(content, ',') + 1;
		if (content == (char *)0x1 || !*content)
			return (error("Color not written in right format", 0, false));
		bytes[rgb] = ft_atoi(content);
		if (bytes[rgb++] > 255)
			return (error("Color value negative or bigger than 255", 0, false));
	}
	if (*line == 'F' && is_space(line + 1))
		map->floor = (bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | 0xFF);
	if (*line == 'C' && is_space(line + 1))
		map->ceiling = (bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | 0xFF);
	return (false);
}

bool	parse_textures(t_map *map, char *line)
{
	char	*content;

	line = skip_spaces(line);
	content = skip_spaces(line + 2);
	content = ft_strdup(content);
	if (!content)
		return (error("Malloc error", 0, true));
	content[ft_strlen(content) - 1] = 0;
	if (*line == 'N' && *(line + 1) == 'O' && is_space(line + 2))
		map->textures[NO] = content;
	else if (*line == 'W' && *(line + 1) == 'E' && is_space(line + 2))
		map->textures[WE] = content;
	else if (*line == 'S' && *(line + 1) == 'O' && is_space(line + 2))
		map->textures[SO] = content;
	else if (*line == 'E' && *(line + 1) == 'A' && is_space(line + 2))
		map->textures[EA] = content;
	return (false);
}

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

int	parse_one_map(t_map *maps, int fd, int num)
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
		return (error("Map allocation failed in map number %d", &num, true));
	map[lines_count] = 0;
	if (map_add_to_back(&maps->maps, map))
		return (error("Adding map number %d to list failed", &num, true));
	return (end);
}

bool	parse_maps(t_map *map, int fd)
{
	int				end;
	int				i;
	t_single_map	*last_map_parsed;

	i = 0;
	while (true)
	{
		i++;
		end = parse_one_map(map, fd, i);
		if (end == true)
			return (true);
		last_map_parsed = map_last(map->maps);
		last_map_parsed->map = square_map(last_map_parsed->map);
		if (!last_map_parsed->map)
			return (error("Map number %d squaring failed", &i, true));
		if (find_player(last_map_parsed))
			return (error("Player not found in map number %d", &i, false));
		if (end == -2)
			break ;
	}
	return (false);
}
