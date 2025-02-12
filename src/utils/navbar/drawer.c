/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:40:41 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 17:40:43 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_top(t_fdf *fdf)
{
	t_vector2	pos;

	pos.y = 0;
	while (pos.y < 51)
	{
		pos.x = 0;
		while (pos.x < width())
		{
			if (pos.y == 50)
				put_pixel(fdf, pos, 0x2F2F33, 0.9);
			else
				put_pixel(fdf, pos, 0x1C1C1E, 0.9);
			pos.x++;
		}
		pos.y++;
	}
}

static void	draw_open_category(t_fdf *fdf)
{
	t_vector2	pos;

	pos.y = 51;
	while (pos.y < 151)
	{
		pos.x = 0;
		while (pos.x < width())
		{
			if (pos.y == 150)
				put_pixel(fdf, pos, 0x2F2F33, 0.9);
			else
				put_pixel(fdf, pos, 0x1C1C1E, 0.9);
			pos.x++;
		}
		pos.y++;
	}
}

static void	draw_subs(t_fdf *fdf, t_subcategory **subs)
{
	int	i;

	i = 0;
	while (subs[i])
	{
		if (is_showable(subs[i]))
			draw_buttons(fdf, subs[i]->buttons);
		i++;
	}
}

static void	draw_category(t_fdf *fdf, t_category *category)
{
	t_vector2	pos;

	draw_button(fdf, category->main);
	pos = category->main->offset;
	pos.x += category->main->size.x;
	while (pos.y < category->main->size.y)
	{
		put_pixel(fdf, pos, 0x2F2F33, 1);
		pos.y++;
	}
	if (get_navbar()->actual && category == get_navbar()->actual)
	{
		draw_open_category(fdf);
		draw_buttons(fdf, category->buttons);
		draw_subs(fdf, category->subs);
	}
}

void	draw_navbar(t_fdf *fdf)
{
	int	i;

	if (!active_navbar(2))
		return ;
	draw_top(fdf);
	if (!get_navbar()->categories)
		return ;
	i = 0;
	while (get_navbar()->categories[i])
	{
		draw_category(fdf, get_navbar()->categories[i]);
		i++;
	}
}
