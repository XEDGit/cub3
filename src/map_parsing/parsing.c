/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:51 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/12 20:12:01 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

static bool	test_fds(t_map *map)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		fd = open(map->textures[i], O_RDONLY);
		if (read(fd, 0, 0))
		{
			if (fd != -1)
				close(fd);
			return (error("Failed to read file '%s'", map->textures[i], false));
		}
		close(fd);
		i++;
	}
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
			return (error("Failed to parse textures or colors", 0, false));
		cur = skip_spaces(line);
		if (!*cur)
			err = true;
		else if (*cur == 'C' || *cur == 'F')
			err = parse_rgb(map, cur);
		else if (*cur == 'N' || *cur == 'W' || *cur == 'S' || *cur == 'E')
			err = parse_textures(map, cur);
		free(line);
		if (err)
			return (1);
		if (map->ceiling && map->floor && map->textures[0] && \
		map->textures[1] && map->textures[2] && map->textures[3])
			break ;
	}
	return (false);
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
		if (end == -3)
			return (error("Wrong format found before \
map number %d", &i, 0));
		if (end == true)
			return (true);
		last_map_parsed = map_last(map->maps);
		last_map_parsed->map = square_map(last_map_parsed->map);
		if (!last_map_parsed->map)
			return (error("Map number %d squaring failed", &i, true));
		if (find_player(last_map_parsed))
			return (error("Zero or multiple players found in map %d", &i, 0));
		if (end == -2)
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
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 3], "cub"))
		return (error("Map '%s' extension is not '.cub'", argv[1], false));
	fd = open(argv[1], O_RDONLY);
	if (read(fd, 0, 0))
		return (error("File open failed", 0, true));
	if (parse_lines(map, fd) || parse_maps(map, fd))
		return (free_fd_gnl(fd));
	if (close(fd))
		return (error("Failed closing file descriptor", 0, true));
	return (test_fds(map));
}
