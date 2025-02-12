/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:14:25 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:57:19 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf	*init_fdf(void)
{
	t_fdf	*fdf;
	int		sizex;
	int		sizey;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (NULL);
	define_fdf(fdf);
	fdf->mlx = mlx_init();
	mlx_get_screen_size(fdf->mlx, &sizex, &sizey);
	fdf->screen.x = sizex;
	fdf->screen.y = sizey;
	fdf->window = mlx_new_window(fdf->mlx, width(), height(), "FdF");
	fdf->img.img = mlx_new_image(fdf->mlx, width(), height());
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bpp,
			&fdf->img.ll, &fdf->img.endian);
	fdf->keys = 0;
	return (fdf);
}

static void	init_data(t_fdf *fdf, t_map *map)
{
	fdf->map = map;
	fdf->pivot_point.x = fdf->map->size.x / 2.0f;
	fdf->pivot_point.y = fdf->map->size.y / 2.0f;
	fdf->pivot_point.z = fdf->map->size.z / 2.0f;
	init_backgrounds(fdf);
	init_isometric(fdf);
	init_conic(fdf);
	init_parallel(fdf);
	fdf->type = ISOMETRIC;
	fdf->position_adr = isometric_data;
	fdf->must_update = 0;
	fdf->edit_key = NULL;
	init_navbar(fdf);
	init_depth(fdf);
}

void	init_mlx(t_fdf *fdf, t_map *map)
{
	init_data(fdf, map);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img.img, 0, 0);
	update_navbar_texts(fdf);
	mlx_hook(fdf->window, 2, 1L << 0, on_press, fdf);
	mlx_hook(fdf->window, 3, 1L << 1, on_release, fdf);
	mlx_hook(fdf->window, 17, 0, on_close, fdf);
	mlx_hook(fdf->window, 12, 1L << 15, on_expose, fdf);
	mlx_loop_hook(fdf->mlx, on_update, fdf);
	mlx_loop(fdf->mlx);
}
