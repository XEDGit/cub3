/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 22:51:44 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/13 01:18:40 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*cur;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (0);
	cur = dup;
	while (*s1)
		*cur++ = *s1++;
	*cur = 0;
	return (dup);
}

char	*ft_reverse_str(char *s1)
{
	char	*dup;
	char	*cur;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	dup = malloc(len + 1);
	if (!dup)
		return (free(s1), (char *)0);
	cur = dup;
	while (len--)
		*cur++ = *(s1 + len);
	*cur = 0;
	free(s1);
	return (dup);
}
