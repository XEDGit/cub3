/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering_utils.c                                  :+:    :+:            */
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

void	input_keyhook(mlx_key_data_t keydata, void *data)
{
	t_renderer	*mapcam;

	mapcam = data;
	if (!mapcam)
		return ;
	mapcam->has_moved = 1;
	handle_input(keydata, \
			mapcam->raycam, mapcam->map->maps->map);
}

void	render_hook(void *data)
{
	t_renderer	*renderer;

	renderer = data;
	if (renderer->has_moved)
	{
		render_frame(renderer->raycam, \
							renderer->image, renderer->map, renderer->tex);
		renderer->has_moved = 0;
	}
}

/* TODO: Replace memset with ft_memset. */
void	render_frame(t_raycam *rc, mlx_image_t *i, t_map *m, mlx_texture_t *t)
{
	int	iter;

	iter = 0;
	memset(i->pixels, 0, i->height * i->width * 4);
	while (iter <= W)
	{
		draw_vert(cast_ray(rc, m, iter), i, t);
		iter++;
	}
}
