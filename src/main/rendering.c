#include "../../includes/rendering.h"

static void	setupStepDirection(t_rayvars *ray, t_raycam *rayCam) {
	if (ray->raydir.x < 0) {
		ray->stepdirection.x = -1;
		ray->sideDistances.x = (rayCam->campos.x - ray->int_map_coords.x) * ray->deltaDistances.x;
	} else {
		ray->stepdirection.x = 1;
		ray->sideDistances.x = (ray->int_map_coords.x + 1->0 - rayCam->campos.x) * ray->deltaDistances.x;
	}
	if (ray->raydir->y < 0) {
		ray->stepdirection->y = -1;
		ray->sideDistances->y = (rayCam->campos->y - ray->int_map_coords->y) * ray->deltaDistances->y;
	} else {
		ray->stepdirection->y = 1;
		ray->sideDistances->y = (ray->int_map_coords->y + 1->0 - rayCam->campos->y) * ray->deltaDistances->y;
	}
}

static int castUntilHit(t_rayvars *ray, char **map) {
	int	hit = 0;
	int	side;

	while (hit == 0) {
		if (ray.sideDistances.x < ray.sideDistances.y) {
			ray.sideDistances.x += ray.deltaDistances.x;
			ray.ImapCoords.x += ray.stepDirection.x;
			side = 0;
		} else {
			ray.sideDistances.y += ray.deltaDistances.y;
			ray.ImapCoords.y += ray.stepDirection.y;
			side = 1;
		}
		if (map.getCoord(ray.ImapCoords.x, ray.ImapCoords.y) == '#') {
			hit = 1;
		}
	}
	return (side);
}

static VertLine genLine(RayVariables& ray, Map& map, int x, int side) {
	VertLine	result;
	double		perpWallDist;
	Color			color;

	if (side == 0)
		perpWallDist = (ray.sideDistances.x - ray.deltaDistances.x);
	else
		perpWallDist = (ray.sideDistances.y - ray.deltaDistances.y);
	int lineHeight = (int)((WIN_HEIGHT / perpWallDist));
	int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	color = getWallColor(map.getCoord(ray.ImapCoords.x, ray.ImapCoords.y));
	if (side == 1) {
		color.r -= 50, color.b -= 10, color.g -= 10;
	};
	result.xCoord = x;
	result.startPoint = drawStart;
	result.endPoint = drawEnd;
	result.color = color;
	return (result);
}

VertLine RayCaster::castRay(RayCamera &rayCam, int x) {
	RayVariables	ray;
	int						side;

	ray.cameraX = 2 * x / double(WIN_WIDTH) - 1;
	ray.rayDir.x = rayCam.dV.x + rayCam.pV.x * ray.cameraX;
	ray.rayDir.y = rayCam.dV.y + rayCam.pV.y * ray.cameraX;
	ray.ImapCoords = { int(rayCam.camPos.x), int(rayCam.camPos.y) };
	ray.deltaDistances = { abs(1 / ray.rayDir.x), abs(1 / ray.rayDir.y) };
	setupStepDirection(ray, rayCam);
	side = castUntilHit(ray, map);
	return (genLine(ray, map, x, side));
}

void	RayCaster::drawVert(VertLine line) {
	ImageDrawLine(&imageBuffer, line.xCoord, line.startPoint, line.xCoord, line.endPoint, line.color);
}

Image& RayCaster::renderFrame() {
	ImageClearBackground(&imageBuffer, BLACK);
	for (int x = 0; x <= WIN_WIDTH; x++)
		drawVert(castRay(rayCam, x));
	return (imageBuffer);
}
