/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navbar_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:30:34 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 16:47:47 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	exec(int (showable)(void))
{
	return (showable());
}

void	check_buttons(t_button **buttons, t_vector2 pos)
{
	int	i;
	int			hovered;

	i = 0;	
	while (buttons[i])
	{
		hovered = buttons[i]->hover;
		buttons[i]->hover = is_button(pos, buttons[i]);
		if (hovered != buttons[i]->hover)
		{
			get_navbar()->must_update = 1;
			break ;
		}
		i++;
	}
}

int	on_move_navbar(int x, int y, t_navbar *navbar)
{
	t_category	**categories;
	int			i;
	t_vector2	pos;
	t_button	*main;
	int			hovered;

	if (!navbar)
		return (0); 
	categories = navbar->categories;
	i = 0;
	pos.x = x;
	pos.y = y;
	while (categories[i])
	{
		main = categories[i]->main;
		hovered = main->hover;
		categories[i]->main->hover = is_button(pos, main);
		if (hovered != categories[i]->main->hover)
		{
			navbar->must_update = 1;
			break ;
		}
		i++;
	}
	if (navbar->actual)
	{
		check_buttons(navbar->actual->buttons, pos);
		i = 0;
		while (navbar->actual->subs[i])
		{
			if (exec(navbar->actual->subs[i]->showable))
				check_buttons(navbar->actual->subs[i]->buttons, pos);
			i++;
		}
	}
	return (0);
}

int	on_click_navbar(int id, int x, int y, t_navbar *navbar)
{
	int			i;
	t_vector2	pos;

	if (id != 1 || !navbar)
		return (0);
	i = 0;
	pos.x = x;
	pos.y = y;
	while (navbar->categories[i])
	{
		if (is_button(pos, navbar->categories[i]->main))
		{
			navbar->must_update = 1;
			button_click(fdf, navbar->categories[i]->main);
		}
		i++;
	}
	if (navbar->actual)
	{
		check_click(fdf, navbar->actual->buttons, pos);
		i = 0;
		while (navbar->actual->subs[i])
		{
			if (exec(navbar->actual->subs[i]->showable))
				check_click(fdf, navbar->actual->subs[i]->buttons, pos);
			i++;
		}
	}
	if (y > 150 && navbar->actual)
	{
		navbar->actual->main->selected = 0;
		navbar->actual = NULL;
		navbar->must_update = 1;
	}
	return (0);
}
