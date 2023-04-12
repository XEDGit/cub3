/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:22 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/13 01:03:43 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int size)
{
	char			*new;
	unsigned int	i;

	new = malloc(size);
	if (!new)
		return (free(ptr), (void *)0);
	if (!ptr)
		return (new);
	i = 0;
	while (i < old_size)
	{
		new[i] = ((char *)ptr)[i];
		i++;
	}
	while (i < size)
		new[i++] = 0;
	free(ptr);
	return ((void *)new);
}
