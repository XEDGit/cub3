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

#include <shared.h>
#include "../../includes/rendering.h"
#include <stdlib.h>

t_raycam	*init_raycam(int x, int y)
{
	t_raycam	*raycam;

	raycam = malloc(sizeof(t_raycam));
	if (!raycam)
		return (NULL);
	raycam->dv = (t_vec2){0, -1};
	raycam->pv = (t_vec2){-0.66, 0};
	raycam->campos = (t_vec2){x, y};
	return (raycam);
}
