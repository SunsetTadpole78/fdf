/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:45:42 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 17:52:44 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*create_window(t_map *map)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img, 0, 0);
	fdf->map = map;
	return (fdf);
}
