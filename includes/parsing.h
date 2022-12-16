#ifndef PARSING_H
# define PARSING_H

//	external
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

//	internal
# include <shared.h>

char	*get_next_line(int fd);
int		free_fd_gnl(int fd);
char	*skip_spaces(char *in);
bool	find_player(t_single_map *map_list);

#endif