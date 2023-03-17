/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   linegen.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rendering.h"
#include <math.h>

#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

static void	tex_coords(t_renderer *rn, int side, int x, t_vertline *r)
{
	double	wall_x;
	double	perpwalldist;
	int		lineheight;

	if (side == 0)
		perpwalldist = (rn->rv->sidedistances.x - rn->rv->deltads.x);
	else
		perpwalldist = (rn->rv->sidedistances.y - rn->rv->deltads.y);
	lineheight = ((H / perpwalldist));
	if (side == 0)
		wall_x = rn->rc->campos.y + perpwalldist * rn->rv->rdir.y;
	else
		wall_x = rn->rc->campos.x + perpwalldist * rn->rv->rdir.x;
	wall_x -= floor((wall_x));
	r->tex_x = (int)(wall_x * (double)TW);
	if (side == 0 && rn->rv->rdir.x > 0)
		r->tex_x = TW - r->tex_x - 1;
	if (side == 1 && rn->rv->rdir.y < 0)
		r->tex_x = TW - r->tex_x - 1;
	r->step = 1.0 * TH / lineheight;
	r->tex_y_begin_pos = (r->startpoint - (H / 2) + (lineheight / 2)) * r->step;
	r->side = side;
}

t_vertline	generate_line(t_renderer *rn, char **map, int x, int side)
{
	t_vertline	r;
	double		perpwalldist;
	int			lineheight;
	double		wall_x;

	if (side == 0)
		perpwalldist = (rn->rv->sidedistances.x - rn->rv->deltads.x);
	else
		perpwalldist = (rn->rv->sidedistances.y - rn->rv->deltads.y);
	lineheight = ((H / perpwalldist));
	r.startpoint = -lineheight / 2 + H / 2;
	if (r.startpoint < 0)
		r.startpoint = 0;
	r.endpoint = lineheight / 2 + H / 2;
	if (r.endpoint >= H)
		r.endpoint = H - 1;
	r.xcoord = x;
	tex_coords(rn, side, x, &r);
	if (side == 1)
	{
		if (rn->rv->rdir.y < 0)
			r.dir = NORTH;
		else
			r.dir = SOUTH;
	}
	else
	{
		if (rn->rv->rdir.x < 0)
			r.dir = WEST;
		else
			r.dir = EAST;
	}
	return (r);
}
