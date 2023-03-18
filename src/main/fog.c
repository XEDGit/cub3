#include "../../includes/rendering.h"
#include <stdio.h>

int	fog(double dist, int colour)
{
	int	r;
	int	g;
	int	b;

	if (dist < 2)
		return (colour);
	r = ((colour >> 24) & 0xFF) / (1 * (dist + 1) / 2);
	g = ((colour >> 16) & 0xFF) / (1 * dist / 2) + 20;
	b = ((colour >> 8) & 0xFF) / (1 * dist / 2);
	colour = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (colour);
}
