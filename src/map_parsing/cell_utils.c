/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:54:32 by lmuzio            #+#    #+#             */
/*   Updated: 2023/03/18 22:51:22 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checking.h>

t_cell	*cell_last(t_cell *cell)
{
	while (cell->next)
		cell = cell->next;
	return (cell);
}

int	cell_add_to_back(t_cell **node, int newX, int newY)
{
	t_cell	*last;

	if (!*node)
	{
		*node = malloc(sizeof(t_cell));
		if (!node)
			return (error("Malloc fail", 0, false));
		(*node)->cellx = newX;
		(*node)->celly = newY;
		(*node)->next = 0;
		return (false);
	}
	last = cell_last(*node);
	last->next = malloc(sizeof(t_cell));
	if (!last->next)
		return (error("Malloc fail", 0, false));
	last->next->cellx = newX;
	last->next->celly = newY;
	last->next->next = 0;
	return (false);
}

void	free_cell(t_cell *node)
{
	t_cell	*next;

	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
}
