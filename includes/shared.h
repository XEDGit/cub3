#ifndef MAP_H
# define MAP_H

typedef int	vec_t[3];

typedef struct s_map
{
	char	*textures[4];
	char	**map;
	vec_t	player;
	vec_t	floor;
	vec_t	ceiling;
}	t_map;

# include <stdbool.h>

bool	error(char *msg, bool perr);

#endif