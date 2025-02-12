/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:52:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 17:52:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_btn(t_category *category, t_button *button)
{
	int			count;

	if (!category)
	{
		free(button);
		return ;
	}
	button->category = category;
	count = buttons_count(category->buttons);
	category->buttons = ft_realloc(category->buttons,
			(count + 1) * sizeof(t_button *),
			(count + 2) * sizeof(t_button *));
	category->buttons[count] = button;
	category->buttons[count + 1] = NULL;
}

void	add_sbtn(t_subcategory *sub, t_button *button)
{
	int			count;

	if (!sub)
	{
		free(button);
		return ;
	}
	button->category = sub->category;
	count = buttons_count(sub->buttons);
	sub->buttons = ft_realloc(sub->buttons,
			(count + 1) * sizeof(t_button *),
			(count + 2) * sizeof(t_button *));
	sub->buttons[count] = button;
	sub->buttons[count + 1] = NULL;
}

void	navbutton_click(t_button *button)
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

void	check_buttons(t_button **buttons, t_vector2 pos)
{
	int	i;
	int	hovered;

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
