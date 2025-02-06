/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:42:03 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 16:25:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map_data(char ***lines, t_map *map)
{
	float		v;

	map->size.z = 0;
	map->min_y = MAX_INT;
	map->max_y = MIN_INT;
	while (lines[(int)map->size.z])
	{
		map->size.x = 0;
		while (lines[(int)map->size.z][(int)map->size.x])
		{
			v = (float)ft_atoi(lines[(int)map->size.z][(int)map->size.x]) / 10;
			if (v < map->min_y)
				map->min_y = v;
			else if (v > map->max_y)
				map->max_y = v;
			map->size.x++;
		}
		map->size.z++;
	}
	map->size.y = ft_abs(map->max_y - map->min_y);
}
