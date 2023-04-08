/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by wmaguire          #+#    #+#             */
/*   Updated: 2023/04/08 19:10:15 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "shared.h"

/* Window width and window height */
# define W 1152
# define H 1152

typedef struct s_vec2 {
	float	x;
	float	y;
}	t_vec2;

typedef struct s_IntVector2 {
	int	x;
	int	y;
}	t_ivec;

/* Contains variables used to render a single vertical line onto the screen */
/* based on the distance from the ray to the player. */

/* dir:				North, South, East or West */
/* xcoord:			X coordinate of the vertical line on the screen. */
/* startpoint:		Y coordinate start point of the vertical line. */
/* endpoint:		Y coordinate end point of the vertical line. */
/* tex_x:			The X coordinate of the pixel to draw. */
/* tex_y:			The Y coordinate of the pixel to draw. */
/* step:			How many / few pixels to step upwards in 
the texture per pixel of the line. */
/* tex_y_begin_pos:	Which pixel in the Y axis of the texture we should begin 
from when drawing the line. */
typedef struct s_vertline {
	double	dist;
	int		dir;
	int		xcoord;
	int		startpoint;
	int		endpoint;
	int		side;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_y_begin_pos;
}	t_vertline;

/* camera_x:			Camera angle. */
/* rdir:			Direction of the ray. */
/* imapcoords:		Integer coordinates of ray. */
/* sidedistances:	x & y distance to nearest side. */
/* deltads:	Length from one x or y side to following x or y side. */
/* stepdirection:	The direction to "step" in as the algorithm continues. */
typedef struct s_RayVariables {
	float		camera_x;
	t_vec2		rdir;
	t_ivec		imapcoords;
	t_vec2		sidedistances;
	t_vec2		deltads;
	t_ivec		stepdirection;
}	t_rayvars;

/* campos:	Camera position. */
/* dv:		Direction vector. */
/* pv:		Plane vector. */
typedef struct s_raycam {
	t_vec2	campos;
	t_vec2	dv;
	t_vec2	pv;
}	t_raycam;

/* This is the dump everything struct where all clean code */
/* goes to die. I apologise in advance. */
typedef struct s_renderer {
	int				th;
	int				tw;
	unsigned int	curr_map;
	int				has_moved;
	t_raycam		rc;
	t_rayvars		rv;
	mlx_image_t		*image;
	t_map			*map;
	mlx_texture_t	*tex[4];
	mlx_t			*mlx;
}	t_renderer;

t_raycam		*init_raycam(t_raycam *raycam, int x, int y, char dir);
int				init_renderer(mlx_t *mlx, t_renderer *rn, t_data *data);
void			input_keyhook(mlx_key_data_t keydata, void *data);
void			render_hook(void *data);
void			render_frame(t_renderer *rn);
void			dealloc_renderer(t_renderer *rn);
t_vertline		cast_ray(t_renderer *rn, int x);
t_vertline		generate_line(t_renderer *rn, int x, int side);
int				handle_input(t_raycam *rc, char **m, mlx_t *mlx);
int				get_texture_pixel_data(int x, int y, mlx_texture_t *tex);
unsigned int	fog(double dist, unsigned int colour);
void			draw_vert(t_vertline line, mlx_image_t *image, mlx_texture_t **tex);

#endif // RENDERING_H
