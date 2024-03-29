/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:54:44 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/13 00:30:50 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

int	init_filedesc(t_filedesc *fds, int fd)
{
	fds->fd = fd;
	fds->fbuff = 0;
	gnl_strlcpy(&fds->fbuff, "", 1);
	fds->rb = 1;
	fds->res = 1;
	return (1);
}

char	*free_all(t_filedesc *fds)
{
	if (fds->fbuff)
	{
		free(fds->fbuff);
		fds->fbuff = 0;
	}
	if (fds->buff)
		free(fds->buff);
	return (0);
}

char	*ret(t_filedesc *fds)
{
	if (fds->fbuff)
	{
		if (!fds->fbuff[0])
		{
			free(fds->fbuff);
			fds->fbuff = 0;
		}
		return (fds->buff);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static t_filedesc	fds[MAX_DESCRIPTORS] = {0};

	if (fd < 0)
		return (0);
	if (!fds[fd].fbuff)
		init_filedesc(&fds[fd], fd);
	fds[fd].buff = malloc(BUFFER_SIZE + 1);
	if (!fds[fd].buff || !fds[fd].fbuff)
		return (free_all(&fds[fd]));
	while (fds[fd].res || fds[fd].fbuff)
	{
		fds[fd].rb = read(fd, fds[fd].buff, BUFFER_SIZE);
		if (fds[fd].rb == -1)
			return (free_all(&fds[fd]));
		fds[fd].buff[fds[fd].rb] = 0;
		fds[fd].fbuff = gnl_strjoin(fds[fd].fbuff, fds[fd].buff, fds[fd].rb);
		if (!fds[fd].fbuff)
			return (free_all(&fds[fd]));
		fds[fd].res = gnl_strchr(&fds[fd], '\n');
		if (fds[fd].res || !*fds[fd].fbuff)
			break ;
	}
	if (!fds[fd].res)
		return (free_all(&fds[fd]));
	return (ret(&fds[fd]));
}

int	free_fd_gnl(int fd)
{
	char	*buffer;

	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		free(buffer);
	}
	close(fd);
	return (1);
}
