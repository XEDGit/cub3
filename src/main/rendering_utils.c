/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmaguire <wmaguire@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by wmaguire          #+#    #+#             */
/*   Updated: 2023/03/18 22:51:01 by wmaguire           ###   ########.fr       */
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
	if (renderer->has_moved)
	{
		render_frame(renderer, \
					renderer->image, renderer->map, renderer->tex);
		renderer->has_moved = 0;
	}
}

void	render_frame(t_renderer *rn, \
				mlx_image_t *i, t_map *m, mlx_texture_t **t)
{
	int	iter;

	iter = 0;
	while (iter <= W)
	{
		draw_vert(cast_ray(rn, iter), i, t, m);
		iter++;
	}
}
