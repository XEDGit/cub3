/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   A C file... Shocker!                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: wmaguire <wmaguire@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 1970/01/01 00:00:00 by wmaguire      #+#    #+#                 */
/*   Updated: 1970/01/01 00:00:00 by wmaguire      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rendering.h"

unsigned int	fog(double dist, unsigned int colour)
{
	unsigned int	bytes[3];

	bytes[0] = ((colour >> 24) & 0xFF) / (1 * dist / 2);
	bytes[1] = ((colour >> 16) & 0xFF) / (1 * dist / 2) + (dist);
	bytes[2] = ((colour >> 8) & 0xFF) / (1 * dist / 2);
	if (bytes[0] > ((colour >> 24) & 0xFF))
		bytes[0] = ((colour >> 24) & 0xFF);
	if (bytes[1] > ((colour >> 16) & 0xFF))
		bytes[1] = ((colour >> 16) & 0xFF);
	if (bytes[2] > ((colour >> 8) & 0xFF))
		bytes[2] = ((colour >> 8) & 0xFF);
	return ((bytes[0] << 24 | bytes[1] << 16 | bytes[2] << 8 | 0xFF));
}
