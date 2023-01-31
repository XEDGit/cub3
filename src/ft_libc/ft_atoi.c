/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:57:17 by lmuzio            #+#    #+#             */
/*   Updated: 2023/01/31 17:30:19 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atoi(const char *str)
{
	long		res;
	int			min;

	res = 0;
	min = 0;
	if (!*str)
		return (res);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-')
		min = 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str++ - '0';
	}
	if (min)
		res *= -min;
	return (res);
}
