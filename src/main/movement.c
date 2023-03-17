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

/* void	forward_backward(mlx_key_data_t k, t_raycam *rc, char **m, mlx_t *mlx) */
/* { */
/* } */

/* void	left_right(mlx_key_data_t k, t_raycam *rc, char **m, mlx_t *mlx) */
/* { */
/* } */

int	handle_input(t_raycam *rc, char **m, mlx_t *mlx)
{
	int		has_moved;
	double	old_dir_x;
	double	old_plane_x;
	double	movs;
	double	rots;

	movs = mlx->delta_time * 4.0;
	rots = mlx->delta_time * 2.0;
	has_moved = false;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x + rc->dv.x * movs)] != '1')
			rc->campos.x += rc->dv.x * movs;
		if (m[(int)(rc->campos.y + rc->dv.y * movs)][(int)rc->campos.x] != '1')
			rc->campos.y += rc->dv.y * movs;
		has_moved = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x - rc->dv.x * movs)] != '1')
			rc->campos.x -= rc->dv.x * movs;
		if (m[(int)(rc->campos.y - rc->dv.y * movs)][(int)rc->campos.x] != '1')
			rc->campos.y -= rc->dv.y * movs;
		has_moved = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cosf(-rots) - rc->dv.y * sinf(-rots);
		rc->dv.y = old_dir_x * sinf(-rots) + rc->dv.y * cosf(-rots);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cosf(-rots) - rc->pv.y * sinf(-rots);
		rc->pv.y = old_plane_x * sinf(-rots) + rc->pv.y * cosf(-rots);
		has_moved = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cosf(rots) - rc->dv.y * sinf(rots);
		rc->dv.y = old_dir_x * sinf(rots) + rc->dv.y * cosf(rots);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cosf(rots) - rc->pv.y * sinf(rots);
		rc->pv.y = old_plane_x * sinf(rots) + rc->pv.y * cosf(rots);
		has_moved = true;
	}
	return (has_moved);
}
