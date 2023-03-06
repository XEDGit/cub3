#include "../../includes/rendering.h"
#include <stdlib.h>

#define WIN_HEIGHT 1152
#define WIN_WIDTH 1152

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
		if (ray->sidedistances.x < ray->sidedistances.y) {
			ray->sidedistances.x += ray->deltadistances.x;
			ray->int_map_coords.x += ray->stepdirection.x;
			side = 0;
		} else {
			ray->sidedistances.y += ray->deltadistances.y;
			ray->int_map_coords.y += ray->stepdirection.y;
			side = 1;
		}
		if (map[ray->int_map_coords.y][ray->int_map_coords.x] == 1) {
			hit = 1;
		}
	}
	return (side);
}

static t_vertline generate_line(t_rayvars *ray, char **map, int x, int side) {
	t_vertline	result;
	double		perpWallDist;

	if (side == 0)
		perpWallDist = (ray->sidedistances.x - ray->deltadistances.x);
	else
		perpWallDist = (ray->sidedistances.y - ray->deltadistances.y);
	int lineHeight = (int)((WIN_HEIGHT / perpWallDist));
	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	result.xcoord = x;
	result.startpoint = drawStart;
	result.endpoint = drawEnd;
	return (result);
}

t_vertline castRay(t_raycam *raycam, char **map, int x) {
	t_rayvars	ray;
	int			side;

	ray.camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray.raydir.x = raycam->dv.x + raycam->pv.x * ray.camera_x;
	ray.raydir.y = raycam->dv.y + raycam->pv.y * ray.camera_x;
	ray.int_map_coords = (t_intvec2){ (int)raycam->campos.x, (int)raycam->campos.y };
	ray.deltadistances = (t_vec2){ abs((int)(1 / ray.raydir.x)), abs((int)(1 / ray.raydir.y)) };
	setup_step_direction(&ray, raycam);
	side = cast_till_hit(&ray, map);
	return (generate_line(&ray, map, x, side));
}

void	drawVert(t_vertline *line, mlx_image_t *mlx) {
	int	iter;

	iter = line->startpoint;
	while (iter != line->endpoint)
	{

	}
}

void render_frame(void) {
	for (int x = 0; x <= WIN_WIDTH; x++)
		;
		/* drawVert(castRay(rayCam, x)); */
	/* return (imageBuffer); */
}
