/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:32:56 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/17 18:45:40 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_display_data(t_fdf *fdf)
{
	t_display_data	*display_data;

	display_data = malloc(sizeof(t_display_data));
	if (!display_data)
		return ;
	display_data->a.x = fdf->map->size.x / 2;
	display_data->a.y = 0;
	display_data->a.z = fdf->map->size.y / 2;
	display_data->pivot_point.x = 0;
	display_data->pivot_point.y = 0;
	display_data->pivot_point.z = 0;
	display_data->rotate.x = 30;
	display_data->rotate.y = 30;
	display_data->rotate.z = 30;
	display_data->zoom = 60;
	fdf->display_data = display_data;
}
