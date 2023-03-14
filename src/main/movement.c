#include <math.h>
#include "../../includes/rendering.h"

#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05

void	forward_backward(mlx_key_data_t key, t_raycam *raycam, char **map)
{
	if (key.key == MLX_KEY_UP && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
	{
		if (map[(int)raycam->campos.y][(int)(raycam->campos.x + raycam->dv.x * MOVE_SPEED)] != '1')
			raycam->campos.x += raycam->dv.x * MOVE_SPEED;
		if (map[(int)(raycam->campos.y + raycam->dv.y * MOVE_SPEED)][(int)raycam->campos.x] != '1')
			raycam->campos.y += raycam->dv.y * MOVE_SPEED;
	}
	if (key.key == MLX_KEY_DOWN && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
	{
		if (map[(int)raycam->campos.y][(int)(raycam->campos.x - raycam->dv.x * MOVE_SPEED)] != '1')
			raycam->campos.x -= raycam->dv.x * MOVE_SPEED;
		if (map[(int)(raycam->campos.y - raycam->dv.y * MOVE_SPEED)][(int)raycam->campos.x] != '1')
			raycam->campos.y -= raycam->dv.y * MOVE_SPEED;
	}
}

void	left_right(mlx_key_data_t key, t_raycam *raycam, char **map)
{
	double	old_dir_x;
	double	old_plane_x;

	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
	{
		old_dir_x = raycam->dv.x;
		raycam->dv.x = raycam->dv.x * cos(-ROT_SPEED) - raycam->dv.y * sin(-ROT_SPEED);
		raycam->dv.y = old_dir_x * sin(-ROT_SPEED) + raycam->dv.y * cos(-ROT_SPEED);
		old_plane_x = raycam->pv.x;
		raycam->pv.x = raycam->pv.x * cos(-ROT_SPEED) - raycam->pv.y * sin(-ROT_SPEED);
		raycam->pv.y = old_plane_x * sin(-ROT_SPEED) + raycam->pv.y * cos(-ROT_SPEED);
	}
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_REPEAT || key.action == MLX_PRESS))
	{
		old_dir_x = raycam->dv.x;
		raycam->dv.x = raycam->dv.x * cos(ROT_SPEED) - raycam->dv.y * sin(ROT_SPEED);
		raycam->dv.y = old_dir_x * sin(ROT_SPEED) + raycam->dv.y * cos(ROT_SPEED);
		old_plane_x = raycam->pv.x;
		raycam->pv.x = raycam->pv.x * cos(ROT_SPEED) - raycam->pv.y * sin(ROT_SPEED);
		raycam->pv.y = old_plane_x * sin(ROT_SPEED) + raycam->pv.y * cos(ROT_SPEED);
	}
}

void	handle_input(mlx_key_data_t key, t_raycam *raycam, char **map)
{
	if (key.key == MLX_KEY_UP || key.key == MLX_KEY_DOWN)
		forward_backward(key, raycam, map);
	else if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
		left_right(key, raycam, map);
}
