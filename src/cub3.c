/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:14 by lmuzio            #+#    #+#             */
/*   Updated: 2023/01/17 17:58:36 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3.h>

bool	error(char *msg, void *msg_arg, bool perr)
{
	char	*arg_ptr;

	printf("Error\n");
	if (perr && msg)
		perror(msg);
	arg_ptr = ft_strchr(msg, '%');
	if (msg && arg_ptr)
	{
		if (*(arg_ptr + 1) == 's')
			printf(msg, (char *)msg_arg);
		else if (*(arg_ptr + 1) == 'd')
			printf(msg, *(int *)msg_arg);
		printf("\n");
	}
	else if (msg)
		printf("%s\n", msg);
	return (true);
}

void	free_map(t_map *map)
{
	t_single_map	*next;
	int				c;

	free(map->textures[0]);
	free(map->textures[1]);
	free(map->textures[2]);
	free(map->textures[3]);
	if (!map->maps)
		return ;
	while (map->maps)
	{
		c = 0;
		while (map->maps->map[c])
			free(map->maps->map[c++]);
		free(map->maps->map);
		next = map->maps->next;
		free(map->maps);
		map->maps = next;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){{{0}, 0, 0, 0, {0}}, {0}};
	// parse map and content
	if (parse_args(&data.map, argc, argv))
		(void)data;
	// checking map
	else if (check_map(&data.map))
		(void)data;
	// execute
	
	// DEBUG
	// printf("tx1: %s\ntx2: %s\ntx3: %s\ntx4: %s\nfloor: %ld, ceiling: %ld\n", data.map.textures[NO], data.map.textures[SO], data.map.textures[WE], data.map.textures[EA], data.map.floor, data.map.ceiling);
	// t_single_map *copy = data.map.maps;
	// int	c = 0;
	// while (copy)
	// {
	// 	printf("map %d:\n", c++);
	// 	int i = 0;
	// 	while (copy->map[i])
	// 		printf("%s\n", copy->map[i++]);
	// 	copy = copy->next;
	// }
	// free all
	free_map(&data.map);
	return (0);
}
