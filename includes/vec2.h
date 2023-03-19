/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 21:18:51 by lmuzio            #+#    #+#             */
/*   Updated: 2023/03/18 21:18:54 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct s_vec2 {
	double	x;
	double	y;
}	t_vec2;

// Add together two t_vec2
t_vec2	add(t_vec2 a, t_vec2 b);
t_vec2	rot(t_vec2 a, t_vec2 b);
t_vec2	mul(t_vec2 a, t_vec2 b);

#endif // VEC2_H
