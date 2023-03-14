#include "../../includes/rendering.h"
#include <stdio.h>
#include <string.h>

int	texdata_to_int(uint8_t *texdata)
{
	int	colour;

	colour = 0;
	colour = \
		(texdata[0] << 24 | texdata[1] << 16 | texdata[2] << 8 | texdata[3]);
	return (colour);
}

int	get_texture_pixel_data(int x, int y, mlx_texture_t *tex)
{
	uint8_t	*pixptr;

	pixptr = &tex->pixels[(x + tex->width * y) * tex->bytes_per_pixel];
	return (texdata_to_int(pixptr));
}

void	input_keyhook(mlx_key_data_t keydata, void *data)
{
	t_renderer	*mapcam;

	mapcam = data;
	if (!mapcam)
		return ;
	mapcam->has_moved = 1;
	handle_input(keydata, \
			mapcam->raycam, mapcam->map->maps->map);
}

void	render_hook(void *data)
{
	t_renderer	*renderer;

	renderer = data;
	if (renderer->has_moved)
	{
		clear(renderer->image);
		render_frame(renderer->raycam, \
							renderer->image, renderer->map, renderer->tex);
		renderer->has_moved = 0;
	}
}

void	clear(mlx_image_t *img)
{
	memset(img->pixels, \
			0, img->height * img->width * 4); // TODO: Replace with ft_memset.
}
