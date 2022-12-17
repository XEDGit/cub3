/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:22 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/17 15:10:16 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int size)
{
	void			*new;
	unsigned int	i;

	new = malloc(size);
	if (!new)
		return (0);
	if (!ptr)
		return (new);
	i = 0;
	while (i < old_size)
	{
		((char *)new)[i] = ((char *)ptr)[i];
		i++;
	}
	while (i < size)
		((char *)new)[i++] = 0;
	free(ptr);
	return (new);
}
