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
#include <string.h>

int	texdata_to_int(uint8_t *texdata)
{
	int	colour;

	colour = 0;
	colour = \
		(texdata[0] << 24 | texdata[1] << 16 | texdata[2] << 8 | texdata[3]);
	return (colour);
}

int	get_texture_pixel_data(int x, int y, mlx_texture_t *tex)
{
	uint8_t	*pixptr;

	pixptr = &tex->pixels[(x + tex->width * y) * tex->bytes_per_pixel];
	return (texdata_to_int(pixptr));
}

void	render_hook(void *data)
{
	t_renderer	*renderer;

	renderer = data;
	renderer->has_moved = \
		handle_input(renderer->rc, renderer->map->maps->map, renderer->mlx);
	if (renderer->has_moved == -1)
	{
		dealloc_renderer(renderer);
		exit(0);
	}
	else if (renderer->has_moved)
	{
		render_frame(renderer);
		renderer->has_moved = 0;
	}
}

static void	floor_ceiling(t_renderer *rn, t_map *m)
{
	unsigned int	iter_y;
	unsigned int	iter_x;

	iter_y = 0;
	while (iter_y < rn->image->height)
	{
		iter_x = 0;
		while (iter_x < rn->image->width)
		{
			if (iter_y < rn->image->height / 2)
				mlx_put_pixel(rn->image, iter_x, iter_y, m->ceiling);
			else
				mlx_put_pixel(rn->image, iter_x, iter_y, m->floor);
			iter_x++;
		}
		iter_y++;
	}
}

void	render_frame(t_renderer *rn)
{
	int	iter;

	iter = 0;
	floor_ceiling(rn, rn->map);
	while (iter <= W)
	{
		draw_vert(cast_ray(rn, iter), rn->image, rn->tex);
		iter++;
	}
}
