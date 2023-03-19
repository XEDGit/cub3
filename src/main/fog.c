#include "../../includes/rendering.h"
#include <stdio.h>

int	fog(double dist, int colour)
{
	int	r;
	int	g;
	int	b;

	r = ((colour >> 24) & 0xFF) / (1 * (dist + 1) / 2);
	g = ((colour >> 16) & 0xFF) / (1 * dist / 2) + 20;
	b = ((colour >> 8) & 0xFF) / (1 * dist / 2);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		r = 255;
	if (r > ((colour >> 24) & 0xFF))
		r = ((colour >> 24) & 0xFF);
	if (g > ((colour >> 16) & 0xFF))
		g = ((colour >> 16) & 0xFF);
	if (r > ((colour >> 8) & 0xFF))
		b = ((colour >> 8) & 0xFF);
	colour = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (colour);
}
