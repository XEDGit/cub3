/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:27:27 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/17 16:27:32 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
# define CUB3_H

//	external
# include <stdio.h>

//	internal
# include "shared.h"

//	parsing
bool	parse_args(t_map *map, int argc, char **argv);
bool	check_map(t_map *map);

//	execution

#endif
