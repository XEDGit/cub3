/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   CODAM C FILE                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire     ########   codam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

typedef struct s_vec2 {
	float	x;
	float	y;
}	t_vec2;

typedef struct s_IntVector2 {
	int	x;
	int	y;
}	t_intvec2;

typedef struct s_vertline {
	int		xcoord;
	int		startpoint;
	int		endpoint;
}	t_vertline;

/* cameraX:			Camera angle. */
/* rayDir:			Direction of the ray. */
/* IMapCoords:		Integer coordinates of ray. */
/* sideDistances:	x & y distance to nearest side. */
/* deltaDistances:	Length from one x or y side to following x or y side. */
/* stepDirection:	The direction to "step" in as the algorithm continues. */
typedef struct s_RayVariables {
	float		camera_x;
	t_vec2		raydir;
	t_intvec2	int_map_coords;
	t_vec2		sidedistances;
	t_vec2		deltadistances;
	t_intvec2	stepdirection;
}	t_rayvars;

// campos:	Camera position.
// dv:		Direction vector.
// pv:		Plane vector.
typedef struct s_raycam {
	t_vec2	campos;
	t_vec2	dv;
	t_vec2	pv;
}	t_raycam;

#endif // RENDERING_H