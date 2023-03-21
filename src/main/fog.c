#include "../../includes/rendering.h"
#include <stdio.h>

unsigned int	fog(double dist, unsigned int colour)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ((colour >> 24) & 0xFF) / (1 * dist / 2);
	g = ((colour >> 16) & 0xFF) / (1 * dist / 2) + (dist);
	b = ((colour >> 8) & 0xFF) / (1 * dist / 2);
	if (r > ((colour >> 24) & 0xFF))
		r = ((colour >> 24) & 0xFF);
	if (g > ((colour >> 16) & 0xFF))
		g = ((colour >> 16) & 0xFF);
	if (b > ((colour >> 8) & 0xFF))
		b = ((colour >> 8) & 0xFF);
	colour = (r << 24 | g << 16 | b << 8 | 0xFF - (unsigned int)dist * 2);
	return (colour);
}
