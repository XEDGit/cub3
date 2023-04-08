/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:28:25 by lmuzio            #+#    #+#             */
/*   Updated: 2023/03/28 21:15:43 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif
# define MAX_DESCRIPTORS 1024

//int fd, char *buff, int isend, int rb, char *fbuff
typedef struct s_filedesc
{
	int		fd;
	char	*buff;
	char	*fbuff;
	int		res;
	int		rb;
}	t_filedesc;

char	*gnl_strjoin(char *s1, char const *s2, size_t len);
int		gnl_strchr(t_filedesc *fds, int c);
size_t	gnl_strlcpy(char **dst, const char *src, size_t dstsize);

#endif
