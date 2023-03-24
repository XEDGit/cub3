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

#include "../../includes/rendering.h"
#include <stdio.h>

static char	get_dir(t_single_map *map)
{
	t_ivec	spawn;

	spawn.x = map->spawn[0];
	spawn.y = map->spawn[1];
	return(map->map[spawn.y][spawn.x]);
}

static int	check_tex_dims(mlx_texture_t **textures)
{
	int	width;
	int	height;
	int	iter;

	iter = 0;
	width = textures[0]->width;
	height = textures[0]->height;
	while (iter < 4)
	{
		if (textures[iter]->width != width || textures[iter]->height != height)
			return (false);
		iter++;
	}
	return (true);
}

void	init_renderer(mlx_t *mlx, t_renderer *rn, t_data *data)
{
	int		iter;
	char	dir;

	iter = 0;
	dir = get_dir(data->map.maps);
	init_raycam(&rn->rc, data->map.maps->spawn[0], \
						data->map.maps->spawn[1], dir);
	rn->image = mlx_new_image(mlx, W, H);
	mlx_image_to_window(mlx, rn->image, 0, 0);
	while (iter < 4)
	{
		rn->tex[iter] = mlx_load_png(data->map.textures[iter]);
		iter++;
	}
	if (!check_tex_dims(rn->tex))
	{
		dealloc_renderer(rn);
		return ;
	}
	rn->th = rn->tex[0]->height;
	rn->tw = rn->tex[0]->width;
	rn->map = &data->map;
	mlx_loop_hook(mlx, render_hook, rn);
}
