/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:05:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 14:26:20 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include "mlx.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_point
{
	t_vector3	pos;
}	t_point;

typedef struct s_line
{
	t_point	*point1;
	t_point	*point2;
	struct s_line	*previous;
	struct s_line	*next;
}	t_line;

typedef struct s_camera
{
	t_vector3	pos;
	float	yaw;
	float	pitch;
}	t_camera;

typedef struct s_map
{
	t_vector2	size;
	t_line	*line;
	t_camera	*camera;
}	t_map;

//lines_utils.c
t_vector2	get_size(char ***lines);

//lines.c
t_line		*build_line(char ***lines, t_vector2 p1, t_vector2 p2);
void		free_lines(char ****lines, int y);
int			add_line(char *line, char ****lines, int y);
int			init_lines(char *path, char ****lines, int *fd);

//map.c
void		free_map(t_map *map);
void		add_to_map(t_map *map, t_line *line);
t_map		*parse_map(char *path);

//points.c
t_point	*init_point(char ***lines, t_vector2 p);
int	init_points(t_map *map, char ***lines);

//utils.c
float	chars_to_float(char *nbr);

//vector.c
t_vector2	vector2(float x, float y);

#endif
