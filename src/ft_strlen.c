/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:29 by lmuzio            #+#    #+#             */
/*   Updated: 2022/12/17 15:10:30 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *ptr)
{
	char	*copy;

	copy = ptr;
	while (*copy)
		copy++;
	return ((int)(copy - ptr));
}
