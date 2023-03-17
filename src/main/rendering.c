/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rendering.h"
#include "../../includes/shared.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static void	setup_step_direction(t_rayvars *ray, t_raycam *rayCam)
{
	if (ray->rdir.x < 0)
	{
		ray->stepdirection.x = -1;
		ray->sidedistances.x = \
			(rayCam->campos.x - ray->imapcoords.x) * ray->deltads.x;
	}
	else
	{
		ray->stepdirection.x = 1;
		ray->sidedistances.x = \
			(ray->imapcoords.x + 1.0 - rayCam->campos.x) * ray->deltads.x;
	}
	if (ray->rdir.y < 0)
	{
		ray->stepdirection.y = -1;
		ray->sidedistances.y = \
			(rayCam->campos.y - ray->imapcoords.y) * ray->deltads.y;
	}
	else
	{
		ray->stepdirection.y = 1;
		ray->sidedistances.y = \
			(ray->imapcoords.y + 1.0 - rayCam->campos.y) * ray->deltads.y;
	}
}

// DDA Algorithm.
static int	cast_till_hit(t_rayvars *ray, char **map)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedistances.x < ray->sidedistances.y)
		{
			ray->sidedistances.x += ray->deltads.x;
			ray->imapcoords.x += ray->stepdirection.x;
			side = 0;
		}
		else
		{
			ray->sidedistances.y += ray->deltads.y;
			ray->imapcoords.y += ray->stepdirection.y;
			side = 1;
		}
		if (map[ray->imapcoords.y][ray->imapcoords.x] == '1')
			hit = 1;
	}
	return (side);
}

// TODO: Replace 0 with current map.
t_vertline	cast_ray(t_renderer *rn, int x)
{
	int			side;
	t_rayvars	*rv;

	rv = rn->rv;
	rv->camera_x = 2 * x / (double)W - 1;
	rv->rdir.x = rn->rc->dv.x + rn->rc->pv.x * rv->camera_x;
	rv->rdir.y = rn->rc->dv.y + rn->rc->pv.y * rv->camera_x;
	rv->imapcoords = (t_ivec){(int)rn->rc->campos.x, (int)rn->rc->campos.y};
	rv->deltads = (t_vec2){fabs(1 / rv->rdir.x), fabs(1 / rv->rdir.y)};
	setup_step_direction(rv, rn->rc);
	side = cast_till_hit(rv, rn->map->maps[0].map);
	return (generate_line(rn, rn->map->maps[0].map, x, side));
}

void	draw_vert(t_vertline line, mlx_image_t *image, mlx_texture_t *tex)
{
	int			iter;
	int			colour;

	if (line.startpoint >= H || line.endpoint < 0 \
		|| line.xcoord < 0 || line.xcoord >= W)
		return ;
	if (line.startpoint < 0)
		line.startpoint = 0;
	if (line.endpoint >= H)
		line.endpoint = H - 1;
	iter = line.startpoint;
	while (iter <= line.endpoint)
	{
		line.tex_y = (int)line.tex_y_begin_pos & (TH - 1);
		line.tex_y_begin_pos += line.step;
		colour = get_texture_pixel_data(line.tex_x, line.tex_y, tex);
		mlx_put_pixel(image, line.xcoord, iter, colour);
		iter++;
	}
}
