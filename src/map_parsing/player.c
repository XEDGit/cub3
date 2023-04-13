/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:54 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/12 18:49:02 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

bool	find_player(t_single_map *map_list)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	found = 0;
	while (map_list->map[i])
	{
		j = 0;
		while (map_list->map[i][j])
		{
			if (map_list->map[i][j] == 'N' || map_list->map[i][j] == 'E' || \
			map_list->map[i][j] == 'W' || map_list->map[i][j] == 'S')
			{
				map_list->spawn[X] = j;
				map_list->spawn[Y] = i;
				found++;
			}
			j++;
		}
		i++;
	}
	if (found == 1)
		return (false);
	return (true);
}
