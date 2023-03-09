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
# include "../MLX42/include/MLX42/MLX42.h"
# include "shared.h"

# define WIN_HEIGHT 640
# define WIN_WIDTH 640

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
	int		wall_xcoord;
	double	tex_ystep;
	double	tex_begin_pos;
	int		tex_y;
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

int			get_texture_pixel_data(int x, int y, mlx_texture_t *tex);
void		render_frame(t_raycam raycam, mlx_image_t *image, t_map *map, mlx_texture_t *tex);
t_raycam	*init_raycam(int x, int y);

#endif // RENDERING_H
