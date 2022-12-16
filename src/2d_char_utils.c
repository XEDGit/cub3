#include <shared.h>

void	free_2d(char **array)
{
	char	**copy;

	copy = array;
	while (*copy)
		free(*copy++);
	free(array);
}

int	len_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	**copy_2d(char **old)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	new = malloc((len_2d(old) + 1) * sizeof(char *));
	if (!new)
		return (0);
	while (old[i])
	{
		new[i] = malloc(ft_strlen(old[i]) + 1);
		if (!new[i])
		{
			free_2d(new);
			return (0);
		}
		j = -1;
		while (old[i][++j])
			new[i][j] = old[i][j];
		new[i++][j] = 0;
	}
	new[i] = 0;
	return (new);
}