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

#endif