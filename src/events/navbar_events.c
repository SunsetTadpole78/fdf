/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navbar_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:30:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 23:15:37 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_move_navbar(int x, int y, t_navbar *navbar)
{
	t_category	**categories;
	int			i;
	t_vector2	pos;
	t_button	*buttons[2];

	if (!navbar)
		return (0);
	categories = navbar->categories;
	i = 0;
	pos = ft_vector2(x, y);
	while (categories[i])
		check_buttons(create_array(buttons, categories[i++]->main), pos);
	if (navbar->actual)
	{
		check_buttons(navbar->actual->buttons, pos);
		i = 0;
		while (navbar->actual->subs[i])
		{
			if (is_showable(navbar->actual->subs[i]))
				check_buttons(navbar->actual->subs[i]->buttons, pos);
			i++;
		}
	}
	return (0);
}

static void	button_click2(t_button *button)
{
	if (button->id == I_AXIS)
		get_fdf()->isometric.axis = button->selected;
	else if (button->id == P_AXIS)
		get_fdf()->parallel.axis = button->selected;
	else if (button->id == I_MIRROR)
		get_fdf()->isometric.mirror = button->selected;
	else if (button->id == C_MIRROR)
		get_fdf()->conic.mirror = button->selected;
	else if (button->id == P_MIRROR)
		get_fdf()->parallel.mirror = button->selected;
	else if (button->id == I_ONLY_POINTS)
		get_fdf()->isometric.only_points = button->selected;
	else if (button->id == C_ONLY_POINTS)
		get_fdf()->conic.only_points = button->selected;
	else if (button->id == P_ONLY_POINTS)
		get_fdf()->parallel.only_points = button->selected;
}

static void	button_click(t_button *button)
{
	if (button->id == BGG && button->color == black)
		change_background(get_fdf(), NULL);
	else if (button->id == BGG)
		change_background(get_fdf(), button->color);
	else if (button->id == LINE)
		update_colors(get_fdf(), button->color);
	else if (button->type == NAVBAR)
		navbutton_click(button);
	else if (button->type == KEYBOX && button->selected)
		get_fdf()->edit_key = get_key_from(get_controls(get_fdf()), button->id);
	else if (button->type == KEYBOX)
		get_fdf()->edit_key = NULL;
	else
		button_click2(button);
	get_fdf()->must_update = 1;
}

static void	check_click(t_button **buttons, t_vector2 pos)
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
			button_click(buttons[i]);
		}
		i++;
	}
}

int	on_click_navbar(int id, int x, int y, t_navbar *navbar)
{
	int			i;
	t_vector2	pos;

	if (id != 1 || !navbar || check_outnav(y, navbar))
		return (0);
	i = 0;
	pos = ft_vector2(x, y);
	while (navbar->categories[i])
	{
		if (is_button(pos, navbar->categories[i]->main))
			button_click(navbar->categories[i]->main);
		i++;
	}
	if (navbar->actual)
	{
		check_click(navbar->actual->buttons, pos);
		i = 0;
		while (navbar->actual->subs[i])
		{
			if (is_showable(navbar->actual->subs[i]))
				check_click(navbar->actual->subs[i]->buttons, pos);
			i++;
		}
	}
	return (0);
}
