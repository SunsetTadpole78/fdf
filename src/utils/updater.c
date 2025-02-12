/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updater.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:15:10 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:29:08 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_fdf	*f(t_fdf *v)
{
	static t_fdf	*fdf = NULL;

	if (v)
		fdf = v;
	return (fdf);
}

void	define_fdf(t_fdf *fdf)
{
	f(fdf);
}

t_fdf	*get_fdf(void)
{
	return (f(NULL));
}

void	update_keys(t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
		isometric_key_event(fdf);
	else if (fdf->type == CONIC)
		conic_key_event(fdf);
	else
		parallel_key_event(fdf);
	fdf->must_update = 1;
}

int	on_update(t_fdf *fdf)
{
	if (fdf->keys != 0)
		update_keys(fdf);
	if (fdf->must_update || (active_navbar(2) && get_navbar()->must_update))
	{
		ft_memset(fdf->img.addr, 0, height() * width() * (fdf->img.bpp / 8));
		clear_depth(fdf);
		draw_background(fdf);
		draw_map(fdf);
		draw_axes(fdf);
		draw_navbar(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->img.img, 0, 0);
		update_navbar_texts(fdf);
		get_navbar()->must_update = 0;
		fdf->must_update = 0;
	}
	return (0);
}
