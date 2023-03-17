/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movement.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "../../includes/rendering.h"

int	forward_backward(t_raycam *rc, char **m, mlx_t *mlx, int dir)
{
	double	movs;

	movs = mlx->delta_time * 4.0;
	if (dir == 1)
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x + rc->dv.x * movs)] != '1')
			rc->campos.x += rc->dv.x * movs;
		if (m[(int)(rc->campos.y + rc->dv.y * movs)][(int)rc->campos.x] != '1')
			rc->campos.y += rc->dv.y * movs;
	}
	if (dir == 0)
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x - rc->dv.x * movs)] != '1')
			rc->campos.x -= rc->dv.x * movs;
		if (m[(int)(rc->campos.y - rc->dv.y * movs)][(int)rc->campos.x] != '1')
			rc->campos.y -= rc->dv.y * movs;
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
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		has_moved = forward_backward(rc, m, mlx, 1);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		has_moved = forward_backward(rc, m, mlx, 0);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		has_moved = left_right(rc, 1, mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		has_moved = left_right(rc, 0, mlx);
	return (has_moved);
}
