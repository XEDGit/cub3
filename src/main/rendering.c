#include "../../includes/rendering.h"
#include "../../includes/shared.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

static void	setup_step_direction(t_rayvars *ray, t_raycam *rayCam)
{
	if (ray->raydir.x < 0)
	{
		ray->stepdirection.x = -1;
		ray->sidedistances.x = \
			(rayCam->campos.x - ray->int_map_coords.x) * ray->deltads.x;
	}
	else
	{
		ray->stepdirection.x = 1;
		ray->sidedistances.x = \
			(ray->int_map_coords.x + 1.0 - rayCam->campos.x) * ray->deltads.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->stepdirection.y = -1;
		ray->sidedistances.y = \
			(rayCam->campos.y - ray->int_map_coords.y) * ray->deltads.y;
	}
	else
	{
		ray->stepdirection.y = 1;
		ray->sidedistances.y = \
			(ray->int_map_coords.y + 1.0 - rayCam->campos.y) * ray->deltads.y;
	}
}

// DDA Algorithm.
static int	cast_till_hit(t_rayvars *ray, char **map)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedistances.x < ray->sidedistances.y)
		{
			ray->sidedistances.x += ray->deltads.x;
			ray->int_map_coords.x += ray->stepdirection.x;
			side = 0;
		}
		else
		{
			ray->sidedistances.y += ray->deltads.y;
			ray->int_map_coords.y += ray->stepdirection.y;
			side = 1;
		}
		if (map[ray->int_map_coords.y][ray->int_map_coords.x] == '1')
			hit = 1;
	}
	return (side);
}

static t_vertline	generate_line(t_rayvars *ray, char **map, int x, int side)
{
	t_vertline	result;
	double		perpwalldist;
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wall_x;

	if (side == 0)
		perpwalldist = (ray->sidedistances.x - ray->deltads.x);
	else
		perpwalldist = (ray->sidedistances.y - ray->deltads.y);
	lineheight = ((WIN_HEIGHT / perpwalldist));
	drawstart = -lineheight / 2 + WIN_HEIGHT / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + WIN_HEIGHT / 2;
	if (drawend >= WIN_HEIGHT)
		drawend = WIN_HEIGHT - 1;
	result.xcoord = x;
	result.startpoint = drawstart;
	result.endpoint = drawend;
	if (side == 0)
		wall_x = ray->int_map_coords.y + perpwalldist * ray->raydir.y;
	else
		wall_x = ray->int_map_coords.x + perpwalldist * ray->raydir.x;
	wall_x -= floor((wall_x));
	//x coordinate on the texture
	result.tex_x = (int)(wall_x * (double)64);
	if (side == 0 && ray->raydir.x > 0)
		result.tex_x = 64 - result.tex_x - 1;
	if (side == 1 && ray->raydir.y < 0)
		result.tex_x = 64 - result.tex_x - 1;
	result.tex_y_step = 1.0 * 64 / lineheight;
	result.tex_y_begin_pos = (drawstart - (WIN_HEIGHT / 2) + (lineheight / 2)) * result.tex_y_step;
	result.side = side;
	return (result);
}

t_vertline	cast_ray(t_raycam *raycam, t_map *map, int x)
{
	t_rayvars	ray;
	int			side;

	ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray.raydir.x = raycam->dv.x + raycam->pv.x * ray.camera_x;
	ray.raydir.y = raycam->dv.y + raycam->pv.y * ray.camera_x;
	ray.int_map_coords = (t_intvec2){ (int)raycam->campos.x, (int)raycam->campos.y };
	ray.deltads = (t_vec2){ fabs(1 / ray.raydir.x), fabs(1 / ray.raydir.y) };
	setup_step_direction(&ray, raycam);
	side = cast_till_hit(&ray, map->maps[0].map); // TODO: Replace 0 with current map.
	return (generate_line(&ray, map->maps[0].map, x, side));
}

void	draw_vert(t_vertline line, mlx_image_t *image, mlx_texture_t *tex)
{
	static int shiftamount;
	int	iter;
	int	colour;

	if (line.startpoint >= WIN_HEIGHT || line.endpoint < 0 \
		|| line.xcoord < 0 || line.xcoord >= WIN_WIDTH)
		return ;
	if (line.startpoint < 0)
		line.startpoint = 0;
	if (line.endpoint >= WIN_HEIGHT)
		line.endpoint = WIN_HEIGHT - 1;
	iter = line.startpoint;
	while (iter <= line.endpoint)
	{
		line.tex_y = (int)line.tex_y_begin_pos & (64 - 1);
		line.tex_y_begin_pos += line.tex_y_step;
		colour = get_texture_pixel_data(line.tex_x, line.tex_y, tex);
		if (shiftamount == 2)
			shiftamount = 0;
		else
			shiftamount++;
		if (line.side == 1)
			colour = (colour << shiftamount);
		mlx_put_pixel(image, line.xcoord, iter, colour);
		iter++;
	}
}

void	handle_input(mlx_key_data_t key, t_raycam *raycam, char **map)
{
	float move_speed = 0.05;
	float rot_speed = 0.05;
	double	old_dir_x;
	double	old_plane_x;

	if (key.key == MLX_KEY_UP && (key.action == MLX_REPEAT || key.action == MLX_PRESS)) {
		if (map[(int)raycam->campos.y][(int)(raycam->campos.x + raycam->dv.x * move_speed)] != '1')
			raycam->campos.x += raycam->dv.x * move_speed;
		if (map[(int)(raycam->campos.y + raycam->dv.y * move_speed)][(int)raycam->campos.x] != '1')
			raycam->campos.y += raycam->dv.y * move_speed;
	}
	if (key.key == MLX_KEY_DOWN && (key.action == MLX_REPEAT || key.action == MLX_PRESS)) {
		if (map[(int)raycam->campos.y][(int)(raycam->campos.x - raycam->dv.x * move_speed)] != '1')
			raycam->campos.x -= raycam->dv.x * move_speed;
		if (map[(int)(raycam->campos.y - raycam->dv.y * move_speed)][(int)raycam->campos.x] != '1')
			raycam->campos.y -= raycam->dv.y * move_speed;
	}
	if (key.key == MLX_KEY_RIGHT && (key.action == MLX_REPEAT || key.action == MLX_PRESS)) {
		old_dir_x = raycam->dv.x;
		raycam->dv.x = raycam->dv.x * cos(-rot_speed) - raycam->dv.y * sin(-rot_speed);
		raycam->dv.y = old_dir_x * sin(-rot_speed) + raycam->dv.y * cos(-rot_speed);
		old_plane_x = raycam->pv.x;
		raycam->pv.x = raycam->pv.x * cos(-rot_speed) - raycam->pv.y * sin(-rot_speed);
		raycam->pv.y = old_plane_x * sin(-rot_speed) + raycam->pv.y * cos(-rot_speed);
	}
	if (key.key == MLX_KEY_LEFT && (key.action == MLX_REPEAT || key.action == MLX_PRESS)) {
		old_dir_x = raycam->dv.x;
		raycam->dv.x = raycam->dv.x * cos(rot_speed) - raycam->dv.y * sin(rot_speed);
		raycam->dv.y = old_dir_x * sin(rot_speed) + raycam->dv.y * cos(rot_speed);
		old_plane_x = raycam->pv.x;
		raycam->pv.x = raycam->pv.x * cos(rot_speed) - raycam->pv.y * sin(rot_speed);
		raycam->pv.y = old_plane_x * sin(rot_speed) + raycam->pv.y * cos(rot_speed);
	}
}

void	render_frame(t_raycam *raycam, mlx_image_t *image, t_map *map, mlx_texture_t *tex)
{
	for (int x = 0; x <= WIN_WIDTH; x++)
		draw_vert(cast_ray(raycam, map, x), image, tex);
}
