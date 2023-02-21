/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:27:34 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/17 16:28:59 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKING_H
# define CHECKING_H

//	internal
# include "shared.h"

typedef struct s_cell
{
	int				cellx;
	int				celly;
	struct s_cell	*next;
}	t_cell;

typedef struct s_cell_list
{
	t_cell			*to_check;
	t_cell			*neighbors;
	t_cell			*check_copy;
	t_single_map	*map_list_copy;
	char			**map_copy;
}	t_cell_list;

//	external

#endif
