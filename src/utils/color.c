/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:42:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:25:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(char *el)
{
	char	**splited;
	char	*color;
	int		i;
	int		v;

	splited = ft_split(el, ',');
	if (!splited || !splited[1])
		return (0xFFFFFF);
	color = ft_strdup(splited[1]);
	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
	if (!color[0] || color[0] != '0' || !color[1]
		|| color[1] != 'x' || !ft_ishexa(color + 2))
		return (0xFFFFFF);
	v = ft_atoh(color);
	free(color);
	return (v);
}

void	update_colors(t_fdf *fdf,
			int (color)(t_vector3, t_vector2, t_vector3))
{
	size_t		y;
	size_t		x;
	t_point		**points;
	t_vector2	mimay;

	y = 0;
	points = fdf->map->points;
	mimay.x = fdf->map->min_y;
	mimay.y = fdf->map->max_y;
	while (points[y])
	{
		x = 0;
		while (x < fdf->map->size.x)
		{
			if (!points[y][x].hardcoded_color)
				points[y][x].color = color(points[y][x].pos,
						mimay, fdf->map->size);
			x++;
		}
		y++;
	}
}
