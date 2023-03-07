/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:14 by lmuzio            #+#    #+#             */
/*   Updated: 2023/01/23 17:31:33 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3.h"
#include "../../includes/rendering.h"
#include <string.h>

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
	t_data			data;
	mlx_texture_t	*tex;
	mlx_t			*mlx;
	mlx_image_t		*buf;

	data = (t_data){{{0}, 0, 0, 0, {0}}, 0};
	/* parse map and content */
	if (parse_args(&data.map, argc, argv))
		(void)data;
	/* checking map */
	else if (check_map(&data.map))
		(void)data;
	/* execute */
	/* free all */
	printf("x pos: %d y pos: %d\n", data.map.maps->spawn[0], data.map.maps->spawn[1]);
	free_map(&data.map);
	mlx = mlx_init(640, 640, "zjop", 0);
	tex = mlx_load_png("./assets/wall.png");
	if (!tex)
		printf("No texture.\n");
	buf = mlx_new_image(mlx, 640, 640);
	int pix = get_texture_pixel_data(32, 32, tex);
	printf("%x\n", pix);
	mlx_put_pixel(buf, 1, 1, pix);
	mlx_image_to_window(mlx, buf, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
