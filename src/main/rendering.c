#include "../../includes/rendering.h"
#include "../../includes/shared.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

static void	setup_step_direction(t_rayvars *ray, t_raycam *rayCam) {
	if (ray->raydir.x < 0) {
		ray->stepdirection.x = -1;
		ray->sidedistances.x = (rayCam->campos.x - ray->int_map_coords.x) * ray->deltadistances.x;
	}
	else {
		ray->stepdirection.x = 1;
		ray->sidedistances.x = (ray->int_map_coords.x + 1.0 - rayCam->campos.x) * ray->deltadistances.x;
	}
	if (ray->raydir.y < 0) {
		ray->stepdirection.y = -1;
		ray->sidedistances.y = (rayCam->campos.y - ray->int_map_coords.y) * ray->deltadistances.y;
	} else {
		ray->stepdirection.y = 1;
		ray->sidedistances.y = (ray->int_map_coords.y + 1.0 - rayCam->campos.y) * ray->deltadistances.y;
	}
}

// DDA Algorithm.
static int cast_till_hit(t_rayvars *ray, char **map) {
	int	hit = 0;
	int	side;

	while (hit == 0) {
		if (ray->sidedistances.x < ray->sidedistances.y)
		{
			ray->sidedistances.x += ray->deltadistances.x;
			ray->int_map_coords.x += ray->stepdirection.x;
			side = 0;
		}
		else
		{
			ray->sidedistances.y += ray->deltadistances.y;
			ray->int_map_coords.y += ray->stepdirection.y;
			side = 1;
		}
		if (map[ray->int_map_coords.y][ray->int_map_coords.x] == '1')
			hit = 1;
	}
	return (side);
}

static t_vertline generate_line(t_rayvars *ray, char **map, int x, int side) {
	t_vertline	result;
	double		perpWallDist;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;

	if (side == 0)
		perpWallDist = (ray->sidedistances.x - ray->deltadistances.x);
	else
		perpWallDist = (ray->sidedistances.y - ray->deltadistances.y);
	lineHeight = (int)((WIN_HEIGHT / perpWallDist));
	drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	result.xcoord = x;
	result.startpoint = drawStart;
	result.endpoint = drawEnd;

	double wallX; //where exactly the wall was hit
	if (side == 0) wallX = ray->int_map_coords.y + perpWallDist * ray->raydir.y;
	else           wallX = ray->int_map_coords.x + perpWallDist * ray->raydir.x;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int texX = (int)wallX * (double)64;
	if(side == 0 && ray->raydir.x > 0) texX = 64 - texX - 1;
	if(side == 1 && ray->raydir.y < 0) texX = 64 - texX - 1;

	double step = 1.0 * 64 / lineHeight;
	double texPos = (drawStart - (double)WIN_HEIGHT / 2 + (double)lineHeight / 2) * step;
	result.tex_begin_pos = texPos;
	result.tex_ystep = step;

	result.wall_xcoord = texX;
	return (result);
}

t_vertline castRay(t_raycam raycam, t_map *map, int x) {
	t_rayvars	ray;
	int			side;

	ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray.raydir.x = raycam.dv.x + raycam.pv.x * ray.camera_x;
	ray.raydir.y = raycam.dv.y + raycam.pv.y * ray.camera_x;
	ray.int_map_coords = (t_intvec2){ (int)raycam.campos.x, (int)raycam.campos.y };
	ray.deltadistances = (t_vec2){ abs((int)(1 / ray.raydir.x)), abs((int)(1 / ray.raydir.y)) };
	setup_step_direction(&ray, &raycam);
	side = cast_till_hit(&ray, map->maps[0].map); // Replace 0 with current map.
	return (generate_line(&ray, map->maps[0].map, x, side));
}

void	drawVert(t_vertline line, mlx_image_t *image, mlx_texture_t *tex) {
	int	iter;

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
		line.tex_y = (int)line.tex_begin_pos & (64 - 1);
		line.tex_begin_pos += line.tex_ystep;
		mlx_put_pixel(image, line.xcoord, iter, get_texture_pixel_data(line.wall_xcoord, line.tex_y, tex));
		iter++;
	}
}

void render_frame(t_raycam raycam, mlx_image_t *image, t_map *map, mlx_texture_t *tex) {
	for (int x = 0; x <= WIN_WIDTH; x++)
		drawVert(castRay(raycam, map, x), image, tex);
}

void handleInput(t_raycam *raycam, char **map) {
	float moveSpeed = 5.0 * 1;
	float rotSpeed = 3.0 * 1;

	if (IsKeyDown(KEY_UP)) {
		if (map.getCoord((int)(raycam->campos.x + raycam->dv.x * moveSpeed), int(raycam->campos.y)) != '#')
			raycam->campos.x += raycam->dv.x * moveSpeed;
		if (map.getCoord(int(raycam->campos.x), (int)(raycam->campos.y + raycam->dv.y * moveSpeed)) != '#')
			raycam->campos.y += raycam->dv.y * moveSpeed;
	}
	if (IsKeyDown(KEY_DOWN)) {
		if (map.getCoord((int)(raycam->campos.x - raycam->dv.x * moveSpeed), int(raycam->campos.y)) != '#')
			raycam->campos.x -= raycam->dv.x * moveSpeed;
		if (map.getCoord(int(raycam->campos.x), (int)(raycam->campos.y - raycam->dv.y * moveSpeed)) != '#')
			raycam->campos.y -= raycam->dv.y * moveSpeed;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		double oldDirX = raycam->dv.x;
		raycam->dv.x = raycam->dv.x * cos(-rotSpeed) - raycam->dv.y * sin(-rotSpeed);
		raycam->dv.y = oldDirX * sin(-rotSpeed) + raycam->dv.y * cos(-rotSpeed);
		double oldPlaneX = raycam->pv.x;
		raycam->pv.x = raycam->pv.x * cos(-rotSpeed) - raycam->pv.y * sin(-rotSpeed);
		raycam->pv.y = oldPlaneX * sin(-rotSpeed) + raycam->pv.y * cos(-rotSpeed);
	}
	if (IsKeyDown(KEY_LEFT)) {
		double oldDirX = raycam->dv.x;
		raycam->dv.x = raycam->dv.x * cos(rotSpeed) - raycam->dv.y * sin(rotSpeed);
		raycam->dv.y = oldDirX * sin(rotSpeed) + raycam->dv.y * cos(rotSpeed);
		double oldPlaneX = raycam->pv.x;
		raycam->pv.x = raycam->pv.x * cos(rotSpeed) - raycam->pv.y * sin(rotSpeed);
		raycam->pv.y = oldPlaneX * sin(rotSpeed) + raycam->pv.y * cos(rotSpeed);
	}
}
