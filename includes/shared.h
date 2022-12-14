#ifndef MAP_H
# define MAP_H

typedef int	vec_t[3];

typedef struct s_player
{
	vec_t	position;
	int		health;
	int		rotH;
	int		rotV;
}	t_player;

# define X 0
# define Y 1
# define Z 2

typedef struct s_map
{
	char		*textures[4];
	long		floor;
	long		ceiling;
	char		**map;
	t_player	player;
}	t_map;

# define NO 0
# define SO 1
# define WE 2
# define EA 3

# include <stdbool.h>
# include <stdlib.h>

bool	error(char *msg, bool perr);

char	*ft_strdup(const char *s1);
int		ft_strlen(char *ptr);
long	ft_atoi(const char *str);
char	*ft_strchr(char *s, int c);

#endif