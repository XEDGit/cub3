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

#include "../../includes/shared.h"
#include "../../includes/rendering.h"
#include <stdlib.h>

t_raycam	*init_raycam(t_raycam *raycam, int x, int y, char dir)
{
	if (dir == 'N')
	{
		raycam->dv = (t_vec2){0, -1};
		raycam->pv = (t_vec2){-0.66, 0};
	}
	if (dir == 'S')
	{
		raycam->dv = (t_vec2){0, 1};
		raycam->pv = (t_vec2){0.66, 0};
	}
	else if (dir == 'W')
	{
		raycam->dv = (t_vec2){-1, 0};
		raycam->pv = (t_vec2){0, 0.66};
	}
	else if (dir == 'E')
	{
		raycam->dv = (t_vec2){1, 0};
		raycam->pv = (t_vec2){0, -0.66};
	}
	raycam->campos = (t_vec2){x + 0.5, y + 0.5};
	return (raycam);
}
