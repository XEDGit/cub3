#include <math.h>
#include "../../includes/rendering.h"

/* Movement speed & rotation speed. */
#define MOVS 0.05
#define ROTS 0.05

void	forward_backward(mlx_key_data_t k, t_raycam *rc, char **m)
{
	if (k.key == MLX_KEY_UP
		&& (k.action == MLX_REPEAT || k.action == MLX_PRESS))
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x + rc->dv.x * MOVS)] != '1')
			rc->campos.x += rc->dv.x * MOVS;
		if (m[(int)(rc->campos.y + rc->dv.y * MOVS)][(int)rc->campos.x] != '1')
			rc->campos.y += rc->dv.y * MOVS;
	}
	if (k.key == MLX_KEY_DOWN
		&& (k.action == MLX_REPEAT || k.action == MLX_PRESS))
	{
		if (m[(int)rc->campos.y][(int)(rc->campos.x - rc->dv.x * MOVS)] != '1')
			rc->campos.x -= rc->dv.x * MOVS;
		if (m[(int)(rc->campos.y - rc->dv.y * MOVS)][(int)rc->campos.x] != '1')
			rc->campos.y -= rc->dv.y * MOVS;
	}
}

void	left_right(mlx_key_data_t k, t_raycam *rc, char **m)
{
	double	old_dir_x;
	double	old_plane_x;

	if (k.key == MLX_KEY_RIGHT
		&& (k.action == MLX_REPEAT || k.action == MLX_PRESS))
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cos(-ROTS) - rc->dv.y * sin(-ROTS);
		rc->dv.y = old_dir_x * sin(-ROTS) + rc->dv.y * cos(-ROTS);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cos(-ROTS) - rc->pv.y * sin(-ROTS);
		rc->pv.y = old_plane_x * sin(-ROTS) + rc->pv.y * cos(-ROTS);
	}
	if (k.key == MLX_KEY_LEFT
		&& (k.action == MLX_REPEAT || k.action == MLX_PRESS))
	{
		old_dir_x = rc->dv.x;
		rc->dv.x = rc->dv.x * cos(ROTS) - rc->dv.y * sin(ROTS);
		rc->dv.y = old_dir_x * sin(ROTS) + rc->dv.y * cos(ROTS);
		old_plane_x = rc->pv.x;
		rc->pv.x = rc->pv.x * cos(ROTS) - rc->pv.y * sin(ROTS);
		rc->pv.y = old_plane_x * sin(ROTS) + rc->pv.y * cos(ROTS);
	}
}

void	handle_input(mlx_key_data_t key, t_raycam *raycam, char **map)
{
	if (key.key == MLX_KEY_UP || key.key == MLX_KEY_DOWN)
		forward_backward(key, raycam, map);
	else if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
		left_right(key, raycam, map);
}
