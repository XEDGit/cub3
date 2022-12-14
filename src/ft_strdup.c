/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sk_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lmuzio <lmuzio@student.42.fr>                +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 22:51:44 by lmuzio        #+#    #+#                 */
/*   Updated: 2022/05/10 22:53:39 by lmuzio        ########   odam.nl         */
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
