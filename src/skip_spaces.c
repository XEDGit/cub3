char	*skip_spaces(char *in)
{
	if (!in)
		return (0);
	while (*in)
	{
		if (*in == ' ')
			in++;
		else
			break ;
	}
	return (in);
}