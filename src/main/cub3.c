/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/17 14:54:14 by lmuzio        #+#    #+#                 */
/*   Updated: 2023/03/11 18:53:16 by lmuzio        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3.h"
#include "../../includes/rendering.h"
#include <string.h>

bool	error(char *msg, void *msg_arg, bool perr)
{
	char	*arg_ptr;

	printf("Error\n");
	arg_ptr = ft_strchr(msg, '%');
	if (perr && msg)
		perror(msg);
	else if (msg && arg_ptr)
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

void	init_renderer(mlx_t *mlx, t_renderer *renderer, t_data *data)
{
	renderer->rc = init_raycam(data->map.maps->spawn[0], \
									data->map.maps->spawn[1]);
	renderer->rv = malloc(sizeof(t_rayvars));
	if (!renderer->rv)
		return ;
	renderer->image = mlx_new_image(mlx, W, H);
	mlx_image_to_window(mlx, renderer->image, 0, 0);
	renderer->tex = mlx_load_png("./assets/wall.png");
	renderer->map = &data->map;
	renderer->has_moved = 1;
	mlx_loop_hook(mlx, render_hook, renderer);
	mlx_key_hook(mlx, input_keyhook, renderer);
}

int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_data			data;
	t_renderer		renderer;

	data = (t_data){{{0}, 0, 0, 0, {0}}, 0};
	if (parse_args(&data.map, argc, argv))
		(void)data;
	else if (check_map(&data.map))
		(void)data;
	else if (1)
	{
		mlx = mlx_init(W, H, "cub3d", 0);
		init_renderer(mlx, &renderer, &data);
		mlx_loop(mlx);
		mlx_terminate(mlx);
	}
	free_map(&data.map);
	return (0);
}
