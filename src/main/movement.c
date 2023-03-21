/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmaguire <wmaguire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by wmaguire          #+#    #+#             */
/*   Updated: 2023/03/18 22:51:01 by wmaguire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "../../includes/rendering.h"

int	forward_backward(t_raycam *rc, char **m, mlx_t *mlx, int dir)
{
	double	movs;
	t_vec2	nextpos;

	movs = mlx->delta_time * 4.0;
	if (dir == 1)
	{
		nextpos.x = rc->campos.x + (rc->dv.x * movs);
		nextpos.y = rc->campos.y + (rc->dv.y * movs);
		if (m[(int)rc->campos.y][(int)(nextpos.x)] != '1')
			rc->campos.x = nextpos.x;
		if (m[(int)(nextpos.y)][(int)rc->campos.x] != '1')
			rc->campos.y = nextpos.y;
	}
	if (dir == 0)
	{
		nextpos.x = rc->campos.x - (rc->dv.x * movs);
		nextpos.y = rc->campos.y - (rc->dv.y * movs);
		if (m[(int)rc->campos.y][(int)(nextpos.x)] != '1')
			rc->campos.x = nextpos.x;
		if (m[(int)(nextpos.y)][(int)rc->campos.x] != '1')
			rc->campos.y = nextpos.y;
	}
	return (1);
}

int	left_right(t_raycam *rc, int dir, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rots;

	rots = mlx->delta_time * 2.0;
	if (dir == 1)
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cosf(-rots) - rc->dv.y * sinf(-rots);
		rc->dv.y = old_dir_x * sinf(-rots) + rc->dv.y * cosf(-rots);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cosf(-rots) - rc->pv.y * sinf(-rots);
		rc->pv.y = old_plane_x * sinf(-rots) + rc->pv.y * cosf(-rots);
	}
	else if (dir == 0)
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cosf(rots) - rc->dv.y * sinf(rots);
		rc->dv.y = old_dir_x * sinf(rots) + rc->dv.y * cosf(rots);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cosf(rots) - rc->pv.y * sinf(rots);
		rc->pv.y = old_plane_x * sinf(rots) + rc->pv.y * cosf(rots);
	}
	return (1);
}

int	handle_input(t_raycam *rc, char **m, mlx_t *mlx)
{
	int		has_moved;

	has_moved = false;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		has_moved = forward_backward(rc, m, mlx, 1);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		has_moved = forward_backward(rc, m, mlx, 0);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		has_moved = left_right(rc, 1, mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		has_moved = left_right(rc, 0, mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		return (-1);
	return (has_moved);
}
