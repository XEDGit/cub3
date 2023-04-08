/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:59:57 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/09 00:26:47 by lmuzio           ###   ########.fr       */
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
	while (rgb < 3)
	{
		if (rgb != 0)
			content = ft_strchr(content, ',') + 1;
		if (content == (char *)0x1 || !*content)
			return (error("Color not in the right format: '%s'", line, false));
		content = skip_spaces(content);
		if (*content < '0' || *content > '9')
			return (error("Color not in the right format: '%s'", line, false));
		bytes[rgb] = ft_atoi(content);
		if (bytes[rgb++] > 255)
			return (error("Color value out of bounds: '%s'", line, false));
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
	char	**target;

	if (*line == 'N' && *(line + 1) == 'O' && is_space(line + 2))
		target = &map->textures[NO];
	else if (*line == 'W' && *(line + 1) == 'E' && is_space(line + 2))
		target = &map->textures[WE];
	else if (*line == 'S' && *(line + 1) == 'O' && is_space(line + 2))
		target = &map->textures[SO];
	else if (*line == 'E' && *(line + 1) == 'A' && is_space(line + 2))
		target = &map->textures[EA];
	line = skip_spaces(line);
	content = skip_spaces(line + 2);
	content = ft_strdup(content);
	if (!content)
		return (error("Malloc error", 0, true));
	content[ft_strlen(content) - 1] = 0;
	if (*target)
		free(*target);
	*target = content;
	return (false);
}

int	parse_one_line(t_map *map, char *line)
{
	int	err;

	err = 0;
	if ((*line == 'N' && *(line + 1) == 'O' && is_space(line + 2)) || \
	(*line == 'W' && *(line + 1) == 'E' && is_space(line + 2)) || \
	(*line == 'S' && *(line + 1) == 'O' && is_space(line + 2)) || \
	(*line == 'E' && *(line + 1) == 'A' && is_space(line + 2)))
		err = parse_textures(map, line);
	else if ((*line == 'F' && is_space(line + 1)) || \
	(*line == 'C' && is_space(line + 1)))
		err = parse_rgb(map, line);
	else
		err = 1;
	return (err);
}

int	parsing_map_loop(char **map, int fd, int *lines_count, t_map *maps)
{
	char	*line;
	char	*content;

	line = get_next_line(fd);
	if (!line)
		return (-2);
	content = skip_spaces(line);
	if (*lines_count && *content == '\n')
		return (free(line), -1);
	if (*content != '\n' && *content)
	{
		if (!*lines_count && *content != '1')
		{
			if (!parse_one_line(maps, content))
				return (free(line), false);
			else
				return (free(line), -3);
		}
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
		end = parsing_map_loop(map, fd, &lines_count, maps);
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
