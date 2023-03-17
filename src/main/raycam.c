/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycam.c                                           :+:    :+:            */
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

t_raycam	*init_raycam(int x, int y)
{
	t_raycam	*raycam;

	raycam = malloc(sizeof(t_raycam));
	if (!raycam)
		return (NULL);
	raycam->dv = (t_vec2){-1, 0};
	raycam->pv = (t_vec2){0, 0.66};
	raycam->campos = (t_vec2){x, y};
	return (raycam);
}
