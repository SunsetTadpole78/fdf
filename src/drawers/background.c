/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:06:26 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 15:06:27 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_background(t_fdf *fdf, int (color)(t_vector2, int, int, int))
{
	t_background	*bg;
	char			*pixel;
	t_vector2		pos;

	bg = fdf->background;
	bg->bg_color = color;
	if (!color)
		return ;
	if (!bg->bg.img)
		bg->bg.img = mlx_new_image(fdf->mlx, width(), height());
	bg->bg.addr = mlx_get_data_addr(bg->bg.img, &bg->bg.bpp,
			&bg->bg.ll, &bg->bg.endian);
	pos.y = 0;
	while (pos.y <= height())
	{
		pos.x = 0;
		while (pos.x <= width())
		{
			pixel = fdf->background->bg.addr
				+ ((int)pos.y * fdf->img.ll + (int)pos.x * (fdf->img.bpp / 8));
			*(unsigned int *)pixel = color(pos, width(), height(), 0);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_background(t_fdf *fdf)
{
	if (!fdf->background->bg_color)
		return ;
	ft_memcpy(
		fdf->img.addr,
		fdf->background->bg.addr,
		height() * fdf->img.ll + width() * (fdf->img.bpp / 8));
}
