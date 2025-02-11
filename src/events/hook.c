/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 09:17:17 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 16:43:10 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	button_click(t_fdf *fdf, t_button *button)
{
	if (button->id == BGG && button->color == black)
		change_background(fdf, NULL);
	else if (button->id == BGG)
		change_background(fdf, button->color);
	if (button->id == LINE)
		update_colors(fdf, button->color);
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
	else if (button->id == I_AXIS)
		fdf->isometric.axis = button->selected;
	else if (button->id == P_AXIS)
		fdf->parallel.axis = button->selected;
	else if (button->id == MIRROR)
		fdf->isometric.mirror = button->selected;
	else if (button->type == KEYBOX && button->selected)
		fdf->edit_key = get_key_from(get_controls(fdf), button->id);
	else if (button->type == KEYBOX)
		fdf->edit_key = NULL;
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

void	unselect_others(t_button *button)
{
	int			i;
	t_button	**buttons;

	if (!button->category)
		return ;
	i = 0;
	buttons = button->category->buttons;
	while (buttons[i])
	{
		if (buttons[i]->uniq_id != button->uniq_id) 
			buttons[i]->selected = 0;
		i++;
	}
}

void	check_click(t_fdf *fdf, t_button **buttons, t_vector2 pos)
{
	int	i;

	i = 0;
	while (buttons[i])
	{
		if (is_button(pos, buttons[i]))
		{
			if (buttons[i]->type == TOGGLE)
				buttons[i]->selected ^= 1;
			else if (buttons[i]->type == KEYBOX)
			{
				unselect_others(buttons[i]);
				buttons[i]->selected ^= 1;
			}
			else
			{
				unselect_others(buttons[i]);
				buttons[i]->selected = 1;
			}
			get_navbar()->must_update = 1;
			button_click(fdf, buttons[i]);
		}
		i++;
	}
}

