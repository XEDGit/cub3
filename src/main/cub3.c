/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   A C file... Shocker!                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
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

void	dealloc_renderer(t_renderer *rn)
{
	int	iter;

	iter = 0;
	mlx_delete_image(rn->mlx, rn->image);
	while (iter < 4)
	{
		mlx_delete_texture(rn->tex[iter]);
		iter++;
	}
	mlx_terminate(rn->mlx);
	free_map(rn->map);
}

void	init_renderer(mlx_t *mlx, t_renderer *rn, t_data *data)
{
	int		iter;
	char	dir;

	iter = 0;
	dir = \
		data->map.maps->map[data->map.maps->spawn[1]][data->map.maps->spawn[0]];
	init_raycam(&rn->rc, data->map.maps->spawn[0], \
						data->map.maps->spawn[1], dir);
	rn->image = mlx_new_image(mlx, W, H);
	mlx_image_to_window(mlx, rn->image, 0, 0);
	while (iter < 4)
	{
		rn->tex[iter] = mlx_load_png(data->map.textures[iter]);
		if (iter > 0 && (rn->tex[iter]->height != rn->tex[0]->height || \
		rn->tex[iter]->width != rn->tex[0]->width))
		{
			printf("[%s] is invalid.\n", data->map.textures[iter]);
			return ;
		}
		iter++;
	}
	rn->th = rn->tex[0]->height;
	rn->tw = rn->tex[0]->width;
	rn->map = &data->map;
	mlx_loop_hook(mlx, render_hook, rn);
}

int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_data			data;
	t_renderer		renderer;

	data = (t_data){{{0}, 0, 0, 0, {0}}, 0};
	if (!(parse_args(&data.map, argc, argv) && \
		check_map(&data.map)))
	{
		mlx = mlx_init(W, H, "cub3d", 0);
		renderer.has_moved = 1;
		renderer.mlx = mlx;
		init_renderer(mlx, &renderer, &data);
		mlx_loop(mlx);
		dealloc_renderer(&renderer);
		return (0);
	}
	free_map(&data.map);
	return (0);
}
