#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
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
