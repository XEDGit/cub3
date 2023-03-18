/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycam.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by wmaguire          #+#    #+#             */
/*   Updated: 2023/03/18 22:51:55 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>
#include <rendering.h>
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
