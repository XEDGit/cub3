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

# define WIN_HEIGHT 2048
# define WIN_WIDTH 2048

typedef struct s_vec2 {
	float	x;
	float	y;
}	t_vec2;

typedef struct s_IntVector2 {
	int	x;
	int	y;
}	t_intvec2;

// Contains variables used to render a single vertical line onto the screen
// based on the distance from the ray to the player.
//
// xcoord:			X coordinate of the vertical line on the screen.
// startpoint:		Y coordinate start point of the vertical line.
// endpoint:		Y coordinate end point of the vertical line.
// tex_x:			The X coordinate of the pixel to draw.
// tex_y:			The Y coordinate of the pixel to draw.
// tex_y_step:		How many / few pixels to step upwards in the texture per pixel of the line.
// tex_y_begin_pos:	Which pixel in the Y axis of the texture we should begin from when drawing the line.
typedef struct s_vertline {
	int		xcoord;
	int		startpoint;
	int		endpoint;
	int		side;
	int		tex_x;
	int		tex_y;
	double	tex_y_step;
	double	tex_y_begin_pos;
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
	t_vec2		deltads;
	t_intvec2	stepdirection;
}	t_rayvars;

/* campos:	Camera position. */
/* dv:		Direction vector. */
/* pv:		Plane vector. */
typedef struct s_raycam {
	t_vec2	campos;
	t_vec2	dv;
	t_vec2	pv;
}	t_raycam;

/* Contains data required for rendering. */
typedef struct s_renderer {
	int				has_moved;
	t_raycam		*raycam;
	mlx_image_t		*image;
	t_map			*map;
	mlx_texture_t	*tex;
} t_renderer;

t_raycam	*init_raycam(int x, int y);
void		input_keyhook(mlx_key_data_t keydata, void *data);
void		render_hook(void *data);
void		render_frame(t_raycam *raycam, mlx_image_t *image, t_map *map, mlx_texture_t *tex);
t_vertline	cast_ray(t_raycam *raycam, t_map *map, int x);
void		handle_input(mlx_key_data_t key, t_raycam *raycam, char **map);
int			get_texture_pixel_data(int x, int y, mlx_texture_t *tex);

#endif // RENDERING_H
