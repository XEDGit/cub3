int	ft_strlen(char *ptr)
{
	char	*copy;

	copy = ptr;
	while (*copy)
		copy++;
	return ((int)(copy - ptr));
}