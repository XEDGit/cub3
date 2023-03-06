#include "../../includes/rendering.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>

int	texdata_to_int(uint8_t *texdata)
{
	int colour = 0;
	colour = (texdata[0] << 24 | texdata[1] << 16 | texdata[2] << 8 | texdata[3]);
	return (colour);
}

int	get_texture_pixel_data(int x, int y, mlx_texture_t *tex)
{
	uint8_t	*pixptr = &tex->pixels[(x + tex->width * y) * tex->bytes_per_pixel];

	printf("R: %02X G: %02X B: %02X A: %02X", pixptr[0], pixptr[1], pixptr[2], pixptr[3]);

	return ((uint32_t)*pixptr);
}
