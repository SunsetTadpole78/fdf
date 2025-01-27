/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:17:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/27 11:51:05 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	keys_hook(int keycode, t_fdf *fdf)
{
	int	resend;

	if (keycode == XK_Escape)
	{
		destruct(fdf);
		return (0);
	}
	resend = translate(keycode, fdf);
	resend |= resend || rotate(keycode, fdf);
	resend |= resend || zoom(keycode, fdf);
	if (resend)
		fdf->must_update = 1;
	return (0);
}

int	on_move(int x, int y, t_navbar *navbar)
{
	t_category	**categories;
	int			i;
	t_button	*main;
	int			hovered;

	if (!navbar)
		return (0);
	categories = navbar->categories;
	i = 0;
	while (categories[i])
	{
		main = categories[i]->main;
		hovered = main->hover;
		categories[i]->main->hover = main->type == NAVBAR && x >= main->offset.x
			&& x <= main->size.x + main->offset.x && y >= main->offset.y
			&& y <= main->size.y + main->offset.y;
		if (hovered != categories[i]->main->hover)
			navbar->must_update = 1;
		i++;
	}
	return (0);
}

void	button_click(t_fdf *fdf, t_button *button)
{
	if (button->id == BGG && button->color == black)
		fdf->display_data->bg = NULL;
	else if (button->id == BGG)
		fdf->display_data->bg = button->color;
	else if (button->type == NAVBAR)
	{
		if (get_navbar()->actual)
			get_navbar()->actual->main->selected = 0;
		if (get_navbar()->actual && get_navbar()->actual == button->category)
			get_navbar()->actual = NULL;
		else
		{
			get_navbar()->actual = button->category;
			button->selected = 1;
		}
	}
}

int	is_button(t_vector2 v, t_button *button)
{
	t_vector2	offset;

	offset = button->offset;
	if (button->type == CIRCLE)
		return (ft_distance(offset, v) <= button->size.x);
	else if (button->type == NAVBAR)
		return (v.x >= offset.x && v.x <= button->size.x + offset.x
			&& v.y >= offset.y && v.y <= button->size.y + offset.y);
	return (0);
}

void	select_toolbar_button(t_button *button)
{
	int			i;
	t_category	**categories;

	i = 0;
	categories = get_navbar()->categories;
	while (categories[i])
	{
		categories[i]->main->selected = categories[i]->main->uniq_id
			== button->uniq_id;
		i++;
	}
}

void	select_button(t_button *button)
{
	int			i;
	t_button	**buttons;

	if (!button->category)
		return ;
	i = 0;
	buttons = button->category->buttons;
	while (buttons[i])
	{
		buttons[i]->selected = buttons[i]->uniq_id == button->uniq_id;
		i++;
	}
}

int	on_click(int id, int x, int y, t_fdf *fdf)
{
	int			i;
	t_vector2	pos;

	if (id == 1)
	{
		i = 0;
		pos.x = x;
		pos.y = y;
		if (active_navbar(2))
		{
			while (get_navbar()->categories[i])
			{
				if (is_button(pos, get_navbar()->categories[i]->main))
				{
					fdf->must_update = 1;
					button_click(fdf, get_navbar()->categories[i]->main);
				}
				i++;
			}
			if (get_navbar()->actual)
			{
				i = 0;
				while (get_navbar()->actual->buttons[i])
				{
					if (is_button(pos, get_navbar()->actual->buttons[i]))
					{
						select_button(get_navbar()->actual->buttons[i]);
						fdf->must_update = 1;
						button_click(fdf, get_navbar()->actual->buttons[i]);
					}
					i++;
				}
			}
			if (y > 150 && get_navbar()->actual)
			{
				get_navbar()->actual->main->selected = 0;
				get_navbar()->actual = NULL;
				fdf->must_update = 1;
			}
		}
	}
	return (0);
}
