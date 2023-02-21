#ifndef RENDERING_H
#define RENDERING_H

typedef struct s_vec2 {
	float x;
	float y;
} t_vec2;

typedef struct s_IntVector2 {
	int	x;
	int	y;
} t_intvec2;

typedef struct s_vertline {
	int		xCoord;
	int		startPoint;
	int		endPoint;
}	t_vertline;

// cameraX:			Camera angle.
// rayDir:			Direction of the ray.
// IMapCoords:		Integer coordinates of ray.
// sideDistances:	x & y distance to nearest side.
// deltaDistances:	Length from one x or y side to following x or y side.
// stepDirection:	The direction to "step" in as the algorithm continues.
typedef struct s_RayVariables {
	float		cameraX;
	t_vec2		rayDir;
	t_intvec2	ImapCoords;
	t_vec2		sideDistances;
	t_vec2		deltaDistances;
	t_intvec2	stepDirection;
} RayVariables;


#endif // RENDERING_H
