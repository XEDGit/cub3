#include <shared.h>

void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int size)
{
	void			*new;
	unsigned int	i;

	new = malloc(size);
	if (!new)
		return (0);
	if (!ptr)
		return (new);
	i = 0;
	while (i < old_size)
	{
		((char *)new)[i] = ((char *)ptr)[i];
		i++;
	}
	while (i < size)
		((char *)new)[i++] = 0;
	free(ptr);
	return (new);
}