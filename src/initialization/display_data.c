/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:32:56 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/30 10:37:56 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_display_data(t_fdf *fdf)
{
	t_display_data	*display_data;
	t_vector3		s;
	float			zoom_width;
	float			zoom_height;

	display_data = malloc(sizeof(t_display_data));
	if (!display_data)
		return ;
	s = fdf->map->size;
	display_data->pivot_point.x = s.x / 2;
	display_data->pivot_point.y = s.y / 2;
	display_data->pivot_point.z = s.z / 2;
	display_data->offset.x = 0;
	display_data->offset.y = 0;
	display_data->rotate.x = 0;
	display_data->rotate.y = 0;
	display_data->rotate.z = 0;
	display_data->zoom = 1;
	zoom_width = (float)WIDTH / (s.x + s.z);
	zoom_height = (float)HEIGHT / (s.y + (s.x + s.z) * sin(30 * (M_PI / 180)));
	display_data->zoom_v = zoom_height;
	if (zoom_width < zoom_height)
		display_data->zoom_v = zoom_width;
	display_data->bg_color = NULL;
	display_data->axis = 1;
	display_data->mirror = 0;
	display_data->bg.img = NULL;
	fdf->display_data = display_data;
	init_backgrounds(fdf);
}
