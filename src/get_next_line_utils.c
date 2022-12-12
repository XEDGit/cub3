#include <get_next_line.h>

char	*ft_strjoin(char *s1, char const *s2, size_t len)
{
	char	*res;
	char	*cur;
	char	*temp;
	int		c;

	c = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[c])
		c++;
	temp = s1;
	res = malloc(c + len + 1);
	if (!res)
		return (0);
	cur = res;
	while (*s1)
		*cur++ = *s1++;
	while (len--)
		*cur++ = *s2++;
	*cur = 0;
	free(temp);
	return (res);
}

int	ft_strchr(t_filedesc *fds, int c)
{
	int		cont;
	int		fill;

	cont = 0;
	fill = 0;
	while (fds->fbuff[cont] && fds->fbuff[cont] != c)
		cont++;
	if (fds->fbuff[cont] == c)
	{
		cont++;
		ft_strlcpy(&fds->buff, fds->fbuff, cont + 1);
		if (!fds->buff)
			return (0);
		while (fds->fbuff[cont + fill])
			fill++;
		ft_strlcpy(&fds->fbuff, &fds->fbuff[cont], fill + 1);
		return (1);
	}
	else if (cont && !fds->rb)
	{
		ft_strlcpy(&fds->buff, fds->fbuff, cont + 1);
		ft_strlcpy(&fds->fbuff, "", 1);
		return (1);
	}
	return (0);
}

size_t	ft_strlcpy(char **dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	char	*tem;
	int		c;

	srcsize = 0;
	c = 0;
	if (!src)
		return (0);
	while (src[srcsize] && srcsize < dstsize)
		srcsize++;
	tem = malloc(srcsize + 1);
	if (!tem)
		return (0);
	if (!dstsize)
		return (srcsize);
	while (dstsize - 1 && *src)
	{
		tem[c++] = *src++;
		dstsize--;
	}
	tem[c] = 0;
	if (*dst)
		free(*dst);
	*dst = tem;
	return (c);
}
