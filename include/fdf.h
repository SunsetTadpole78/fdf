/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:05:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 11:39:14 by lroussel         ###   ########.fr       */
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
	t_vector3	*pos;
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
	t_vector3	*pos;
	float	yaw;
	float	pitch;
}	t_camera;

typedef struct s_map
{
	t_vector2	*size;
	t_line	*line;
	t_camera	*camera;
}	t_map;

#endif
