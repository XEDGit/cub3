/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:54 by lmuzio            #+#    #+#             */
/*   Updated: 2023/03/18 22:51:55 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

bool	find_player(t_single_map *map_list)
{
	int	i;
	int	j;

	i = 0;
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
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
