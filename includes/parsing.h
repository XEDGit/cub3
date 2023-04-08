/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmuzio <lmuzio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:27:23 by lmuzio            #+#    #+#             */
/*   Updated: 2023/04/08 23:08:08 by lmuzio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//	external
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

//	internal
# include <shared.h>

char			*get_next_line(int fd);
int				free_fd_gnl(int fd);
char			*skip_spaces(char *in);
bool			find_player(t_single_map *map_list);
bool			parse_textures(t_map *map, char *line);
bool			parse_rgb(t_map *map, char *line);
bool			map_add_to_back(t_single_map **node, char **map);
t_single_map	*map_last(t_single_map *map);
char			**square_map(char **map);
int				parse_one_map(t_map *maps, int fd, int num);
bool			parse_maps(t_map *map, int fd);
bool			is_space(char *ch);

#endif
