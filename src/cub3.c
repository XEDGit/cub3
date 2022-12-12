#include <cub3.h>

bool	error(char *msg, bool perr)
{
	printf("Error\n");
	if (perr && msg)
		perror(msg);
	else if (msg)
		printf("%s\n", msg);
	return (true);
}

int main(int argc, char **argv)
{
	t_map	map;

	if (parse_map(&map, argc, argv))
		return (1);
	return (0);
}
