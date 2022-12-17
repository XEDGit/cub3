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

typedef struct s_single_map
{
	char				**map;
	vec_t				spawn;
	struct s_single_map	*next;
}	t_single_map;

typedef struct s_map
{
	char			*textures[4];
	long			floor;
	long			ceiling;
	t_single_map	*maps;
	t_player		player;
}	t_map;

typedef	struct s_data
{
	t_map		map;
	t_player	player;
}	t_data;

# define NO 0
# define SO 1
# define WE 2
# define EA 3

# include <stdbool.h>
# include <stdlib.h>

bool	error(char *msg, void *msg_arg, bool perr);

char	*ft_strdup(const char *s1);
int		ft_strlen(char *ptr);
long	ft_atoi(const char *str);
void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int size);
char	*ft_strchr(char *s, int c);
char	**copy_2d(char **old);
void	free_2d(char **array);
int		len_2d(char **array);

#endif