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

/* Movement speed & rotation speed. */
#define MOVS 0.05
#define ROTS 0.05

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

	has_moved = false;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x + rc->dv.x * MOVS)] != '1')
			rc->campos.x += rc->dv.x * MOVS;
		if (m[(int)(rc->campos.y + rc->dv.y * MOVS)][(int)rc->campos.x] != '1')
			rc->campos.y += rc->dv.y * MOVS;
		has_moved = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x - rc->dv.x * MOVS)] != '1')
			rc->campos.x -= rc->dv.x * MOVS;
		if (m[(int)(rc->campos.y - rc->dv.y * MOVS)][(int)rc->campos.x] != '1')
			rc->campos.y -= rc->dv.y * MOVS;
		has_moved = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cosf(-ROTS) - rc->dv.y * sinf(-ROTS);
		rc->dv.y = old_dir_x * sinf(-ROTS) + rc->dv.y * cosf(-ROTS);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cosf(-ROTS) - rc->pv.y * sinf(-ROTS);
		rc->pv.y = old_plane_x * sinf(-ROTS) + rc->pv.y * cosf(-ROTS);
		has_moved = true;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cosf(ROTS) - rc->dv.y * sinf(ROTS);
		rc->dv.y = old_dir_x * sinf(ROTS) + rc->dv.y * cosf(ROTS);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cosf(ROTS) - rc->pv.y * sinf(ROTS);
		rc->pv.y = old_plane_x * sinf(ROTS) + rc->pv.y * cosf(ROTS);
		has_moved = true;
	}
	printf("dv.x: %f | dv.y %f\n", rc->dv.x, rc->dv.y);
	printf("pv.x: %f | pv.y %f\n", rc->pv.x, rc->pv.y);
	return (has_moved);
}
